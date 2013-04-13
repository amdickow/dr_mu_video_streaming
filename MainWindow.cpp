#include "MainWindow.h"
#include "ui_MainWindow.h"
#include <QProgressDialog>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    currentSlugSelection(-1)
{
    ui->setupUi(this);

    controller = new MainController();
    connect(controller, SIGNAL(slugsChanged(QStringListModel*)),
            this, SLOT(slugsChanged(QStringListModel*)));
    connect(controller, SIGNAL(videosChanged(QStringListModel*,QString)),
            this, SLOT(videosChanged(QStringListModel*,QString)));

    progressDialog = new QProgressDialog(this);
    progressDialog->setAutoClose(false);
    connect(controller, SIGNAL(actionProgress(qint64,qint64)),
            this, SLOT(progress(qint64,qint64)));

    ui->fetchButton->setEnabled(false);
    ui->downloadButton->setEnabled(false);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::progress(qint64 value, qint64 total)
{
    qDebug("DEBUG: progress() value: %d total: %d", value, total);
    if (this->progressDialog) {
        if (this->progressDialog->isVisible()) {
            this->progressDialog->setMaximum(total);
            if (value) {
                this->progressDialog->setValue(value);
            } else {
                this->progressDialog->setValue(0);
            }
        }
    }
}

void MainWindow::slugsChanged(QStringListModel *model)
{
    if (progressDialog) {
        progressDialog->hide();
    }
    ui->slugsView->setModel(model);
    ui->refreshButton->setEnabled(true);
}

void MainWindow::videosChanged(QStringListModel *model, const QString &header)
{
    if (progressDialog) {
        progressDialog->hide();
    }
    ui->slugHeader->setText(header);
    ui->downloadView->setModel(model);
}

void MainWindow::on_refreshButton_released()
{
    if (progressDialog) {
        progressDialog->setWindowTitle(tr("REFRESH"));
        progressDialog->setLabelText("Refreshing TV-show list");
        progressDialog->show();
    }
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
    if (progressDialog) {
        progressDialog->setWindowTitle(tr("FETCHING"));
        //progressDialog->setLabelText(tr("Fecthing episodes for %s",slugsModel->getTitleAt(selectedVideoIndex).toUtf8()));
        progressDialog->show();
    }
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
