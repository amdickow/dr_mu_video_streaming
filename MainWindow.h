#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStringListModel>
#include "MainController.h"
#include "IMainController.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow, public IMainController
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    /// Interface provided by IMainController
    void progress(double current, double total);

    void slugsChanged(QStringListModel *model);

    void videosChanged(QStringListModel *model, const QString &header);


    
private slots:
    void on_refreshButton_released();

    void on_actionAbout_triggered();


    void on_slugsView_clicked(const QModelIndex &index);

    void on_fetchButton_released();

private:
    Ui::MainWindow *ui;
    MainController *controller;
    int currentSlugSelection;

};

#endif // MAINWINDOW_H
