#include <QObject>
#include "MainController.h"
#include "DRSession.h"
#include "SlugModel.h"
#include "VideoModel.h"
#include <QByteArray>


using namespace std;

MainController::MainController(IMainController *client) :
    state(MainController::kIdle),
    selectedVideoIndex(-1),
    slugsListModel(0),
    videoListModel(0),
    slugsModel(0),
    videoModel(0)
{
     this->client = client;
}

MainController::~MainController() {
    if (slugsModel) delete slugsModel;
    if (videoModel) delete videoModel;
}


void MainController::getProgramSeries()
{
    DRSession* session = new DRSession();

    connect(session, SIGNAL(done(QByteArray*)),
            this, SLOT(programsDownloadDone(QByteArray*)));

    session->setup(QString("http://www.dr.dk/nu/api/programseries"));
    session->execute();
    sessionList.push_back(session);
}

void MainController::programsDownloadDone(QByteArray *data) {
    slugsModel = new SlugModel();
    slugsModel->create(data,0);
    slugsModel->process();
    slugsModel->print();

    updateSlugsModel(slugsModel->getTitles());
    client->slugsChanged(slugsListModel);

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

    session->setup(slugUrl);
    session->execute();
    sessionList.push_back(session);
}

void MainController::videoDownloadDone(QByteArray *data) {
    videoModel = new VideoModel();
    videoModel->create(data,0);
    videoModel->process();
    videoModel->print();

    updateVideoModel(videoModel->getTitles());
    client->videosChanged(videoListModel, slugsModel->getTitleAt(selectedVideoIndex));
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
