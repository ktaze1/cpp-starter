#include <catch2/catch_all.hpp>
#include <project.h>

TEST_CASE("echoHello test for Project class", "[Project]") {
    Project project;

    SECTION("Check echoHello() output") {
        std::cout << "Running echoHello test" << std::endl;
        std::string expected_output = "Hello World\n";
        REQUIRE(project.echoHello() == expected_output);
    }
}