#pragma once
#include "sdk.h"
#include "Wrappers.h"

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
class CDOTAParticleManager :public VClass {
public:
	// Enum from animationsystem.dll, dumped by Liberalist
	enum class ParticleAttachment_t : int {
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

	// Struct used when creating a particle
	struct ParticleInfo {
		const char* particleName;
		ParticleAttachment_t attachtType;
		BaseEntity* attachEntity;
	private:
		void* unk0 = nullptr;
		void* unk1 = nullptr;
		void* unk2 = nullptr;
		void* unk3 = nullptr;
		void* unk4 = nullptr;
	};

	class Particle : public VClass {
	public:
		VClass* GetParticleCollection() {
			return Member<VClass*>(0x20);
		}
		Particle* SetControlPoint(int idx, Vector3* pos) {
			auto coll = GetParticleCollection();
			coll->GetVFunc(Particle_SetControlPoint_VTABLE_INDEX)(coll, idx, pos);
			return this;
		}
	};
	struct ParticleContainer : NormalClass {
		Particle* GetParticle() {
			return Member<Particle*>(0x10);
		}
	};

	int GetParticleCount() {
		return Member<uint32_t>(0x80);
	}
	ParticleContainer** GetParticleArray() {
		return Member<ParticleContainer**>(0x88);
	}

	uint32_t GetHandle() {
		return Member<uint32_t>(0x98);
	}
	void IncHandle() {
		*(uint32_t*)((uintptr_t)this + 0x98) = GetHandle() + 1;
	}

	struct ParticleWrapper {
		ParticleInfo info;
		Particle* particle;
		ENT_HANDLE handle;
	};

	ParticleWrapper CreateParticle(const char* name, ParticleAttachment_t attachType, BaseEntity* ent = nullptr) {
		CDOTAParticleManager::ParticleInfo info{};
		info.attachtType = attachType;
		info.attachEntity = ent;
		info.particleName = name;

		IncHandle();
		GetVFunc(7)(this, GetHandle(), info);

		ParticleWrapper result{};
		result.info = info;
		result.particle = GetParticleArray()[GetParticleCount() - 1]->GetParticle();
		result.handle = GetHandle();

		return result;
	}
};