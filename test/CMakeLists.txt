# Parent project does not export its library target, so this CML implicitly
# depends on being added from it, i.e. the testing is done only from the build
# tree and is not feasible from an install location

project(algorithmsTests LANGUAGES CXX)

# ---- Tests ----

add_executable(algorithms_test source/algorithms_test.cpp)
target_link_libraries(algorithms_test PRIVATE algorithms_lib)
target_compile_features(algorithms_test PRIVATE cxx_std_17)

add_test(NAME algorithms_test COMMAND algorithms_test)

# ---- End-of-file commands ----

add_folders(Test)
