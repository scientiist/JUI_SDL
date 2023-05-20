# Tests

file(GLOB_RECURSE TEST_SRCS CONFIGURE_DEPENDS "JUI/*.cpp")

# Add source to this project's executable.
add_executable(JUITest ${TEST_SRCS})
target_link_libraries(JUITest PUBLIC JUI)

include_directories("include")

add_test(NAME, "JUITest" COMMAND JUITest)