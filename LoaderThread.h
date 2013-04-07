#ifndef LOADERTHREAD_H
#define LOADERTHREAD_H

#include <QThread>

class LoaderThread : public QThread
{
    Q_OBJECT

    protected:
        void run();

    signals:
        void done();
};

#endif // LOADERTHREAD_H
