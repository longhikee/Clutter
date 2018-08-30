#include <sys/statfs.h>
bool check_disk_free_space(const char *path, unsigned long long  needSize)
{
    struct statfs fs;
    unsigned long long  f_space;
    unsigned long long  b_size;
    int i;

    i = statfs(path, &fs);
    if (i < 0)
    {
        Hlr_elog("failed to call statfs()");
        return false;
    }

    b_size = static_cast<unsigned long long>(fs.f_bsize);

    f_space = static_cast<unsigned long long>( b_size * fs.f_bavail );

    if(f_space < needSize)
    {
        Hlr_elog("disk size limited,dir %s free size is %llu Bytes,needed size is %llu Bytes",path,f_space, needSize);
        return false;
    }

    return true;
}>
