#include <QObject>
#include "MainUiController.h"
#include "DRHttpSession.h"
#include "JsonHandlerSlug.h"
#include "JsonHandlerVideo.h"
#include "JsonHandlerResource.h"
#include <QByteArray>
#include <QThread>


using namespace std;

MainUiController::MainUiController() :
    state(MainUiController::kIdle),
    selectedSlugIndex(-1),
    selectedVideoIndex(-1),
    selectedBitrateIndex(-1),
    slugsListModel(0),
    videoListModel(0),
    slugsModel(0),
    videoModel(0) {
}

MainUiController::~MainUiController() {
    if (slugsModel) slugsModel->kill();
    if (videoModel) videoModel->kill();
}

void MainUiController::getSlugs()
{
    DRHttpSession* session = new DRHttpSession();

    connect(session, SIGNAL(done(QByteArray*)),
            this, SLOT(slugsDownloadDone(QByteArray*)), Qt::AutoConnection);

    connect(session, SIGNAL(readProgress(qint64, qint64)),
            this, SLOT(dataReadProgress(qint64, qint64)), Qt::AutoConnection);

    session->setup(QString("http://www.dr.dk/nu/api/programseries"));

    startDownload(session);
}

void MainUiController::slugsDownloadDone(QByteArray *data) {
    slugsModel = new JsonHandlerSlug();
    slugsModel->create(data);
    slugsModel->process();
    slugsModel->print();

    updateSlugsModel(slugsModel->getTitles());

    slugsChanged(slugsListModel);

    // TODO clean the QByteArray passed from the signal
}

void MainUiController::updateSlugsModel(QList<QString>& list)
{
    if(!list.empty()) {
        if(!slugsListModel) {
            slugsListModel = new QStringListModel(list);
        } else {
            slugsListModel->setStringList(list);
        }
    }
}

void MainUiController::getVideos(int index)
{
    DRHttpSession* session = new DRHttpSession();
    const QString program = slugsModel->getSlugAt(index);
    QString slugUrl = QString("http://www.dr.dk/nu/api/programseries/");

    slugUrl.append(program);
    slugUrl.append("/videos");

    selectedSlugIndex = index;

    connect(session, SIGNAL(done(QByteArray*)),
            this, SLOT(videosDownloadDone(QByteArray*)));

    connect(session, SIGNAL(readProgress(qint64, qint64)),
            this, SLOT(dataReadProgress(qint64, qint64)));

    session->setup(slugUrl);

    startDownload(session);
}

void MainUiController::videosDownloadDone(QByteArray *data) {

    videoModel = new JsonHandlerVideo();
    videoModel->create(data);
    videoModel->process();
    videoModel->print();

    updateJsonHandlerVideo(videoModel->getTitles());

    videosChanged(videoListModel, slugsModel->getTitleAt(selectedSlugIndex));
}


void MainUiController::updateJsonHandlerVideo(QList<QString>& list)
{
    if(!list.empty()) {
        if(!videoListModel) {
            videoListModel = new QStringListModel(list);
        } else {
            videoListModel->setStringList(list);
        }
    }
}


// TODO this method should return bitrates for the different downloads
//      and this needs to be presented in a dialog to the user to be chosen from
//      on bitrate selected and click on "download" the file will begin downloading
void MainUiController::getResourceUriBitrates(int index) {
    DRHttpSession* session = new DRHttpSession();
    const QString videoUrl = videoModel->getVideoResourceUrlAt(index);

    selectedVideoIndex = index;

    connect(session, SIGNAL(done(QByteArray*)),
            this, SLOT(resourceUriDownloadDone(QByteArray*)));

    connect(session, SIGNAL(readProgress(qint64, qint64)),
            this, SLOT(dataReadProgress(qint64, qint64)));

    session->setup(videoUrl);

    startDownload(session);
}

void MainUiController::resourceUriDownloadDone(QByteArray *data) {
    resourceModel = new JsonHandlerResource();
    resourceModel->create(data);
    resourceModel->process();
    resourceModel->print();

    getResource((int)2);
}

void MainUiController::getResource(int index) {
    DRHttpSession* session = new DRHttpSession();
    const QString downloadUri = resourceModel->getDownloadUri(index);
    QString preparedUri = QString("http://vodfiles.dr.dk/");
    int delimPos = downloadUri.indexOf("CMS/Resources/");
    preparedUri.append(downloadUri.right(delimPos));

    qDebug("DEBUG: getResource() index: %d uri: %s\n", index, qPrintable(preparedUri));

    selectedBitrateIndex = index;

    connect(session, SIGNAL(finished()),
            this, SLOT(resourceDownloadDone()));

    connect(session, SIGNAL(readProgress(qint64, qint64)),
            this, SLOT(dataReadProgress(qint64, qint64)));

    session->setup(preparedUri);

    startDownload(session);
}

void MainUiController::resourceDownloadDone() {
    qDebug("DEBUG: resourceDownloadDone() >>\n");
    downloaded();
}

void MainUiController::dataReadProgress(qint64 bytesRead, qint64 totalKb) {
    actionProgress(bytesRead,totalKb);
}

void MainUiController::startDownload(DRHttpSession *session) {
    QThread* thread = new QThread;
    session->moveToThread(thread);

    //connect(session, SIGNAL(error(QString)), this, SLOT(errorString(QString)));
    connect(thread, SIGNAL(started()), session, SLOT(execute()));
    connect(session, SIGNAL(finished()), thread, SLOT(quit()));
    connect(session, SIGNAL(finished()), session, SLOT(deleteLater()));
    connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
    thread->start(QThread::LowestPriority);

    //sessionList.push_back(session);
}

