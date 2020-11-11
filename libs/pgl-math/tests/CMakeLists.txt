find_package(glm REQUIRED)

foreach(test_name test-vector.cpp test-matrix.cpp) # test-quaternion.cpp)
	get_filename_component(bin_name ${test_name} NAME_WE)

	add_executable(Pgl.${bin_name} ${test_name})
	target_link_libraries(Pgl.${bin_name}
		PRIVATE
			gtest gtest_main glm
			pgl::math compilation_flags
	)

	gtest_add_tests(Pgl.${bin_name} "" AUTO)
endforeach(test_name)

foreach(test_name vector-properties.cpp)
	get_filename_component(bin_name ${test_name} NAME_WE)

	add_executable(Pgl.${bin_name} ${test_name})
	target_link_libraries(Pgl.${bin_name}
		PRIVATE
			pgl::math pgl::test compilation_flags
	)

	gtest_add_tests(Pgl.${bin_name} "" AUTO)
endforeach(test_name)
