#ifndef MAINCONTROLLER_H
#define MAINCONTROLLER_H

#include <QObject>
#include <QByteArray>
#include <QString>
#include <QList>
#include <QStringListModel>
#include "IMainController.h"
#include "SlugModel.h"
#include "VideoModel.h"
#include "DRSession.h"

class MainController : public QObject
{
    Q_OBJECT

public:
    MainController(IMainController *client);
    ~MainController();

    enum ControllerState {
        kIdle,
        kRunning
    };

    void getProgramSeries();

    void getProgramDetails(int index);

public slots:
    void programsDownloadDone(QByteArray *data);
    void videoDownloadDone(QByteArray *data);

private:
    MainController();   // disable default constructor

    void updateSlugsModel(QList<QString>& list);
    void updateVideoModel(QList<QString>& list);

    IMainController *client;
    ControllerState state;
    int selectedVideoIndex;
    QList<DRSession*> sessionList;
    QStringListModel* slugsListModel;
    QStringListModel* videoListModel;
    SlugModel *slugsModel;
    VideoModel * videoModel;
};

#endif // MAINCONTROLLER_H
