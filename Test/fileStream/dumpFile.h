#ifndef _DUMPFILE_H
#define _DUMPFILE_H
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <iomanip>
#include <time.h>
#include <stdlib.h>
#include <pthread.h>

using namespace std;
class dumpFile
{
public:
    dumpFile(std::string fileName = std::string("dumpfile"),std::string filePath =  std::string("/sn/log"), unsigned long long disksize = static_cast<unsigned long long>(100*1024*1024));
    virtual ~dumpFile();
    bool setFileName(std::string fileName);
    bool setPathName(std::string filePath);
    bool setDiskFreeSize(int size = 100*1024*1024);
    bool isDumping();
    bool openFile(std::string& file, std::string& error);
    bool out(const char* buf);
    bool closeFile();
    static dumpFile* getInstance();
private:
    void getLock()
    {
        pthread_mutex_lock(&m_dumpFile_mutex);
    }
    void releaseLock()
    {
        pthread_mutex_unlock(&m_dumpFile_mutex);
    }
private:
    // singleton
    static dumpFile* _instance;
    unsigned long long m_diskFreeSize;
    std::string m_fileName;
    std::string m_filePath;
    ofstream foutForDumpFile;
    pthread_mutex_t  m_dumpFile_mutex;

};

#endif

