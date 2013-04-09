#include "MainWindow.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    IMainController(),
    ui(new Ui::MainWindow),
    currentSlugSelection(-1)
{
    ui->setupUi(this);

    controller = new MainController(this);
    ui->fetchButton->setEnabled(false);
    ui->downloadButton->setEnabled(false);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::Progress(double current, double total)
{

}

void MainWindow::SlugsChanged(QStringListModel *model)
{
    ui->slugsView->setModel(model);
    ui->refreshButton->setEnabled(true);
}

void MainWindow::VideosChanged(QStringListModel *model, QString *header)
{
    ui->slugHeader->setText(*header);
}



void MainWindow::on_refreshButton_released()
{
    ui->refreshButton->setEnabled(false);
    controller->getProgramSeries();
}

void MainWindow::on_slugsView_clicked(const QModelIndex &index)
{
    ui->fetchButton->setEnabled(true);

    //ensure that we are not already processing
    if(0 > currentSlugSelection) {
        currentSlugSelection = index.row();
    }
}

void MainWindow::on_fetchButton_released()
{
    ui->fetchButton->setEnabled(false);
    // shouldn't be nescessary but let's check anyway
    if(currentSlugSelection >= 0) {
        controller->getProgramDetails(currentSlugSelection);
    }
}


void MainWindow::on_actionAbout_triggered()
{
    // About was clicked.. show something()
}
