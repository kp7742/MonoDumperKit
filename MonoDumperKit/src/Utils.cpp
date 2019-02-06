//
//  Utils.cpp
//
//  Created by MJ (Ruit) on 2/3/19.
//

#include "Utils.h"


ProcMap getLibraryMap(pid_t pid, const char *libraryName) {
    ProcMap retMap = {0};
    char mapFile[256] = {0}, line[512] = {0};

    snprintf(mapFile, sizeof(mapFile), "/proc/%d/maps", pid);
    FILE *fp = fopen(mapFile, "rt");
    if (fp != NULL) {
        while (fgets(line, sizeof(line), fp)) {
            if (strstr(line, libraryName)) {
                char tmpPerms[5] = {0}, tmpDev[12] = {0}, tmpPathname[666] = {0};
                // parse a line in maps file
                // (format) startAddress-endAddress perms offset dev inode pathname
                sscanf(line, "%llx-%llx %s %ld %s %d %s",
                       (long long unsigned *) &retMap.startAddr,
                       (long long unsigned *) &retMap.endAddr,
                       tmpPerms, &retMap.offset, tmpDev, &retMap.inode, tmpPathname);

                retMap.length = (uintptr_t) retMap.endAddr - (uintptr_t) retMap.startAddr;
                retMap.perms = tmpPerms;
                retMap.dev = tmpDev;
                retMap.pathname = tmpPathname;
                break;
            }
        }
        fclose(fp);
    }
    return retMap;
}
