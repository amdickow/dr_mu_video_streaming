#ifndef MAINCONTROLLER_H
#define MAINCONTROLLER_H

#include "IMainController.h"
#include <string>
#include <vector>

class MainController
{
public:
    MainController(IMainController *client);

    enum ControllerState {
        kIdle,
        kRunning
    };

    std::vector<std::string> &getProgramSeries();

private:
    MainController();
    IMainController *client;
    ControllerState state;
};

#endif // MAINCONTROLLER_H
