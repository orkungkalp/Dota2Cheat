#pragma once
#include "../SDK/pch.h"
#include "../../Utils/Drawing.h"
#include "../../Config.h"
#include <map>

namespace ESP {
	class AbilityESP {
		struct AbilityData {
			CDOTABaseAbility* ability{};
			TextureData icon{};

			float lastActiveTime{};
			float lastActiveCooldown{};
			float currentCooldown{};
		};

		std::map<std::string, TextureData*> loadingQueue;

		// Scales a value according to the config parameter
		template<typename T = int>
		T ScaleVar(auto val) {
			return (T)(val * Config::AbilityESP::UIScale);
		}

		int AbilityIconSize = 40;
		bool Initialized = false;
		static inline std::map<CDOTABaseNPC_Hero*, std::vector<AbilityData>> EnemyAbilities{};
		// For each hero there's a map of slot indexes to ability data(for items tho, but they're abilities too)
		static inline std::map<CDOTABaseNPC_Hero*, std::map<int, AbilityData>> EnemyItems{};

		bool CanDraw(CDOTABaseNPC_Hero* hero);;
		void DrawAbilities(ImFont* textFont);
		void DrawItems(ImFont* textFont);
		void DrawLevelCounter(CDOTABaseAbility* ability, ImFont* font, ImVec2 pos);
		void DrawChargeCounter(CDOTABaseAbility* ability, ImFont* font, ImVec2 pos, int radius);
	public:
		void UpdateAbilities(CDOTABaseNPC_Hero* hero);
		void UpdateItems(CDOTABaseNPC_Hero* hero);
		void UpdateHeroData();
		void SubscribeHeroes();
		void Reset();
		void DrawESP(ImFont* textFont);
	};
}
namespace Modules {
	inline ESP::AbilityESP AbilityESP{};
}