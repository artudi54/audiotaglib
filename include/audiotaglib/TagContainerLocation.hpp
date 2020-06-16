#pragma once
#include <audiotaglib/TagContainerFormat.hpp>
#include <vector>

namespace audiotaglib {
	class TagContainerLocation {
	public:
		TagContainerLocation(TagContainerFormat format,
							std::uint64_t headerPosition,
							std::uint64_t length) noexcept;
		[[nodiscard]] TagContainerFormat getTagContainerFormat() const noexcept;
        [[nodiscard]] std::uint64_t getHeaderOffset() const noexcept;
        [[nodiscard]] std::uint64_t getLength() const noexcept;

	private:
		TagContainerFormat tagContainerFormat;
		std::uint64_t headerOffset;
		std::uint64_t length;
	};
}
