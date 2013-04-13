#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QProgressDialog>
#include <QStringListModel>
#include "MainController.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void progress(qint64 value, qint64 total);
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
    QProgressDialog *progressDialog;
    int currentSlugSelection;

};

#endif // MAINWINDOW_H
