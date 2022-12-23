//
// Created by anmar on 9/18/2022.
//

#include <TestApplication.h>
#include <cassert>

int main(int argc, char *argv[])
{
    TestApplication application("Exam: BlockOut", "1.0");
    assert(application.parseArguments(argc, argv) != EXIT_FAILURE);
    assert(application.initialize() != EXIT_FAILURE);
    return application.run();
}
