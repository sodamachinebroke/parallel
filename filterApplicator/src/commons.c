#include "commons.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *addSuffix(const char *filename, const char *suffix) {
    const char *ext = strrchr(filename, '.');
    if (!ext) return NULL;

    size_t fnLength = ext - filename;
    size_t sfxLength = strlen(suffix);
    size_t nfnLength = fnLength + sfxLength + 1;

    char *nfn = malloc(nfnLength + 1);
    if (!nfn) return NULL;

    memcpy(nfn, filename, fnLength);
    memcpy(nfn + fnLength, suffix, sfxLength);
    nfn[nfnLength - 1] = '\0';
    strcat(nfn, ext);

    return nfn;
}