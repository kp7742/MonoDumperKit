//
//  Utils.h
//
//  Created by MJ (Ruit) on 2/3/19.
//

#ifndef UTILS_H
#define UTILS_H

#include "Logger.h"
#include <dlfcn.h>
#include <string>
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>



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


ProcMap getLibraryMap(pid_t pid, const char *libraryName);

#endif //UTILS_H
