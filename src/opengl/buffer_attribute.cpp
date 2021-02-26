#include "buffer_attribute.h"

std::size_t gl::buffer_attribute::size() const
{
	switch (m_type)
	{
	case gl::data_type::float1: return 1 * sizeof(float);
	case gl::data_type::float2: return 2 * sizeof(float);
	case gl::data_type::float3: return 3 * sizeof(float);
	case gl::data_type::float4: return 4 * sizeof(float);
	case gl::data_type::int1: return 1 * sizeof(int);
	case gl::data_type::int2: return 2 * sizeof(int);
	case gl::data_type::int3: return 3 * sizeof(int);
	case gl::data_type::int4: return 4 * sizeof(int);
	default: return 0;
	}
}

std::size_t gl::buffer_attribute::component_count() const
{
	switch (m_type)
	{
	case gl::data_type::float1: return 1;
	case gl::data_type::float2: return 2;
	case gl::data_type::float3: return 3;
	case gl::data_type::float4: return 4;
	case gl::data_type::int1: return 1;
	case gl::data_type::int2: return 2;
	case gl::data_type::int3: return 3;
	case gl::data_type::int4: return 4;
	default: return 0;
	}
}
