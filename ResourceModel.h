#ifndef RESOURCEMODEL_H
#define RESOURCEMODEL_H

#include <QJsonArray>
#include <string>
#include <vector>



#include "JsonHandlerBase.h"

class ResourceModel : public JsonHandlerBase
{
public:
    ResourceModel();

    unsigned int getResourceId();
    std::string *getName();
    std::string *getDownloadUri(int index);

    void print();

    virtual void processJsonArray(const QJsonArray &node);

private:
    void processLinks(QJsonObject *node);

    unsigned int resId;
    std::string name;
    std::vector<std::string> downloadUri;
};

#endif // RESOURCEMODEL_H
