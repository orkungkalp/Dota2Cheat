#pragma once
#include "../../Config.h"

namespace Hacks {
	class AutoDodge {
	public:
		void FrameBasedLogic();
	};
}
namespace Modules {
	inline Hacks::AutoDodge AutoDodge{};
}