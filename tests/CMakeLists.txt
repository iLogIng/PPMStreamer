find_package(GTest REQUIRED)

add_executable(test_pnmstream
    test_Math.cpp
)

target_link_libraries(test_pnmstream PRIVATE pnmstream GTest::GTest GTest::Main)
target_include_directories(test_pnmstream PRIVATE ${CMAKE_SOURCE_DIR}/include)

add_test(NAME test_pnmstream COMMAND test_pnmstream)
