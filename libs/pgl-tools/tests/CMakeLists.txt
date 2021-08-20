file(GLOB
    test_files
    logger.cpp
)

foreach(test_name ${test_files})
    get_filename_component(bin_name ${test_name} NAME_WE)

    add_executable(Pgl.${bin_name} ${test_name})
    target_link_libraries(Pgl.${bin_name}
        PRIVATE
            gtest gtest_main pgl::tools
    )

    gtest_add_tests(Pgl.${bin_name} "" AUTO)
endforeach(test_name)
