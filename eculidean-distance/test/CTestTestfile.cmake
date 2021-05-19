# CMake generated Testfile for 
# Source directory: /home/ubuntu/eculidean-distances/eculidean-distance/test
# Build directory: /home/ubuntu/eculidean-distances/eculidean-distance/test
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(addition "./run" "/home/ubuntu/eculidean-distances/eculidean-distance/bin/test_addition")
set_tests_properties(addition PROPERTIES  WORKING_DIRECTORY "/home/ubuntu/eculidean-distances/eculidean-distance/" _BACKTRACE_TRIPLES "/home/ubuntu/eculidean-distances/eculidean-distance/test/CMakeLists.txt;9;add_test;/home/ubuntu/eculidean-distances/eculidean-distance/test/CMakeLists.txt;14;add_test_case_with_run;/home/ubuntu/eculidean-distances/eculidean-distance/test/CMakeLists.txt;0;")
add_test(multiplication "./run" "/home/ubuntu/eculidean-distances/eculidean-distance/bin/test_multiplication")
set_tests_properties(multiplication PROPERTIES  WORKING_DIRECTORY "/home/ubuntu/eculidean-distances/eculidean-distance/" _BACKTRACE_TRIPLES "/home/ubuntu/eculidean-distances/eculidean-distance/test/CMakeLists.txt;9;add_test;/home/ubuntu/eculidean-distances/eculidean-distance/test/CMakeLists.txt;15;add_test_case_with_run;/home/ubuntu/eculidean-distances/eculidean-distance/test/CMakeLists.txt;0;")
add_test(eculidean_distance "./run" "/home/ubuntu/eculidean-distances/eculidean-distance/bin/test_eculidean_distance")
set_tests_properties(eculidean_distance PROPERTIES  WORKING_DIRECTORY "/home/ubuntu/eculidean-distances/eculidean-distance/" _BACKTRACE_TRIPLES "/home/ubuntu/eculidean-distances/eculidean-distance/test/CMakeLists.txt;9;add_test;/home/ubuntu/eculidean-distances/eculidean-distance/test/CMakeLists.txt;16;add_test_case_with_run;/home/ubuntu/eculidean-distances/eculidean-distance/test/CMakeLists.txt;0;")
