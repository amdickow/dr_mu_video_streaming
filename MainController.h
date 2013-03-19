#ifndef MAINCONTROLLER_H
#define MAINCONTROLLER_H

#include "IMainController.h"
#include <QString>
#include <QList>

class MainController
{
public:
    MainController(IMainController *client);

    enum ControllerState {
        kIdle,
        kRunning
    };

    QList<QString> &getProgramSeries();

private:
    MainController();
    IMainController *client;
    ControllerState state;
};

#endif // MAINCONTROLLER_H
