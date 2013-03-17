#include "BaseModel.h"

#include <stdio.h>

BaseModel::BaseModel() : data(0) {}

BaseModel::BaseModel(const char* data) : data(data) {}

void BaseModel::Process(const char* data) {
    printf("DEBUG: BaseModel::Process() >> \n");
    JSONNODE *nodeContent = json_parse(data);

    if (nodeContent) {
        json_index_t childCount = json_size(nodeContent);
        printf("DEBUG:      json_size() childCount=%d\n",(int)childCount);
        this->ProcessJson(nodeContent);
    } else  {
        printf("DEBUG:      Parsing failed!\n");
    }
}
