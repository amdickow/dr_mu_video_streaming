#include "MainController.h"
#include "DRSession.h"
#include "SlugModel.h"
#include "VideoModel.h"


using namespace std;

MainController::MainController(IMainController *client) :
    slugsListModel(0),
    videoListModel(0)
{
     this->client = client;
}


void MainController::getProgramSeries()
{
    DRSession* session = new DRSession();
    SlugModel* slugsModel = new SlugModel();

    sessionList.push_back(session);

    session->Init();
    session->Setup(string("http://www.dr.dk/nu/api/programseries"));

    slugsModel->Process(session->Execute());
    slugsModel->Print();
    UpdateSlugsModel(slugsModel->GetSlugs());

    client->SlugsChanged(slugsListModel);
}

void MainController::getProgramDetails(int index)
{
    DRSession* session = new DRSession();
    VideoModel* videoModel = new VideoModel();
    QString program = (QString) slugsListModel->stringList().at(index);

    sessionList.push_back(session);

    string slugUrl = string("http://www.dr.dk/nu/api/programseries/");
    slugUrl.append(program.toStdString());
    slugUrl.append("/videos");

    session->Init();
    session->Setup(slugUrl);
    videoModel->Process(session->Execute());
    videoModel->Print();

    client->VideosChanged(0, videoModel->GetTitle());
}

void MainController::UpdateSlugsModel(QList<QString>& list)
{
    if(!list.empty()) {
        if(!slugsListModel) {
            slugsListModel = new QStringListModel(list);
        } else {
            slugsListModel->setStringList(list);
        }
    }
}

void MainController::UpdateVideoModel(QList<QString>& list)
{
    if(!list.empty()) {
        if(!videoListModel) {
            videoListModel = new QStringListModel(list);
        } else {
            videoListModel->setStringList(list);
        }
    }
}
