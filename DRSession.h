#ifndef DRSESSION_H
#define DRSESSION_H

#include <QObject>
#include <QByteArray>

#include <QtNetwork/QNetworkAccessManager>
#include <QUrl>

#include <stdio.h>
#include <string>

//#define DEBUG_WRITE_DATA_TO_FILE
//#define DEBUG_READ_DATA_FROM_FILE

class QNetworkReply;

class DRSession : public QObject
{
    Q_OBJECT
public:
    DRSession(bool saveToFile = false);
    ~DRSession();

    /**
     * Clear the session
     *
     * /return Boolean  success/failure
     **/
    bool clear();

    /**
     * Setup the session
     *
     * /return Boolean  success/failure
     */
    bool setup(QString url);

    /**
     * Execute the session
     *
     * /return char*  Pointer to fetched data
     */
    void execute();

#ifndef DEBUG_READ_DATA_FROM_FILE
public slots:
    void httpFinished();
    void updateDataReadProgress(qint64 bytesRead, qint64 totalBytes);
#endif

signals:
    void done(QByteArray *data);

private:
    bool toFile;
    QNetworkReply *reply;
    QUrl url;
    QNetworkAccessManager networkAccessMgr;



#ifdef DEBUG_WRITE_DATA_TO_FILE
    void dumpToFile();
#endif

#ifdef DEBUG_READ_DATA_FROM_FILE
    char* readFromFile(size_t *size);
#endif

};

#endif // DRSESSION_H
