//
// Created by anmar on 9/18/2022.
//

#ifndef LAB1_LAB2APPLICATION_H
#define LAB1_LAB2APPLICATION_H

#include <SphynxApplication.h>

class TestApplication : public Sphynx::Application {
private:

public:
    TestApplication(const std::string& name, const std::string& version);
    int run() override;

};

#endif //LAB1_LAB2APPLICATION_H
