#include "MainController.h"
#include "DRSession.h"
#include "SlugModel.h"

using namespace std;

MainController::MainController(IMainController *client)
{
     this->client = client;
}


vector<string> &MainController::getProgramSeries()
{
    DRSession* session = new DRSession();
    SlugModel* slugsModel = new SlugModel();

    session->Init();
    session->Setup(string("http://www.dr.dk/nu/api/programseries"));

    slugsModel->Process(session->Execute());
    slugsModel->Print();

    return slugsModel->GetSlugs();
}
