#ifndef IMAINCONTROLLER_H
#define IMAINCONTROLLER_H

class QString;
class QStringListModel;
class IMainController
{
public:

    virtual void progress(double current, double total) = 0;
    virtual void slugsChanged(QStringListModel *model) = 0;
    virtual void videosChanged(QStringListModel *model, const QString &header) = 0;

};

#endif // IMAINCONTROLLER_H
