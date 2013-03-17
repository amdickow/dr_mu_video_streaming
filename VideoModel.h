#ifndef VIDEOMODEL_H
#define VIDEOMODEL_H

#include <string>

#include "libjson/libjson.h"

#include "BaseModel.h"

class VideoModel : public BaseModel
{
public:
    VideoModel();
    VideoModel(const char* data);

    unsigned int GetId();
    std::string *GetDescription();
    std::string *GetTitle();
    std::string *GetVideoManifestUrl();
    std::string *GetVideoResourceUrl();

    void Print();

    virtual void ProcessJson(JSONNODE *node);

private:
    unsigned int id;
    std::string description;
    std::string title;
    std::string videoManifestUrl;
    std::string videoResourceUrl;
};

#endif // VIDEOMODEL_H
