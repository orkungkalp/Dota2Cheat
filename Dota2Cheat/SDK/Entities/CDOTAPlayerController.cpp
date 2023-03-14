#include "CDOTAPlayerController.h"

std::vector<uint32_t> CDOTAPlayerController::GetSelectedUnits() {
	return Member<CUtlVector<uint32_t>>(Netvars::C_DOTAPlayerController::m_nSelectedUnits).AsStdVector();
}

CDOTABaseNPC_Hero* CDOTAPlayerController::GetAssignedHero() {
	return Interfaces::EntitySystem->GetEntity<CDOTABaseNPC_Hero>(H2IDX(GetAssignedHeroHandle()));
}

void CDOTAPlayerController::CastNoTarget(ENT_HANDLE handle, CBaseEntity* issuer) {
	if (issuer == nullptr)
		issuer = GetAssignedHero();
	PrepareOrder(DOTA_UNIT_ORDER_CAST_NO_TARGET,
		0,
		&Vector::Zero,
		H2IDX(handle),
		DOTA_ORDER_ISSUER_PASSED_UNIT_ONLY,
		issuer,
		false,
		true
	);
}

void CDOTAPlayerController::BuyItem(int itemId) {
	PrepareOrder(DOTA_UNIT_ORDER_PURCHASE_ITEM,
		1,
		&Vector::Zero,
		itemId,
		DOTA_ORDER_ISSUER_PASSED_UNIT_ONLY,
		GetAssignedHero(),
		false,
		true
	);
}

void CDOTAPlayerController::OrderMoveTo(Vector* pos, bool directMovement, CBaseEntity* issuer) {
	if (issuer == nullptr)
		issuer = GetAssignedHero();

	PrepareOrder(directMovement ? DOTA_UNIT_ORDER_MOVE_TO_DIRECTION : DOTA_UNIT_ORDER_MOVE_TO_POSITION,
		0,
		pos,
		0,
		DOTA_ORDER_ISSUER_PASSED_UNIT_ONLY,
		issuer,
		false,
		true
	);
}

void CDOTAPlayerController::PrepareOrder(dotaunitorder_t orderType, uint32_t targetIndex, Vector* position, uint32_t abilityIndex, PlayerOrderIssuer_t orderIssuer, CBaseEntity* issuer, bool queue, bool showEffects) {
	//if (issuer == nullptr)
	//	issuer = GetAssignedHero();

	if (Signatures::PrepareUnitOrders == nullptr)
		return;

	Signatures::PrepareUnitOrders(this, orderType, targetIndex, position, abilityIndex, orderIssuer, issuer, queue, showEffects);
}

void CDOTAPlayerController::BindLua(sol::state& lua) {
	auto type = lua.new_usertype<CDOTAPlayerController>("CDOTAPlayerController", sol::base_classes, sol::bases<CBaseEntity>());
	type["GetAssignedHeroHandle"] = &CDOTAPlayerController::GetAssignedHeroHandle;
	type["GetSelectedUnits"] = &CDOTAPlayerController::GetSelectedUnits;
	type["GetAssignedHero"] = &CDOTAPlayerController::GetAssignedHero;
	type["GetSteamID"] = &CDOTAPlayerController::GetSteamID;

	type["PrepareOrder"] = &CDOTAPlayerController::PrepareOrder;
	type["CastNoTarget"] = &CDOTAPlayerController::CastNoTarget;
	type["OrderMoveTo"] = &CDOTAPlayerController::OrderMoveTo;
	type["BuyItem"] = &CDOTAPlayerController::BuyItem;
}
