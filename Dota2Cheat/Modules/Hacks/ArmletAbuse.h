#pragma once
#include "../../SDK/pch.h"
namespace Config {
	inline bool ArmletAbuse = false;
}

namespace Hacks {
	// STUB
	class ArmletAbuse {
	public:
		inline void SwitchArmletIfNeeded() {
			for (auto& proj : GameSystems::ProjectileManager->GetTrackingProjectiles()) {
				if (!proj || !proj->IsAttack() ||
					!ctx.ImportantItems["armlet"])
					continue;

				auto target = proj->GetTarget();
				auto source = proj->GetSource();
				if (target != ctx.assignedHero || !source)
					continue;

				auto armlet = ctx.ImportantItems["armlet"];
				auto attackDamage = source->GetAttackDamageMin();
				if (attackDamage >= target->GetHealth()) {

				};

			}
		}
	};

}
namespace Modules {
	inline Hacks::ArmletAbuse ArmletAbuse{};
}