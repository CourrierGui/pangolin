find_package(glm REQUIRED)

file(GLOB
    files
    base-vector.cpp
    algebraic-vector.cpp
    vector.cpp
    # matrix.cpp
    # quaternion.cpp
)

foreach(file ${files})
    get_filename_component(bin ${file} NAME_WE)

    add_executable(PglMath.test-${bin} ${file})
    target_link_libraries(PglMath.test-${bin}
        PRIVATE
            pgl::math pgl::test compilation_flags
    )
    add_test(
        NAME    PglMath.test-${bin}
        COMMAND PglMath.test-${bin}
    )
endforeach(file)
