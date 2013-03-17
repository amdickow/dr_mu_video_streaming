#include "MainWindow.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    IMainController(),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    controller = new MainController(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::Progress(double current, double total)
{


}

void MainWindow::on_refreshButton_released()
{
    controller->getProgramSeries();
}
