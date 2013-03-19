#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <QString>

#include "DRSession.h"

#include "curl/curl.h"

using namespace std;

#define MINIMAL_PROGRESS_GRANULARITY        3

#ifdef FEATURE_LIMIT_DOWNLOAD_SIZE
#define MAXIMUM_DOWNLOAD_SIZE               20000
#endif

extern "C"
int curl_data_progress_callback(void *self, double dl_total, double dl_now, double ul_total, double ul_now) {
    DRSession *thiz = (DRSession *)self;
    double cur_time = 0;

    curl_easy_getinfo(thiz->curl, CURLINFO_TOTAL_TIME, &cur_time);

    if ((cur_time - thiz->lastRunTime) >= MINIMAL_PROGRESS_GRANULARITY) {
        thiz->lastRunTime = cur_time;
        printf("DEBUG: data_progress_callback() TOTAL_TIME= %f \n",cur_time);
    }

    printf("DEBUG: data_progress_callback() PROGRESS: %g of %g\n", dl_now, dl_total);

#ifdef FEATURE_LIMIT_DOWNLOAD_SIZE
    if (dl_now > MAXIMUM_DOWNLOAD_SIZE) {
        return 1;
    }
#endif

    return 0;
}

extern "C"
size_t curl_write_to_memory_callback(void *buffer, size_t size, size_t nmemb, void *self) {
    size_t realsize = size * nmemb;
    DRSession *thiz = (DRSession *)self;

    thiz->memory = (char *)realloc(thiz->memory, thiz->memorySize + realsize + 1);
    if(thiz->memory == NULL) {
        // out of memory!
        printf("DEBUG: not enough memory (realloc returned NULL)\n");
        return 0;
    }

    memcpy(&(thiz->memory[thiz->memorySize]), buffer, realsize);
    thiz->memorySize += realsize;
    thiz->memory[thiz->memorySize] = 0;

    return realsize;
}

extern "C"
size_t curl_write_to_file_callback(void *buffer, size_t size, size_t nmemb, void *self)
{
    DRSession *thiz = (DRSession *)self;
    if(thiz && !thiz->fileHandle) {
        thiz->fileHandle = fopen(thiz->fileName.c_str(), "wb");

        if(!thiz->fileHandle) {
            return -1; /* failure, can't open file to write */
        }
    }
    return fwrite(buffer, size, nmemb, thiz->fileHandle);
}


DRSession::DRSession(bool saveToFile) :
    curl(0),
    lastRunTime(0),
    memory(0),
    memorySize(0),
    fileHandle(0),
    progress_cb(0),
    data_cb(0),
    toFile(saveToFile) {
    curl_global_init(CURL_GLOBAL_ALL);
}

DRSession::~DRSession() {
    Clean();
}

void DRSession::Clean() {
    printf("DEBUG >> Clean() this->memorySize=%d\n",(int)this->memorySize);
    if (this->memorySize) {
        free(this->memory);
        this->memory = 0;
        this->memorySize = 0;
    }

    if (this->curl) {
        curl_easy_cleanup(curl);
        this->curl = 0;
    }
}
#ifdef DEBUG_READ_DATA_FROM_FILE
bool DRSession::Init() {
    return true;
}
#else
bool DRSession::Init() {

    curl = curl_easy_init();

    return curl?true:false;
}
#endif

#ifdef DEBUG_READ_DATA_FROM_FILE
bool DRSession::Setup(std::string url) {
    if (!url.empty()) {
        this->url = url;
        return true;
    }
    return false;
}
#else
bool DRSession::Setup(std::string url) {
    if (curl && !url.empty()) {
        this->url = url;
        curl_easy_setopt(curl, CURLOPT_URL, (const char*) url.c_str());

        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);


        // setup progress callbacks
        curl_easy_setopt(curl, CURLOPT_PROGRESSFUNCTION, curl_data_progress_callback);
        curl_easy_setopt(curl, CURLOPT_PROGRESSDATA, (void*)this);
        curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 0L);

        if (toFile) {
            BuildFileName(url);
            // setup data callbacks
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, curl_write_to_file_callback);
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)this);

            /* Switch on full protocol/debug output */
            curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
        } else {
            // setup data callbacks
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, curl_write_to_memory_callback);
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)this);
        }

        // provide user-agent if requested by the server (possibly not needed)
        curl_easy_setopt(curl, CURLOPT_USERAGENT, "libcurl-agent/1.0");

        return true;
    }
    return false;
}
#endif

