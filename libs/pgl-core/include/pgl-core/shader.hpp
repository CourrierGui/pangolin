#pragma once

#include <string>

#include <glad/glad.h>
#include <pgl-math/impl/vector.hpp>
#include <pgl-math/impl/matrix.hpp>

namespace pgl {

    /*
     * General purpsoe shader object. Compiles from file, generates
     * compile/link-time error messages and hosts several utility functions for
     * easy management.
     */
    class shader {
        public:
            // state
            unsigned int id;
            // constructor
            shader();
            // sets the current shader as active
            shader& use();

            /**
             * compiles the shader from given source code
             * note: geometry source code is optional
             */
            void compile(const char* vertex_source,
                         const char* fragment_source,
                         const char* geometry_source=nullptr);

            /* utility functions */
            void setvalue(const char* name, int   value);
            void setvalue(const char* name, float value);
            void setvalue(const char* name, float x, float y);
            void setvalue(const char* name, float x, float y, float z);
            void setvalue(const char* name, float x, float y, float z, float w);
            void setvalue(const char* name, const pgl::float2& value);
            void setvalue(const char* name, const pgl::float3& value);
            void setvalue(const char* name, const pgl::float4& value);
            void setvalue(const char* name, const pgl::float44& matrix);

        private:
            /**
             * checks if compilation or linking failed and if so, print the error logs
             */
            void check_compile_errors(unsigned int object, const std::string& type);
    };

} /* end of namespace pgl */
