//
//  main.cpp
//
//  Created by MJ (Ruit) on 2/3/19.
//

#include <pthread.h>
#include "Dumper.h"
#include "Utils.h"

void *mono_dump_thread(void *args);


__attribute__((constructor))
void init() {
    LOGD("Hello cats from MonoDumperKit!");
    pthread_t dumpTID;
    pthread_create(&dumpTID, NULL, mono_dump_thread, NULL);
}


void *mono_dump_thread(void *args){

    LOGD("Looking for libmono.so");

    ProcMap monoMap;
    do {
        monoMap = getLibraryMap("libmono.so");
        sleep(1);
    } while (!monoMap.isValid());

    LOGD("Initializing mono exports...");

    Mono::initialize_exports();

    LOGD("Creating dump folder...");

    // dump to app's external files directory since it does't need storage permission or root
    std::string exStorage = getenv("EXTERNAL_STORAGE");
    std::string dir = exStorage + "/Android/data/" + getProcName() + "/files/dumpDir";
    mkdir(dir.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
    LOGD("Dump folder: %s", dir.c_str());

    MonoDumper::Dump_DLLs(dir.c_str());

    return NULL;
}