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
    LOGD("Hello cats from injected lib!");
    pthread_t dumpTID;
    pthread_create(&dumpTID, NULL, mono_dump_thread, NULL);
}


void *mono_dump_thread(void *args){
    LOGD("waiting for dump...");

    while(!getLibraryMap(getpid(), "libmono.so").isValid()) {
        sleep(1);
    }

    Mono::initialize_exports();

    MonoDumper::Dump_DLLs();

    return NULL;
}