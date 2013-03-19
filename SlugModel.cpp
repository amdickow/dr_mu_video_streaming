#include "SlugModel.h"

#include <stdio.h>
#include <QString>
//#include <string.h>


#include "libjson/libjson.h"

SlugModel::SlugModel() : BaseModel(0) { }

SlugModel::SlugModel(const char* data) : BaseModel(data) { }

void SlugModel::ProcessJson(JSONNODE *node) {
    JSONNODE_ITERATOR begin = json_begin(node);
    JSONNODE_ITERATOR end   = json_end(node);

    printf("DEBUG: ProcessJson() >>\n");

    while(begin != end) {
        if (json_type(*begin) == JSON_ARRAY ||
            json_type(*begin) == JSON_NODE) {
            ProcessJson(*begin);
        }

        json_char *name = json_name(*begin);

        // look for slug's
        if (strcmp(name, "slug") == 0) {
            json_char *value = json_as_string(*begin);
            slugs.push_back(QString((const char*) value));
            printf("DEBUG: ProcessJson() found slug, value=%s\n", (const char*) value);
            json_free(value);
        }
        json_free(name);
        ++begin;
    }
    //json_free(begin);
    //json_free(end);
}

void SlugModel::Print() {
    printf("DEBUG Print() >>\nslugs.size=%d\n",(int)slugs.size());
    for (QList<QString>::iterator it=slugs.begin(); it != slugs.end(); ++it) {
      printf("slugs: %s \n", qPrintable((QString)*it));
    }
}


QString *SlugModel::Get(int index) {
    if (index < (int)slugs.size()) {
        return (new QString(slugs.at(index)));
    } else {
        return 0;
    }
}


