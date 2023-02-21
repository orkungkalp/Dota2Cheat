#pragma once
#include <sol/sol.hpp>
#include "../Enums.h"
#include "../CGameEntitySystem.h"
#include "../Wrappers.h"
#define LUA_ENUM_TABLE_ENTRY(x) #x, x

namespace Lua {
	inline void InitEnums(sol::state& lua) {

		auto orderTable = lua.create_table_with(
			LUA_ENUM_TABLE_ENTRY(DOTA_UNIT_ORDER_NONE),
			LUA_ENUM_TABLE_ENTRY(DOTA_UNIT_ORDER_MOVE_TO_POSITION),
			LUA_ENUM_TABLE_ENTRY(DOTA_UNIT_ORDER_MOVE_TO_TARGET),
			LUA_ENUM_TABLE_ENTRY(DOTA_UNIT_ORDER_ATTACK_MOVE),
			LUA_ENUM_TABLE_ENTRY(DOTA_UNIT_ORDER_ATTACK_TARGET),
			LUA_ENUM_TABLE_ENTRY(DOTA_UNIT_ORDER_CAST_POSITION),
			LUA_ENUM_TABLE_ENTRY(DOTA_UNIT_ORDER_CAST_TARGET),
			LUA_ENUM_TABLE_ENTRY(DOTA_UNIT_ORDER_CAST_TARGET_TREE),
			LUA_ENUM_TABLE_ENTRY(DOTA_UNIT_ORDER_CAST_NO_TARGET),
			LUA_ENUM_TABLE_ENTRY(DOTA_UNIT_ORDER_CAST_TOGGLE),
			LUA_ENUM_TABLE_ENTRY(DOTA_UNIT_ORDER_HOLD_POSITION),
			LUA_ENUM_TABLE_ENTRY(DOTA_UNIT_ORDER_TRAIN_ABILITY),
			LUA_ENUM_TABLE_ENTRY(DOTA_UNIT_ORDER_DROP_ITEM),
			LUA_ENUM_TABLE_ENTRY(DOTA_UNIT_ORDER_GIVE_ITEM),
			LUA_ENUM_TABLE_ENTRY(DOTA_UNIT_ORDER_PICKUP_ITEM),
			LUA_ENUM_TABLE_ENTRY(DOTA_UNIT_ORDER_PICKUP_RUNE),
			LUA_ENUM_TABLE_ENTRY(DOTA_UNIT_ORDER_PURCHASE_ITEM),
			LUA_ENUM_TABLE_ENTRY(DOTA_UNIT_ORDER_SELL_ITEM),
			LUA_ENUM_TABLE_ENTRY(DOTA_UNIT_ORDER_DISASSEMBLE_ITEM),
			LUA_ENUM_TABLE_ENTRY(DOTA_UNIT_ORDER_MOVE_ITEM),
			LUA_ENUM_TABLE_ENTRY(DOTA_UNIT_ORDER_CAST_TOGGLE_AUTO),
			LUA_ENUM_TABLE_ENTRY(DOTA_UNIT_ORDER_STOP),
			LUA_ENUM_TABLE_ENTRY(DOTA_UNIT_ORDER_TAUNT),
			LUA_ENUM_TABLE_ENTRY(DOTA_UNIT_ORDER_BUYBACK),
			LUA_ENUM_TABLE_ENTRY(DOTA_UNIT_ORDER_GLYPH),
			LUA_ENUM_TABLE_ENTRY(DOTA_UNIT_ORDER_EJECT_ITEM_FROM_STASH),
			LUA_ENUM_TABLE_ENTRY(DOTA_UNIT_ORDER_CAST_RUNE),
			LUA_ENUM_TABLE_ENTRY(DOTA_UNIT_ORDER_PING_ABILITY),
			LUA_ENUM_TABLE_ENTRY(DOTA_UNIT_ORDER_MOVE_TO_DIRECTION),
			LUA_ENUM_TABLE_ENTRY(DOTA_UNIT_ORDER_PATROL),
			LUA_ENUM_TABLE_ENTRY(DOTA_UNIT_ORDER_VECTOR_TARGET_POSITION),
			LUA_ENUM_TABLE_ENTRY(DOTA_UNIT_ORDER_RADAR),
			LUA_ENUM_TABLE_ENTRY(DOTA_UNIT_ORDER_SET_ITEM_COMBINE_LOCK),
			LUA_ENUM_TABLE_ENTRY(DOTA_UNIT_ORDER_CONTINUE),
			LUA_ENUM_TABLE_ENTRY(DOTA_UNIT_ORDER_VECTOR_TARGET_CANCELED),
			LUA_ENUM_TABLE_ENTRY(DOTA_UNIT_ORDER_CAST_RIVER_PAINT),
			LUA_ENUM_TABLE_ENTRY(DOTA_UNIT_ORDER_PREGAME_ADJUST_ITEM_ASSIGNMENT)
		);
		auto orderIssuerTable = lua.create_table_with(
			LUA_ENUM_TABLE_ENTRY(DOTA_ORDER_ISSUER_SELECTED_UNITS),
			LUA_ENUM_TABLE_ENTRY(DOTA_ORDER_ISSUER_CURRENT_UNIT_ONLY),
			LUA_ENUM_TABLE_ENTRY(DOTA_ORDER_ISSUER_HERO_ONLY),
			LUA_ENUM_TABLE_ENTRY(DOTA_ORDER_ISSUER_PASSED_UNIT_ONLY)
		);
		lua.create_named_table("Enum",
			"PlayerOrderIssuer", orderIssuerTable,
			"DotaUnitOrder", orderTable
			);
		
	}
	inline void InitInterfaces(sol::state& lua) {
		lua["EntitySystem"] = Interfaces::EntitySystem;
	}
	inline void InitClasses(sol::state& lua) {
#pragma region Base types
		{
			lua.new_usertype<Vector3>(
				"Vector3",
				sol::constructors<Vector3(), Vector3(float, float, float)>());
			sol::usertype<Vector2> type_Vector2 = lua.new_usertype<Vector2>(
				"Vector2",
				sol::constructors<Vector2(float, float)>());
			sol::usertype<Color> type_Color = lua.new_usertype<Color>(
				"Color",
				sol::constructors<Color(unsigned char, unsigned char, unsigned char, unsigned char)>()
				);
			type_Color["RGBA"] = &Color::RGBA;
		}
#pragma endregion

		CSchemaClassBinding::BindLua(lua);
		CEntityIdentity::BindLua(lua);

		BaseEntity::BindLua(lua);
		CGameEntitySystem::BindLua(lua);
		DotaModifier::BindLua(lua);
		DotaModifierManager::BindLua(lua);
		BaseNpc::ItemOrAbility::BindLua(lua);
		BaseNpc::BindLua(lua);
		DotaPlayer::BindLua(lua);
	}
}