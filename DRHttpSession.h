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

class DRHttpSession : public QObject
{
    Q_OBJECT
public:
    DRHttpSession(bool saveToFile = false);
    ~DRHttpSession();

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



#ifndef DEBUG_READ_DATA_FROM_FILE
public slots:
    /**
     * Execute the session
     *
     * Calling this method will initiate the downloading and
     * during the process the progress signal will be sent indication progress
     */
    void execute();
    void httpFinished();
    void updateDataReadProgress(qint64 bytesRead, qint64 totalBytes);
#endif

signals:
    void error(QString error);
    /**
     * @brief done
     *
     * This is invoked when downloading is done
     *
     * @param data  downloaded data
     */
    void done(QByteArray *data);
    void readProgress(qint64 bytesRead, qint64 totalKb);
    /**
     * @brief finished
     *
     * This is invoked once the download session has completed
     */
    void finished();

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
