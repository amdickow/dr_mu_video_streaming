#ifndef MAINCONTROLLER_H
#define MAINCONTROLLER_H

#include <QObject>
#include <QByteArray>
#include <QString>
#include <QList>
#include <QStringListModel>
#include <QProgressDialog>
#include <QThread>
#include "SlugModel.h"
#include "VideoModel.h"
#include "DRSession.h"

class MainController : public QObject
{
    Q_OBJECT

public:
    MainController();
    ~MainController();

    enum ControllerState {
        kIdle,
        kRunning
    };

    void getProgramSeries();

    void getProgramDetails(int index);

signals:
    void actionProgress(qint64 value, qint64 total);
    void slugsChanged(QStringListModel *model);
    void videosChanged(QStringListModel *model, const QString &header);

public slots:
    void programsDownloadDone(QByteArray *data);
    void videoDownloadDone(QByteArray *data);
    void dataReadProgress(qint64 bytesRead, qint64 totalKb);

private:
    void updateSlugsModel(QList<QString>& list);
    void updateVideoModel(QList<QString>& list);
    void startDownload(DRSession *session);

    ControllerState state;
    int selectedVideoIndex;
    QList<DRSession*> sessionList;
    QList<QThread*> threadList;
    QStringListModel* slugsListModel;
    QStringListModel* videoListModel;
    SlugModel *slugsModel;
    VideoModel * videoModel;
};

#endif // MAINCONTROLLER_H
