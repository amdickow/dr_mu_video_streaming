#ifndef RESOURCEMODEL_H
#define RESOURCEMODEL_H

#include <string>
#include <vector>

#include "libjson/libjson.h"

#include "BaseModel.h"

class ResourceModel : public BaseModel
{
public:
    ResourceModel();
    ResourceModel(const char* data);

    unsigned int GetResourceId();
    std::string *GetName();
    std::string *GetDownloadUri(int index);

    void Print();

    virtual void ProcessJson(JSONNODE *node);

private:
    void ProcessLinks(JSONNODE *node);

    unsigned int resId;
    std::string name;
    std::vector<std::string> downloadUri;
};

#endif // RESOURCEMODEL_H
