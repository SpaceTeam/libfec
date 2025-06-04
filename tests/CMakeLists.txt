project(libfecTests LANGUAGES CXX)

add_executable(libfecTests_EncodeRs decode_rs_ccsds_test.cpp)
target_link_libraries(libfecTests_EncodeRs PRIVATE libfec::libfec)
add_test(NAME EncodeRs COMMAND libfecTests_EncodeRs)