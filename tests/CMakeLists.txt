add_executable(test_card ${CMAKE_SOURCE_DIR}/src/Card.cpp ${CMAKE_SOURCE_DIR}/tests/test_card.cpp)
target_link_libraries(test_card gtest gtest_main)
add_test(NAME CardTest COMMAND test_card)

add_executable(test_drawdeck ${SOURCES} ${CMAKE_SOURCE_DIR}/tests/test_drawdeck.cpp)
target_link_libraries(test_drawdeck gtest gtest_main)
add_test(NAME DrawDeckTest COMMAND test_drawdeck)

add_executable(test_playerdeck ${SOURCES} ${CMAKE_SOURCE_DIR}/tests/test_playerdeck.cpp)
target_link_libraries(test_playerdeck gtest gtest_main)
add_test(NAME PlayerDeckTest COMMAND test_playerdeck)

add_executable(test_discardpile ${SOURCES} ${CMAKE_SOURCE_DIR}/tests/test_discardpile.cpp)
target_link_libraries(test_discardpile gtest gtest_main)
add_test(NAME DiscardPileTest COMMAND test_discardpile)

add_executable(test_humanplayer ${SOURCES} ${CMAKE_SOURCE_DIR}/tests/test_humanplayer.cpp)
target_link_libraries(test_humanplayer gtest gtest_main)
add_test(NAME HumanPlayerTest COMMAND test_humanplayer)

add_executable(test_playloop ${SOURCES} ${CMAKE_SOURCE_DIR}/tests/test_playloop.cpp)
target_link_libraries(test_playloop gtest gtest_main)
add_test(NAME PlayLoopTest COMMAND test_playloop)