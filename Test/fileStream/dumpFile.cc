#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <iomanip>
#include <unistd.h>
#include "dumpFile.h"
#include "wildcardUtils.h"
#include "hlr_log.h"
#include "hlrOMsg.h"

dumpFile* dumpFile::_instance = new dumpFile("dumpfile","/sn/log",static_cast<unsigned long long>(100*1024*1024));

dumpFile::dumpFile(std::string fileName,std::string filePath, unsigned long long disksize)
{
    pthread_mutex_init(&m_dumpFile_mutex, NULL);
    m_fileName.assign(fileName);
    m_filePath.assign(filePath);
    m_diskFreeSize = disksize;
}

dumpFile::~dumpFile()
{
    if(foutForDumpFile.is_open())
    {
        foutForDumpFile.flush();
        foutForDumpFile.close();
    }

    if(_instance != 0)
    {
        delete _instance;
    }

}

dumpFile*  dumpFile::getInstance()
{
    if(_instance == 0)
    {
        _instance = new dumpFile();

        if(_instance == 0)
        {
            return NULL;
        }

    }

    return _instance;
}

bool
dumpFile::setFileName(std::string fileName)
{
    getLock();
    m_fileName.assign(fileName);
    releaseLock();
    return true;
}

bool
dumpFile::setPathName(std::string filePath)
{
    getLock();
    m_filePath.assign(filePath);
    releaseLock();
    return true;
}


bool
dumpFile::setDiskFreeSize(int size)
{
    getLock();
    m_diskFreeSize =static_cast<unsigned long long>(size);
    releaseLock();
    return true;
}


bool
dumpFile::isDumping()
{
    getLock();
    if(foutForDumpFile.is_open())
    {
        releaseLock();
        return true;
    }
    else
    {
        releaseLock();
        return false;
    }
}

bool
dumpFile::openFile(std::string& file, std::string& error)
{
    char buf[512];
    memset(buf, 0, 512);

    file = m_filePath + "/" + m_fileName;

    getLock();
    if(foutForDumpFile.is_open())
    {
        releaseLock();
        return false;
    }

    if(!wildcardUtils::check_disk_free_space(m_filePath.data(), static_cast<unsigned long long>(m_diskFreeSize)))
    {
        Hlr_elog("%s disk free size is not enough for %llu MB",m_filePath.data(), static_cast<unsigned long long>(m_diskFreeSize/1024/1024));
        snprintf(buf,sizeof(buf),"%s disk free size is not enough for %llu MB",m_filePath.data(), static_cast<unsigned long long>(m_diskFreeSize/1024/1024));
        error.assign(buf);
        releaseLock();
        return false;
    }

    if((access(m_filePath.data(), 0)) == -1 )
    {
        std::string mkdir = std::string("mkdir -p -m 777 ") + m_filePath;
        int ret = system(mkdir.c_str());
        if(ret < 0)
        {
            Hlr_elog("failed to call system(%s)",mkdir.c_str());
            snprintf(buf,sizeof(buf),"failed to call system(%s)",mkdir.c_str());
            error.assign(buf);
            releaseLock();
            return false;
        }
        if (WIFEXITED(ret))
        {
            if(WEXITSTATUS(ret) != 0)
            {
                Hlr_elog("failed to mkdir: %s, return val is %d",mkdir.c_str(),WEXITSTATUS(ret));
                snprintf(buf,sizeof(buf),"failed to mkdir: %s, return val is %d",mkdir.c_str(),WEXITSTATUS(ret));
                error.assign(buf);
                releaseLock();
                return false;
            }
        }
        else
        {
            Hlr_elog("system() return error:%s",mkdir.c_str());
            snprintf(buf,sizeof(buf),"system() return error:%s",mkdir.c_str());
            error.assign(buf);
            releaseLock();
            return false;
        }
    }
    if((access(m_filePath.data(), 0)) == -1 )
    {
        Hlr_elog("faied to create dir %s",m_filePath.data());
        snprintf(buf,sizeof(buf),"faied to create dir %s",m_filePath.data());
        error.assign(buf);
        releaseLock();
        return false;
    }

    std::string dumpFileName = m_filePath + "/" + m_fileName;
    if(!foutForDumpFile.is_open())
    {

        Hlr_elog("dump file %s is not opened, will open it...",dumpFileName.data());

        foutForDumpFile.open(dumpFileName.data(), ios::trunc);
    }


    if(!foutForDumpFile.is_open())
    {
        Hlr_elog("dump file %s can not be opened",dumpFileName.data());
        snprintf(buf,sizeof(buf),"dump file %s can not be opened",dumpFileName.data());
        error.assign(buf);
        releaseLock();
        return false;
    }

    releaseLock();
    return true;

}
bool
dumpFile::closeFile()
{
    getLock();
    if(!foutForDumpFile.is_open())
    {

        releaseLock();
        return true;
    }

    foutForDumpFile.flush();
    foutForDumpFile.close();

    releaseLock();
    return true;
}

bool
dumpFile::out(const char* buf)
{
    getLock();
    foutForDumpFile <<buf<<std::endl;

    foutForDumpFile.flush();
    releaseLock();
    return true;
}


