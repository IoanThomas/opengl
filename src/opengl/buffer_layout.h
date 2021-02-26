#pragma once

#include <cstddef>
#include <initializer_list>
#include <iterator>
#include <vector>

#include "buffer_attribute.h"

namespace gl
{
	class buffer_layout
	{
	public:
		buffer_layout(const std::initializer_list<buffer_attribute> attributes);

		std::size_t stride() const;

		std::vector<buffer_attribute>::iterator begin() { return m_attributes.begin(); }
		std::vector<buffer_attribute>::iterator end() { return m_attributes.end(); }
		std::vector<buffer_attribute>::const_iterator begin() const { return m_attributes.begin(); }
		std::vector<buffer_attribute>::const_iterator end() const { return m_attributes.end(); }

	private:
		std::vector<buffer_attribute> m_attributes;
	};
}
