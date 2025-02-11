#include "MatchStateHandling.h"
#include "HookHelper.h"
#include "Lua/LuaModules.h"
void FillPlayerList() {
	auto vec = GameSystems::PlayerResource->GetVecPlayerTeamData();
	std::cout << "<PLAYERS>\n";
	for (auto& data : vec) {
		auto slot = data.GetPlayerSlot();

		auto player = Interfaces::EntitySystem->GetEntity<CDOTAPlayerController>(
			H2IDX(
				GameSystems::PlayerResource->PlayerSlotToHandle(slot)
			)
			);

		if (!player)
			continue;

		auto hero = player->GetAssignedHero();
		std::cout << "Player " << std::dec << slot << ": " << player;
		if (hero &&
			hero->GetUnitName()) {
			std::cout << "\n\t" << hero->GetUnitName() << " " << hero;
			ctx.heroes.insert(hero);
		}

		std::cout << '\n';
		//players.push_back(player);
	}
}

// Now that the iteration is based on collections, the cheat does not retain the entity lists upon reinjection
void CacheAllEntities() {
	if (ctx.gameStage != Context::GameStage::IN_GAME)
		return;
	for (int i = 0; i <= Interfaces::EntitySystem->GetHighestEntityIndex(); i++) {
		auto ent = Interfaces::EntitySystem->GetEntity(i);
		if (ent->SchemaBinding()->binaryName) {
			std::string_view className = ent->SchemaBinding()->binaryName;

			if (className == "C_DOTA_Item_Physical")
				ctx.physicalItems.insert(ent);
			else if (className.find("Creep") != -1)
				ctx.creeps.insert((CDOTABaseNPC*)ent);
			else if (className == "C_DOTA_Item_Rune")
				ctx.runes.insert((CDOTAItemRune*)ent);
			else if (className.find("C_DOTA_Unit_Hero") != -1)
				ctx.heroes.insert(reinterpret_cast<CDOTABaseNPC_Hero*>(ent));

			ctx.entities.insert(ent);
			Lua::CallModuleFunc("OnAddEntity", ent);
		}
	}
}
void OnUpdatedAssignedHero()
{
	ctx.lua["localHero"] = ctx.assignedHero;
	Lua::CallModuleFunc("OnUpdatedAssignedHero");

	for (auto& modifier : ctx.assignedHero->GetModifierManager()->GetModifierList())
		Hooks::CacheIfItemModifier(modifier); // for registering important items on reinjection

	Modules::ShakerAttackAnimFix.SubscribeEntity(ctx.assignedHero);
}

void UpdateAssignedHero() {
	if (!ctx.localPlayer)
		return;

	auto heroHandle = ctx.localPlayer->GetAssignedHeroHandle();
	if (ctx.assignedHeroHandle != heroHandle) {
		ctx.assignedHeroHandle = heroHandle;
		auto assignedHero = Interfaces::EntitySystem->GetEntity<CDOTABaseNPC_Hero>(H2IDX(ctx.localPlayer->GetAssignedHeroHandle()));
		ctx.assignedHero = assignedHero;

		std::cout << "Changed hero:" << '\n';
		std::cout << "\thandle: " << std::hex << heroHandle << '\n';
		std::cout << "\tentity: " << assignedHero << '\n';

		if (assignedHero)
			OnUpdatedAssignedHero();
	}
}

void EnteredPreGame() {
	GetGameSystem(GameRules);
	GetGameSystem(ProjectileManager);
	GetGameSystem(PlayerResource);
	GetGameSystem(ParticleManager);
	GetGameSystem(GameEventManager);

	//	Modules::AutoPick.autoBanHero = "sniper";
	//	Modules::AutoPick.autoPickHero = "arc_warden";

	ctx.localPlayer = Signatures::GetPlayer(-1);
	if (!ctx.localPlayer)
		return;

	ctx.gameStage = Context::GameStage::PRE_GAME;
	std::cout << "[PRE-GAME]\n";
}

void EnteredInGame() {
	DOTA_GameState gameState = GameSystems::GameRules->GetGameState();
	if (gameState != DOTA_GAMERULES_STATE_PRE_GAME &&
		gameState != DOTA_GAMERULES_STATE_GAME_IN_PROGRESS)
		return;

	UpdateAssignedHero();

	if (!ctx.assignedHero) {
		return;
	}

	//Config::AutoPingTarget = ctx.assignedHero;
	//FillPlayerList();

	std::cout << "[GAME]:\n";
	std::cout << "Local Player: " << ctx.localPlayer
		<< "\n\t" << std::dec << "STEAM ID: " << ctx.localPlayer->GetSteamID()
		<< '\n';
	if (ctx.assignedHero->GetUnitName())
		std::cout << "Assigned Hero: " << ctx.assignedHero << " " << ctx.assignedHero->GetUnitName() << '\n';

	Interfaces::CVar->SetConvars();

	auto roshanListener = new RoshanListener();
	roshanListener->gameStartTime = GameSystems::GameRules->GetGameTime();
	auto hurtListener = new EntityHurtListener();
	GameSystems::GameEventManager->AddListener(roshanListener, "dota_roshan_kill");
	//GameSystems::GameEventManager->AddListener(hurtListener, "entity_hurt");

	GameSystems::LogGameSystems();

	Lua::SetGlobals(ctx.lua);

	CacheAllEntities();

	Modules::AutoBuyTome.Init();
	Modules::AbilityESP.SubscribeHeroes();

	Lua::CallModuleFunc("Init");

	Hooks::EnableHooks();
	ctx.gameStage = Context::GameStage::IN_GAME;
	std::cout << "[/GAME]\n";
}

void LeftMatch() {
	ctx.gameStage = Context::GameStage::NONE;

	Lua::CallModuleFunc("Reset");

	GameSystems::ParticleManager->OnExitMatch();

	Modules::AutoBuyTome.Reset();
	Modules::TargetedSpellHighlighter.Reset();
	Modules::AutoPick.Reset();
	Modules::ParticleGC.Reset();
	Modules::AbilityESP.Reset();

	GameSystems::PlayerResource = nullptr;
	GameSystems::GameRules = nullptr;
	GameSystems::ParticleManager = nullptr;
	GameSystems::ProjectileManager = nullptr;

	for (auto& listener : CGameEventManager::EventListeners)
		GameSystems::GameEventManager->RemoveListener(listener.get());
	CGameEventManager::EventListeners.clear();
	GameSystems::GameEventManager = nullptr;

	ctx.localPlayer = nullptr;
	ctx.assignedHero = nullptr;

	Lua::SetGlobals(ctx.lua);
	Hooks::DisableHooks();
	texManager.QueueTextureUnload();

	std::cout << "LEFT MATCH\n";
}

void CheckMatchState() {
	if (Interfaces::Engine->IsInGame()) {
		//Modules::AutoPick.TryAutoBan();
		if (ctx.gameStage == Context::GameStage::NONE)
			EnteredPreGame();
		else if (ctx.gameStage == Context::GameStage::PRE_GAME)
			EnteredInGame();
		else if (ctx.gameStage == Context::GameStage::IN_GAME)
			UpdateAssignedHero();
	}
	else if (ctx.gameStage != Context::GameStage::NONE)
		LeftMatch();
}
