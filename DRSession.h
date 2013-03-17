#ifndef DRSESSION_H
#define DRSESSION_H

#include <stdio.h>
#include <string>
#include "curl/curl.h"

//#define DEBUG_WRITE_DATA_TO_FILE
#define DEBUG_READ_DATA_FROM_FILE

class DRSession
{
public:
    DRSession(bool saveToFile = false);
    ~DRSession();

    /**
     * Initialize the session
     *
     * /return Boolean  success/failure
     **/
    bool Init();

    /**
     * Setup the session
     *
     * /return Boolean  success/failure
     */
    bool Setup(std::string url);

    /**
     * Execute the session
     *
     * /return char*  Pointer to fetched data
     */
    char *Execute();

    /**
     * Set progress callback
     *
     * /brief Set progress callback, that will be called repeatedly during the
     *        execution of the curl session.
     *        The progress callback should follow this format:
     *        int prog_cb(void *, double, double, double, double)
     *
     * /param callback  Reference to the progress callback
     */
    void SetProgressCallback(void *callback);

    /**
     * Data callback
     *
     * /brief Set data callback, that will be called data is ready to be
     *        consumed e.g. due to curl session downloading.
     *        The data callback should follow this format:
     *        size_t data_cb(void *, size_t, size_t, void *)
     *
     * /param callback  Reference to the progress callback
     */
    void SetDataCallback(void *callback);

    /// Curl session
    CURL *curl;
    /// Used for the progress callback
    double lastRunTime;

    /// Data store for the data read
    char* memory;

    /// Number of bytes of data read
    size_t memorySize;

    FILE *fileHandle;

    std::string fileName;

private:
    void Clean();
    void BuildFileName(std::string url);

    void* progress_cb;
    void* data_cb;
    std::string url;
    bool toFile;



#ifdef DEBUG_WRITE_DATA_TO_FILE
    void DumpToFile();
#endif

#ifdef DEBUG_READ_DATA_FROM_FILE
    char* ReadFromFile(size_t *size);
#endif

};

#endif // DRSESSION_H
