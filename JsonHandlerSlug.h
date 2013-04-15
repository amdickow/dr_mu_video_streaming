#ifndef SLUGMODEL_H
#define SLUGMODEL_H

#include <QJsonArray>
#include <QString>
#include <QList>



#include "JsonHandlerBase.h"

class JsonHandlerSlug : public JsonHandlerBase
{
public:
    JsonHandlerSlug();

    const QString &getSlugAt(int index);
    const QString &getTitleAt(int index);
    int getSize();

    QList<QString> &getSlugs();
    QList<QString> &getTitles();

    void print();

    virtual void processJsonArray(const QJsonArray &node);

private:
    QList<QString> slugs;
    QList<QString> titles;
};

#endif // SLUGMODEL_H
