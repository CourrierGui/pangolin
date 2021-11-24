file(GLOB
    files
    basic.cpp # TODO rename
    # checker.cpp
    # main.cpp
)

foreach(file ${files})
    get_filename_component(bin ${file} NAME_WE)

    add_executable(PglTest.test-${bin} ${file})
    target_link_libraries(PglTest.test-${bin}
        PRIVATE
            pgl::test compilation_flags
    )
    target_compile_options(PglTest.test-${bin}
        PRIVATE
            -Wno-tautological-compare
    )
    add_test(
        NAME    PglTest.test-${bin}
        COMMAND PglTest.test-${bin}
    )
endforeach(file)