#ifdef DEBUG_READ_DATA_FROM_FILE
char *DRSession::Execute() {
    size_t size = 0;
    char * data = ReadFromFile(&size);

    if (size) {
        return data;
    }
    return 0;
}
#else
char *DRSession::Execute() {
    CURLcode result;

    this->memory = (char *)malloc(1);
    this->memorySize = 0;

    result = curl_easy_perform(this->curl);

    printf("DEBUG: Execute() - result: %d\n", (int)result);

    if (result != CURLE_OK) {
        printf("DEBUG: curl_easy_perform() failed: %s\n", curl_easy_strerror(result));
        return 0;
    } else {
        if (toFile) {
            return strdup(this->fileName.c_str());
        } else {
        #ifdef DEBUG_WRITE_DATA_TO_FILE
            DumpToFile();
        #endif
        return (char*)this->memory;
        }
    }
}
#endif


/**
 * @brief DRSession::SetProgressCallback
 * @param callback
 * @todo IMPLEMENT ME
 */
void DRSession::SetProgressCallback(void *callback) {
    (void)callback;
}

/**
 * @brief DRSession::SetDataCallback
 * @param callback
 * @todo IMPLEMENT ME
 */
void DRSession::SetDataCallback(void *callback) {
    (void)callback;
}

void DRSession::BuildFileName(std::string url) {
    int delimIdx = url.find_last_of("/");
    fileName.append(url.substr(delimIdx+1));

    printf("DEBUG: BuildFileName() fileName=%s\n", fileName.c_str());

    delimIdx = fileName.find_last_of("?");
    fileName.resize(delimIdx);

    printf("DEBUG: BuildFileName() fileName=%s\n", fileName.c_str());
}

#ifdef DEBUG_WRITE_DATA_TO_FILE
void DRSession::DumpToFile() {
    FILE* file = 0;

    string fileStr = string("curlDump");
    int delimIdx = url.find_last_of("/");
    fileStr.append(url.substr(delimIdx+1));
    fileStr.append(".txt");

    file = fopen(fileStr.c_str(), "w");

    printf("DEBUG: DumpToFile() pFile=%d\n", file);

    if (file) {
        fprintf(file, "%s\n", (const char*)this->memory);
        fclose(file);
    }
}
#endif

#ifdef DEBUG_READ_DATA_FROM_FILE
char * DRSession::ReadFromFile(size_t *size) {
    char * buffer = 0;
    FILE * file = 0;
    string fileStr = string("/home/dickow/git_wa/DRVideoGrabber/test/curlDump");
    int delimIdx = url.find_last_of("/");
    fileStr.append(url.substr(delimIdx+1));
    fileStr.append(".txt");
    file = fopen(fileStr.c_str() , "r");

    printf("DEBUG: fileStr=%s\n", fileStr.c_str());

    if (file==0) {
        printf("DEBUG: fopen() error\n");
        *size = 0;
    } else {
        long lSize;
        size_t result;

        // obtain file size:
        fseek (file , 0 , SEEK_END);
        lSize = ftell (file);
        rewind (file);

        // allocate memory to contain the whole file:
        buffer = (char*) malloc (sizeof(char)*lSize);
        if (buffer == NULL) {fputs ("Memory error",stderr); exit (2);}

        // copy the file into the buffer:
        result = fread (buffer,1,lSize,file);
        if (result != (size_t)lSize) {
            printf("DEBUG: fread() error\n");
            *size = 0;
        } else {
            *size = (size_t)lSize;
        }
        fclose(file);
    }
    return buffer;
}
#endif
