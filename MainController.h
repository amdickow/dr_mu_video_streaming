#ifndef MAINCONTROLLER_H
#define MAINCONTROLLER_H

#include "IMainController.h"
#include "DRSession.h"
#include <QString>
#include <QList>
#include <QStringListModel>

class MainController
{
public:
    MainController(IMainController *client);

    enum ControllerState {
        kIdle,
        kRunning
    };

    void getProgramSeries();

    void getProgramDetails(int index);

private:
    MainController();   // disable default constructor

    void UpdateSlugsModel(QList<QString>& list);
    void UpdateVideoModel(QList<QString>& list);

    IMainController *client;
    ControllerState state;
    QList<DRSession*> sessionList;
    QStringListModel* slugsListModel;
    QStringListModel* videoListModel;
};

#endif // MAINCONTROLLER_H
