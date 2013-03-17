#ifndef SLUGMODEL_H
#define SLUGMODEL_H

#include <string>
#include <vector>

#include "libjson/libjson.h"

#include "BaseModel.h"

class SlugModel : public BaseModel
{
public:
    SlugModel();
    SlugModel(const char* data);

    std::string *Get(int index);
    int GetSize();

    std::vector<std::string> &GetSlugs() {return slugs;}

    void Print();

    virtual void ProcessJson(JSONNODE *node);

private:
    std::vector<std::string> slugs;
};

#endif // SLUGMODEL_H
