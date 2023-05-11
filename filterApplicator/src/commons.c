#ifdef _WIN32
#include <windows.h>
#elif MACOS
#include <sys/param.h>
#include <sys/sysctl.h>
#else
#include <unistd.h>
#endif

#include "commons.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *addSuffix(const char *filename, const char *suffix)
{
    const char *ext = strrchr(filename, '.');
    if (!ext)
        return NULL;

    size_t fnLength = ext - filename;
    size_t sfxLength = strlen(suffix);
    size_t nfnLength = fnLength + sfxLength + 1;

    char *nfn = malloc(nfnLength + 1);
    if (!nfn)
        return NULL;

    memcpy(nfn, filename, fnLength);
    memcpy(nfn + fnLength, suffix, sfxLength);
    nfn[nfnLength - 1] = '\0';
    strcat(nfn, ext);

    return nfn;
}

int getNumberOfCores()
{
#ifdef WIN32
    SYSTEM_INFO sysinfo;
    GetSystemInfo(&sysinfo);
    return sysinfo.dwNumberOfProcessors;
#elif MACOS
    int nm[2];
    size_t len = 4;
    uint32_t count;

    nm[0] = CTL_HW;
    nm[1] = HW_AVAILCPU;
    sysctl(nm, 2, &count, &len, NULL, 0);

    if (count < 1)
    {
        nm[1] = HW_NCPU;
        sysctl(nm, 2, &count, &len, NULL, 0);
        if (count < 1)
        {
            count = 1;
        }
    }
    return count;
#else
    return sysconf(_SC_NPROCESSORS_ONLN);
#endif
}