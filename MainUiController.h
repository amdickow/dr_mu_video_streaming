#ifndef MAINCONTROLLER_H
#define MAINCONTROLLER_H

#include <QObject>
#include <QByteArray>
#include <QString>
#include <QList>
#include <QStringListModel>
#include <QProgressDialog>
#include <QThread>
#include "JsonHandlerSlug.h"
#include "JsonHandlerVideo.h"
#include "JsonHandlerResource.h"
#include "DRHttpSession.h"

class MainUiController : public QObject
{
    Q_OBJECT

public:
    MainUiController();
    ~MainUiController();

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
    void updateJsonHandlerVideo(QList<QString>& list);
    void startDownload(DRHttpSession *session);

    ControllerState state;
    int selectedSlugIndex;
    int selectedVideoIndex;
    int selectedBitrateIndex;
    QList<DRHttpSession*> sessionList;
    QList<QThread*> threadList;
    QStringListModel* slugsListModel;
    QStringListModel* videoListModel;
    JsonHandlerSlug *slugsModel;
    JsonHandlerVideo * videoModel;
    JsonHandlerResource *resourceModel;
};

#endif // MAINCONTROLLER_H
