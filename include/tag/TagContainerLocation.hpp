#pragma once
#include <tag/TagContainerFormat.hpp>
#include <vector>

namespace tag {
	class TagContainerLocation {
	public:
		TagContainerLocation(TagContainerFormat format,
							std::uint64_t headerPosition,
							std::uint64_t length) noexcept;
		TagContainerFormat getTagContainerFormat() const noexcept;
		std::uint64_t getHeaderOffset() const noexcept;
		std::uint64_t getLength() const noexcept;
	private:

		TagContainerFormat tagContainerFormat;
		std::uint64_t headerOffset;
		std::uint64_t length;
	};
}
