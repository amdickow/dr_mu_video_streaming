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
#include "ResourceModel.h"
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

    void getSlugs();
    void getVideos(int index);
    void getResourceUriBitrates(int index);
    void getResource(int index);

signals:
    void actionProgress(qint64 value, qint64 total);
    void slugsChanged(QStringListModel *model);
    void videosChanged(QStringListModel *model, const QString &header);
    void downloaded();

public slots:
    void slugsDownloadDone(QByteArray *data);
    void videosDownloadDone(QByteArray *data);
    void resourceUriDownloadDone(QByteArray *data);
    void resourceDownloadDone();
    void dataReadProgress(qint64 bytesRead, qint64 totalKb);

private:
    void updateSlugsModel(QList<QString>& list);
    void updateVideoModel(QList<QString>& list);
    void startDownload(DRSession *session);

    ControllerState state;
    int selectedSlugIndex;
    int selectedVideoIndex;
    int selectedBitrateIndex;
    QList<DRSession*> sessionList;
    QList<QThread*> threadList;
    QStringListModel* slugsListModel;
    QStringListModel* videoListModel;
    SlugModel *slugsModel;
    VideoModel * videoModel;
    ResourceModel *resourceModel;
};

#endif // MAINCONTROLLER_H
