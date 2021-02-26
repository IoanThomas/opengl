#pragma once

#include <glad/glad.h>

namespace gl
{
	enum class data_type
	{
		float1,
		float2,
		float3,
		float4,
		int1,
		int2,
		int3,
		int4
	};

	static GLenum data_type_to_opengl_type(const data_type type)
	{
		switch (type)
		{
		case data_type::float1:
		case data_type::float2:
		case data_type::float3:
		case data_type::float4:
			return GL_FLOAT;
		case data_type::int1:
		case data_type::int2:
		case data_type::int3:
		case data_type::int4:
			return GL_INT;
		default:
			return 0;
		}
	}
}
