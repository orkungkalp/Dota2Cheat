#pragma once
#include "../../SDK/pch.h"
#include "../../Config.h"

namespace Hacks {
	class DotaPlusUnlocker {
	public:
		// rebuilt from xref: "Failed to find CDOTAGameAccountPlus"
		void UpdateDotaPlusStatus();
	};
}
namespace Modules {
	inline Hacks::DotaPlusUnlocker DotaPlusUnlocker{};
}