#pragma once

#include <string>

#include <glad/glad.h>
#include <pgl-math/vector.hpp>
#include <pgl-math/matrix.hpp>

namespace pgl {

	/*
	 * General purpsoe shader object. Compiles from file, generates
	 * compile/link-time error messages and hosts several utility functions for
	 * easy management.
	 */
	class Shader {
		public:
			// state
			unsigned int id;
			// constructor
			Shader();
			// sets the current shader as active
			Shader& use();

			/**
			 * compiles the shader from given source code
			 * note: geometry source code is optional
			 */
			void compile(
				const char* vertex_source,
				const char* fragment_source,
				const char* geometry_source=nullptr
			);

			/* utility functions */
			void setInteger (const char* name, int   value                       );

			void setFloat   (const char* name, float value                       );
			void setVector2f(const char* name, float x, float y                  );
			void setVector3f(const char* name, float x, float y, float z         );
			void setVector4f(const char* name, float x, float y, float z, float w);

			void setVector2f(const char* name, const pgl::float2& value          );
			void setVector3f(const char* name, const pgl::float3& value          );
			void setVector4f(const char* name, const pgl::float4& value          );

			void setMatrix4 (const char* name, const pgl::float44& matrix        );

		private:
			/**
			 * checks if compilation or linking failed and if so, print the error logs
			 */
			void check_compile_errors(unsigned int object, const std::string& type);
	};

} /* end of namespace pgl */
