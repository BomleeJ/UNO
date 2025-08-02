add_executable(test_card ${CMAKE_SOURCE_DIR}/src/Card.cpp ${CMAKE_SOURCE_DIR}/tests/test_card.cpp)
target_link_libraries(test_card gtest gtest_main)
add_test(NAME CardTest COMMAND test_card)

add_executable(test_drawdeck ${SOURCES} ${CMAKE_SOURCE_DIR}/tests/test_drawdeck.cpp)
target_link_libraries(test_drawdeck gtest gtest_main)
add_test(NAME DrawDeckTest COMMAND test_drawdeck)