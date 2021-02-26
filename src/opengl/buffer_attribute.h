#pragma once

#include <cstddef>

#include "data_type.h"

namespace gl
{
	class buffer_attribute
	{
	public:
		buffer_attribute(const data_type type, const bool normalised = false)
			: m_type(type), m_normalised(normalised) {}

		std::size_t size() const;
		std::size_t component_count() const;

		data_type get_type() const { return m_type; }
		bool is_normalised() const { return m_normalised; }

	private:
		data_type m_type;
		bool m_normalised;
	};
}
