#pragma once
#include "sdk.h"
#include "Wrappers.h"

// Enum from animationsystem.dll, dumped by Liberalist
enum ParticleAttachment_t : int32_t {
	PATTACH_INVALID = -1,
	PATTACH_ABSORIGIN = 0,
	PATTACH_ABSORIGIN_FOLLOW = 1,
	PATTACH_CUSTOMORIGIN = 2,
	PATTACH_CUSTOMORIGIN_FOLLOW = 3,
	PATTACH_POINT = 4,
	PATTACH_POINT_FOLLOW = 5,
	PATTACH_EYES_FOLLOW = 6,
	PATTACH_OVERHEAD_FOLLOW = 7,
	PATTACH_WORLDORIGIN = 8,
	PATTACH_ROOTBONE_FOLLOW = 9,
	PATTACH_RENDERORIGIN_FOLLOW = 10,
	PATTACH_MAIN_VIEW = 11,
	PATTACH_WATERWAKE = 12,
	PATTACH_CENTER_FOLLOW = 13,
	PATTACH_CUSTOM_GAME_STATE_1 = 14,
	PATTACH_HEALTHBAR = 15,
	MAX_PATTACH_TYPES = 16,
};

// Found via x64dbg
// Xref "CreateParticle" to a lea rax instruction
// You must see "pParticleName" below it
// Right above "pParticleName" is lea rcx, [XXXXXXXXX], Right click -> Follow in Disassembler -> Constant
// The second call instruction is GetParticleManager, has only mov rax, [XXXXXXXX] then ret
// Now the only remaining step is to get the absolute address of the call, then of the CDOTAParticleManager**(yes, it's a pointer to a pointer, must be dereferenced as seen in Globals.h)

// In the next, third call, we see:
// mov rax, [rcx]       <- Puts the Particle vtable pointer into rax
// call [rax + 38h]     <- Calls the vfunc on index 0x38 / 8 = 16
#define Particle_SetControlPoint_VTABLE_INDEX 16
class CDOTAParticleManager : public VClass {
public:

	// Struct used when creating a particle
	struct ParticleInfo {
		const char* particleName = nullptr;
		ParticleAttachment_t attachType = ParticleAttachment_t::PATTACH_INVALID;
	private:
		char pad0[4] = { 0,0,0,0 };
	public:
		BaseEntity* attachEntity = nullptr;
	private:
		void* unk0 = nullptr;
		void* unk1 = nullptr;
		void* unk2 = nullptr;
		void* unk3 = nullptr;
		void* unk4 = nullptr;
	};

	struct CNewParticleEffect : public VClass {
	
		VClass* GetParticleCollection() {
			return Member<VClass*>(0x20);
		}
		CNewParticleEffect* SetControlPoint(int idx, Vector3* pos) {
			auto coll = GetParticleCollection();
			coll->GetVFunc(Particle_SetControlPoint_VTABLE_INDEX)(coll, idx, pos);
			return this;
		}
		static void BindLua(sol::state& lua) {
			auto type = lua.new_usertype<CNewParticleEffect>("Particle");
			type["SetControlPoint"] = &CNewParticleEffect::SetControlPoint;
		}
	};

	struct ParticleWrapper {
		ParticleInfo info{};
		CNewParticleEffect* particle{};
		ENT_HANDLE handle = 0XFFFFFFFF;

		void Invalidate() {
			particle = nullptr;
			handle = 0XFFFFFFFF;
			info = CDOTAParticleManager::ParticleInfo{};
		}

		static void BindLua(sol::state& lua) {
			auto type = lua.new_usertype<ParticleWrapper>("ParticleWrapper");
			type["info"] = &ParticleWrapper::info;
			type["particle"] = &ParticleWrapper::particle;
			type["handle"] = &ParticleWrapper::handle;
		}
	};
	struct ParticleContainer : NormalClass {
		inline CNewParticleEffect* GetParticle() {
			return Member<CNewParticleEffect*>(0x10);
		}
	};

	int GetParticleCount();
	ParticleContainer** GetParticleArray();

	uint32_t GetHandle();
	void IncHandle();

	ParticleWrapper CreateParticle(const char* name, ParticleAttachment_t attachType, BaseEntity* ent);
	void DestroyParticle(uint32_t handle);
	void DestroyParticle(ParticleWrapper& info);

	static void BindLua(sol::state& lua) {
		auto type = lua.new_usertype<CDOTAParticleManager>(
			"CDOTAParticleManager"
			);
		type["GetParticleCount"] = &CDOTAParticleManager::GetParticleCount;
		//type["GetParticleArray"] = &CDOTAParticleManager::GetParticleArray;
		//type["GetHandle"] = &CDOTAParticleManager::GetHandle;
		//type["IncHandle"] = &CDOTAParticleManager::IncHandle;
		type["CreateParticle"] = &CDOTAParticleManager::CreateParticle;

		type["DestroyParticleByHandle"] = [](CDOTAParticleManager& thisptr, uint32_t handle) -> void {
			thisptr.DestroyParticle(handle);
		};

		type["DestroyParticleWrapper"] = [](CDOTAParticleManager& thisptr, ParticleWrapper& wrapper) -> void {
			thisptr.DestroyParticle(wrapper);
		};

	}
};

