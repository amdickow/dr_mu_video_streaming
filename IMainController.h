#ifndef IMAINCONTROLLER_H
#define IMAINCONTROLLER_H

class QString;
class QStringListModel;
class IMainController
{
public:

    virtual void Progress(double current, double total) = 0;
    virtual void SlugsChanged(QStringListModel *model) = 0;
    virtual void VideosChanged(QStringListModel *model, QString *header) = 0;

};

#endif // IMAINCONTROLLER_H
