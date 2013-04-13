#include <QObject>
#include "MainController.h"
#include "DRSession.h"
#include "SlugModel.h"
#include "VideoModel.h"
#include "ResourceModel.h"
#include <QByteArray>
#include <QThread>


using namespace std;

MainController::MainController() :
    state(MainController::kIdle),
    selectedSlugIndex(-1),
    selectedVideoIndex(-1),
    selectedBitrateIndex(-1),
    slugsListModel(0),
    videoListModel(0),
    slugsModel(0),
    videoModel(0) {
}

MainController::~MainController() {
    if (slugsModel) delete slugsModel;
    if (videoModel) delete videoModel;
}

void MainController::getSlugs()
{
    DRSession* session = new DRSession();

    connect(session, SIGNAL(done(QByteArray*)),
            this, SLOT(slugsDownloadDone(QByteArray*)), Qt::AutoConnection);

    connect(session, SIGNAL(readProgress(qint64, qint64)),
            this, SLOT(dataReadProgress(qint64, qint64)), Qt::AutoConnection);

    session->setup(QString("http://www.dr.dk/nu/api/programseries"));

    startDownload(session);
}

void MainController::slugsDownloadDone(QByteArray *data) {
    slugsModel = new SlugModel();
    slugsModel->create(data,0);
    slugsModel->process();
    slugsModel->print();

    updateSlugsModel(slugsModel->getTitles());

    slugsChanged(slugsListModel);

    // TODO clean the QByteArray passed from the signal
}

void MainController::updateSlugsModel(QList<QString>& list)
{
    if(!list.empty()) {
        if(!slugsListModel) {
            slugsListModel = new QStringListModel(list);
        } else {
            slugsListModel->setStringList(list);
        }
    }
}

void MainController::getVideos(int index)
{
    DRSession* session = new DRSession();
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

void MainController::videosDownloadDone(QByteArray *data) {

    videoModel = new VideoModel();
    videoModel->create(data,0);
    videoModel->process();
    videoModel->print();

    updateVideoModel(videoModel->getTitles());

    videosChanged(videoListModel, slugsModel->getTitleAt(selectedSlugIndex));
}


void MainController::updateVideoModel(QList<QString>& list)
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
void MainController::getResourceUriBitrates(int index) {
    DRSession* session = new DRSession();
    const QString videoUrl = videoModel->getVideoResourceUrlAt(index);

    selectedVideoIndex = index;

    connect(session, SIGNAL(done(QByteArray*)),
            this, SLOT(resourceUriDownloadDone(QByteArray*)));

    connect(session, SIGNAL(readProgress(qint64, qint64)),
            this, SLOT(dataReadProgress(qint64, qint64)));

    session->setup(videoUrl);

    startDownload(session);
}

void MainController::resourceUriDownloadDone(QByteArray *data) {
    resourceModel = new ResourceModel();
    resourceModel->create(data,0);
    resourceModel->process();
    resourceModel->print();

    getResource((int)2);
}

void MainController::getResource(int index) {
    DRSession* session = new DRSession();
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

void MainController::resourceDownloadDone() {
    qDebug("DEBUG: resourceDownloadDone() >>\n");
    downloaded();
}

void MainController::dataReadProgress(qint64 bytesRead, qint64 totalKb) {
    actionProgress(bytesRead,totalKb);
}

void MainController::startDownload(DRSession *session) {
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

