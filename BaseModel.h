#ifndef BASEMODEL_H
#define BASEMODEL_H

#include "libjson/libjson.h"

class BaseModel
{
public:
    BaseModel();
    BaseModel(const char* data);

    void Process(const char* data);

protected:
    /// has to be implemented by derivation class
    virtual void ProcessJson(JSONNODE *node) = 0;

    const char* data;
};

#endif // BASEMODEL_H
