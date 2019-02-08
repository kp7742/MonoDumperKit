//
//  Dumper.h
//
//  Created by MJ (Ruit) on 2/3/19.
//

#ifndef DUMPER_H
#define DUMPER_H

#include "Mono.h"
#include <unistd.h>
#include <sys/stat.h>


using Mono::MonoImage;
using Mono::MonoAssembly;
using Mono::MonoFunc;


namespace MonoDumper {

    extern bool IsReady;

    void Check_AssemblyCSharp(MonoAssembly *assembly, void *user_data);

    void Dump_Foreach_Assembly(MonoAssembly *assembly, void *user_data);

    void Dump_DLLs(const char *dumpFolder);
};

#endif /* DUMPER_H */
