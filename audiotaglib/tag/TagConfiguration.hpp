#pragma once
#include <memory>

namespace tag::manager {

	class TagConfiguration {
	public:
		bool probeAllPossible = false;
		bool saveOnDestroy = false;
		bool saveWithPrefferedFormat = true;
	};

	using SharedTagConfiguration = std::shared_ptr<TagConfiguration>;
}

