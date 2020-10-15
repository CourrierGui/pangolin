foreach(test_name test-vector.cpp test-matrix.cpp) # test-quaternion.cpp)
	get_filename_component(bin_name ${test_name} NAME_WE)

	add_executable(Pgl.${bin_name} ${test_name})
	target_link_libraries(Pgl.${bin_name}
		PRIVATE
			gtest gtest_main
			pangolin::pgl-math target-flags
	)

	gtest_add_tests(Pgl.${bin_name} "" AUTO)
endforeach(test_name)

foreach(test_name vector-properties.cpp)
	get_filename_component(bin_name ${test_name} NAME_WE)

	add_executable(Pgl.${bin_name} ${test_name})
	target_link_libraries(Pgl.${bin_name}
		PRIVATE
			pangolin::pgl-test
			pangolin::pgl-math target-flags
	)

	gtest_add_tests(Pgl.${bin_name} "" AUTO)
endforeach(test_name)
