//
//  Utils.h
//
//  Created by MJ (Ruit) on 2/3/19.
//

#ifndef UTILS_H
#define UTILS_H

#include "Logger.h"
#include <dlfcn.h>
#include <string.h>
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string>



struct ProcMap {
    void *startAddr;
    void *endAddr;
    size_t length;
    std::string perms;
    long offset;
    std::string dev;
    int inode;
    std::string pathname;

    bool isValid() { return (startAddr != NULL && endAddr != NULL && !pathname.empty()); }
};


ProcMap getLibraryMap(const char *libraryName);
std::string getProcName();

#endif //UTILS_H
