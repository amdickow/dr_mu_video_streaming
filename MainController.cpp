#include <QObject>
#include "MainController.h"
#include "DRSession.h"
#include "SlugModel.h"
#include "VideoModel.h"
#include <QByteArray>
#include <QThread>


using namespace std;

MainController::MainController() :
    state(MainController::kIdle),
    selectedVideoIndex(-1),
    slugsListModel(0),
    videoListModel(0),
    slugsModel(0),
    videoModel(0) {
}

MainController::~MainController() {
    if (slugsModel) delete slugsModel;
    if (videoModel) delete videoModel;
}

void MainController::getProgramSeries()
{
    DRSession* session = new DRSession();

    connect(session, SIGNAL(done(QByteArray*)),
            this, SLOT(programsDownloadDone(QByteArray*)), Qt::AutoConnection);

    connect(session, SIGNAL(readProgress(qint64, qint64)),
            this, SLOT(dataReadProgress(qint64, qint64)), Qt::AutoConnection);

    session->setup(QString("http://www.dr.dk/nu/api/programseries"));

    startDownload(session);
}

void MainController::programsDownloadDone(QByteArray *data) {
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

void MainController::getProgramDetails(int index)
{
    DRSession* session = new DRSession();
    const QString program = slugsModel->getSlugAt(index);
    QString slugUrl = QString("http://www.dr.dk/nu/api/programseries/");

    slugUrl.append(program);
    slugUrl.append("/videos");

    selectedVideoIndex = index;

    connect(session, SIGNAL(done(QByteArray*)),
            this, SLOT(videoDownloadDone(QByteArray*)));

    connect(session, SIGNAL(readProgress(qint64, qint64)),
            this, SLOT(dataReadProgress(qint64, qint64)));

    session->setup(slugUrl);

    startDownload(session);
}

void MainController::videoDownloadDone(QByteArray *data) {

    videoModel = new VideoModel();
    videoModel->create(data,0);
    videoModel->process();
    videoModel->print();

    updateVideoModel(videoModel->getTitles());

    videosChanged(videoListModel, slugsModel->getTitleAt(selectedVideoIndex));
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

