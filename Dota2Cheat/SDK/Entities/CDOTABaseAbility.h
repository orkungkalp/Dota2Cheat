#pragma once
#include "CBaseEntity.h"

// Structure that GetKVEntry returns, rebuilt through Reclass
struct AbilityKVEntry : public NormalClass {
	GETTER(const char*, GetKey, 0);
	GETTER(int, GetValuesSize, 0x30);

	auto GetValues() {
		auto size = GetValuesSize();
		return std::span{ MemberInline<float>(0x34), uint64_t(size) };
	}
};

class CDOTABaseAbility : public CBaseEntity {
public:
	// The problem is that GetLevelSpecialValueFor fails to find a non-special value like AbilityCastRange
	// Which is why we also need that GetKVEntry thing, thankfully it's inside GetLevelSpecialValueFor

	
	using GetLevelSpecialValueForFn = float(__fastcall* )(void* thisptr, const char* value, int level, void* unk1, bool noOverride, bool* result);
	static inline GetLevelSpecialValueForFn GetLevelSpecialValueForFunc{};

	typedef AbilityKVEntry* (__fastcall* GetKVEntryFn)(CDOTABaseAbility* thisptr, const char* value);
	static inline GetKVEntryFn GetKVEntry{};
	
	template<typename T = float>
	T GetLevelSpecialValueFor(const char* value, int level = -1) {
		return (T)GetLevelSpecialValueForFunc(this, value, level, nullptr, 0, nullptr);
	}

	// For things like Pudge's Rot or Armlet
	GETTER(bool, IsToggled, Netvars::C_DOTABaseAbility::m_bToggleState);
	GETTER(bool, IsHidden, Netvars::C_DOTABaseAbility::m_bHidden);
	GETTER(float, GetCooldown, Netvars::C_DOTABaseAbility::m_fCooldown);
	GETTER(float, GetCooldownLength, Netvars::C_DOTABaseAbility::m_flCooldownLength);
	GETTER(int, GetLevel, Netvars::C_DOTABaseAbility::m_iLevel);
	GETTER(int, GetMaxLevel, Netvars::C_DOTABaseAbility::m_iMaxLevel);
	GETTER(int, GetCharges, Netvars::C_DOTABaseAbility::m_nAbilityCurrentCharges);
	GETTER(float, GetChargeRestoreCooldown, Netvars::C_DOTABaseAbility::m_fAbilityChargeRestoreTimeRemaining);
	GETTER(int, GetManaCost, Netvars::C_DOTABaseAbility::m_iManaCost);
	GETTER(bool, IsInAbilityPhase, Netvars::C_DOTABaseAbility::m_bInAbilityPhase);

	// xref: "GetCastRange" to lea rcx, above that is lea rax, [XXXXXXXXX]
	// In the end of the func is a call to [rcx + 0x???] <--- that divided by 8 gives you the index
	int GetCastRange();

	// Goes right after GetCastRange ^
	int GetCastRangeBonus();
	int GetEffectiveCastRange();

	// Rebuilt by analyzing GetLevelSpecialValueFor logic
	template<typename T = float>
	T GetKVValueFor(const char* valName, int level = -1);

	int GetAOERadius();

	static void BindLua(sol::state& lua);
};

// Rebuilt by analyzing GetLevelSpecialValueFor logic
template<typename T>
T CDOTABaseAbility::GetKVValueFor(const char* valName, int level) {
	auto entry = GetKVEntry(this, valName);

	// Clamping the level value
	if (level < 0)
		level = GetLevel();
	if (level > entry->GetValuesSize() - 1)
		level = entry->GetValuesSize();

	auto values = entry->GetValues();
	return (T)values[level - 1];
}
