#ifndef JSONHANDLERBASE_H
#define JSONHANDLERBASE_H

#include <QByteArray>
#include <QJsonDocument>

class JsonHandlerBase
{
public:
    JsonHandlerBase();

    bool create(QByteArray *data, int size);

    void process();

protected:
    /// has to be implemented by derivation class
    virtual void processJsonArray(const QJsonArray &node) = 0;

    QJsonDocument doc;
};

#endif // JSONHANDLERBASE_H
