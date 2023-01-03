//
// Created by anmar on 9/18/2022.
//

#ifndef TEST_APPLICATION_H
#define TEST_APPLICATION_H

#include <SphynxApplication.h>
#include <log.h>

class TestApplication : public Sphynx::Application {
public:
    TestApplication(const std::string& name, const std::string& version);
    int run() override;

};

#endif
