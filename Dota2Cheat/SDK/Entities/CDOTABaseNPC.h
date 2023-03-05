#pragma once
#include "../Globals/Interfaces.h"
#include "CBaseEntity.h"
#include "CDOTABaseAbility.h"
#include "CDOTAUnitInventory.h"
#include "CDOTAModifierManager.h"

struct ItemOrAbility {
	const char* name;
	ENT_HANDLE handle;
	ItemOrAbility(const char* name, ENT_HANDLE handle) :name(name), handle(handle) {

	}
	CDOTABaseAbility* GetEnt() const {
		return Interfaces::EntitySystem->GetEntity<CDOTABaseAbility>(H2IDX(handle));
	}
	bool IsValid() const {
		return handle != 0xFFFFFFFF;
	}

	static void BindLua(sol::state& lua) {
		auto type = lua.new_usertype<ItemOrAbility>("ItemOrAbility", sol::constructors<ItemOrAbility(const char*, ENT_HANDLE)>());

		type["GetEnt"] = &ItemOrAbility::GetEnt;
		type["IsValid"] = &ItemOrAbility::IsValid;
	}
};

class CDOTABaseNPC : public CBaseEntity {
public:
	CDOTAModifierManager* GetModifierManager() {
		// Inlined into the object instead of a pointer
		return MemberInline<CDOTAModifierManager>(Netvars::C_DOTA_BaseNPC::m_ModifierManager);
	}

	// Wrapper function combining the following conditions: 
	// Is not dormant
	// Is alive
	// Is not waiting to spawn
	bool IsTargetable() {
		return !GetIdentity()->IsDormant() && GetLifeState() == 0 && !IsWaitingToSpawn();
	}
	bool IsWaitingToSpawn() {
		return Member<bool>(Netvars::C_DOTA_BaseNPC::m_bIsWaitingToSpawn);
	}
	bool IsAncient() {
		return Member<bool>(Netvars::C_DOTA_BaseNPC::m_bIsAncient);
	}

	//Implemented as a method returning a bool rather than a field
	//Is inside some kind of structure on offset BE8
	bool IsRoshan() {
		return MemberInline<VClass>(0xbe8)->CallVFunc<57, bool>();
	}

	int GetAttackRange() {
		return Member<int>(Netvars::C_DOTA_BaseNPC::m_iAttackRange);
	}

	float GetSSC() {
		return Member<float>(Netvars::C_DOTA_BaseNPC::m_flStartSequenceCycle);
	}
	ENT_HANDLE GoalEntity() {
		return Member<ENT_HANDLE>(Netvars::C_DOTA_BaseNPC::m_hGoalEntity);
	}
	const char* GetUnitName() {
		return Member<const char*>(Netvars::C_DOTA_BaseNPC::m_iszUnitName);
	}
	std::vector<ItemOrAbility> GetAbilities() {
		std::vector<ItemOrAbility> result{};
		ENT_HANDLE* hAbilities = MemberInline<ENT_HANDLE>(Netvars::C_DOTA_BaseNPC::m_hAbilities);
		for (int j = 0; j < 35; j++) {
			ENT_HANDLE handle = hAbilities[j];
			if (!HVALID(handle))
				continue;

			auto* identity = Interfaces::EntitySystem->GetIdentity(H2IDX(handle));
			result.push_back(ItemOrAbility(identity->GetName(), identity->entHandle));
		}
		return result;
	}

	ItemOrAbility FindItemBySubstring(const char* str) {
		if (!str)
			return ItemOrAbility{ nullptr, 0xFFFFFFFF };
		for (const auto& item : GetItems())
			if (item.name &&
				strstr(item.name, str))
				return item;

		return ItemOrAbility{ nullptr, 0xFFFFFFFF };
	}

	CDOTAUnitInventory* GetInventory() {
		return MemberInline<CDOTAUnitInventory>(Netvars::C_DOTA_BaseNPC::m_Inventory);
	}
	std::vector<ItemOrAbility> GetItems() {
		std::vector<ItemOrAbility> result{};
		CDOTAUnitInventory* inv = GetInventory();
		if (!inv)
			return result;

		auto itemsHandle = inv->GetItems();
		for (auto& handle : itemsHandle) {
			if (!HVALID(handle))
				continue;

			auto* identity = Interfaces::EntitySystem->GetIdentity(H2IDX(handle));
			result.push_back(ItemOrAbility(identity->GetName(), identity->entHandle));
		}

		return result;
	}

	float GetMana() {
		return Member<float>(Netvars::C_DOTA_BaseNPC::m_flMana);
	}
	float GetMaxMana() {
		return Member<float>(Netvars::C_DOTA_BaseNPC::m_flMaxMana);
	}

	float GetBaseAttackTime() {
		return Member<float>(Netvars::C_DOTA_BaseNPC::m_flBaseAttackTime);
	}
	float GetHullRadius() {
		return Member<float>(Netvars::C_DOTA_BaseNPC::m_flHullRadius);
	}
	float GetAttackSpeed() {
		return 1 + CallVFunc<295, float>();
	}

	static void BindLua(sol::state& lua) {
		auto type = lua.new_usertype<CDOTABaseNPC>("CDOTABaseNPC", sol::base_classes, sol::bases<CBaseEntity>());

		type["GetModifierManager"] = &CDOTABaseNPC::GetModifierManager;
		type["IsTargetable"] = &CDOTABaseNPC::IsTargetable;
		type["IsWaitingToSpawn"] = &CDOTABaseNPC::IsWaitingToSpawn;
		type["IsAncient"] = &CDOTABaseNPC::IsAncient;
		type["IsRoshan"] = &CDOTABaseNPC::IsRoshan;
		type["GetAttackRange"] = &CDOTABaseNPC::GetAttackRange;
		type["GetSSC"] = &CDOTABaseNPC::GetSSC;
		type["GoalEntity"] = &CDOTABaseNPC::GoalEntity;
		type["GetUnitName"] = &CDOTABaseNPC::GetUnitName;
		type["GetAbilities"] = &CDOTABaseNPC::GetAbilities;
		type["FindItemBySubstring"] = &CDOTABaseNPC::FindItemBySubstring;
		type["GetInventory"] = &CDOTABaseNPC::GetInventory;
		type["GetItems"] = &CDOTABaseNPC::GetItems;;
		type["GetMana"] = &CDOTABaseNPC::GetMana;
		type["GetMaxMana"] = &CDOTABaseNPC::GetMaxMana;
		type["GetBaseAttackTime"] = &CDOTABaseNPC::GetBaseAttackTime;
		type["GetHullRadius"] = &CDOTABaseNPC::GetHullRadius;
		type["GetAttackSpeed"] = &CDOTABaseNPC::GetAttackSpeed;
		lua["CDOTABaseNPC"] = [](CBaseEntity* ent) { return (CDOTABaseNPC*)ent; };
	}
};
