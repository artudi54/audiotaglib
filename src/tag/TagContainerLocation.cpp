#include "TagContainerLocation.hpp"


namespace tag {
	TagContainerLocation::TagContainerLocation(TagContainerFormat tagFormat,
											 std::uint64_t headerOffset,
											 std::uint64_t length) noexcept
		: tagContainerFormat(tagFormat), headerOffset(headerOffset), length(length) {}


    TagContainerFormat TagContainerLocation::getTagContainerFormat() const noexcept {
		return tagContainerFormat;
	}

	std::uint64_t TagContainerLocation::getHeaderOffset() const noexcept {
		return headerOffset;
	}

	std::uint64_t TagContainerLocation::getLength() const noexcept {
		return length;
	}
}
