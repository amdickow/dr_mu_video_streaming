#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
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
    void Progress(double current, double total);
    
private slots:
    void on_refreshButton_released();

private:
    Ui::MainWindow *ui;
    MainController *controller;

};

#endif // MAINWINDOW_H
