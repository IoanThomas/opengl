#include "buffer_layout.h"

gl::buffer_layout::buffer_layout(const std::initializer_list<buffer_attribute> attributes)
	: m_attributes(attributes)
{
}

std::size_t gl::buffer_layout::stride() const
{
	std::size_t stride = 0;
	for (const auto& attribute : m_attributes)
	{
		stride += attribute.size();
	}

	return stride;
}
