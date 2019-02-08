//
//  Dumper.cpp
//
//  Created by MJ (Ruit) on 2/3/19.
//

#include "Dumper.h"

bool MonoDumper::IsReady = false;


#define GET_ASSEMBLY_IMAGE(X) *(MonoImage **) ((uintptr_t) assembly + 0x40)
#define GET_IMAGE_NAME(X) *(const char **)((uintptr_t)image + 0x18)


void MonoDumper::Check_AssemblyCSharp(MonoAssembly *assembly, void *user_data) {
    MonoImage *image = GET_ASSEMBLY_IMAGE(assembly);
    if (!image) {
        LOGE("Couldn't find image of assembly %p", assembly);
        return;
    }
    std::string imageName = std::string(GET_IMAGE_NAME(image));
    LOGD("Found image: %s", imageName.c_str());
    if (strcmp(imageName.c_str(), "Assembly-CSharp") == 0)
        IsReady = true;
}


void MonoDumper::Dump_Foreach_Assembly(MonoAssembly *assembly, void *user_data) {
    MonoImage *image = GET_ASSEMBLY_IMAGE(assembly);
    if (!image) {
        LOGE("Couldn't find image of assembly %p", assembly);
        return;
    }

    std::string imageName = std::string(GET_IMAGE_NAME(image));
    LOGD("Image name: %s", imageName.c_str());
    char *data = image->raw_data;
    uint32_t dataLen = image->raw_data_len;
    if (data == NULL || dataLen < 1) {
        LOGE("Failed to find data of %s", imageName.c_str());
        return;
    }

    std::string dumpFolder = (const char *) user_data;
    std::string dest = dumpFolder + "/" + imageName + ".dll";
    LOGD("Dumping %s", dest.c_str());

    FILE *file = fopen(dest.c_str(), "wb");
    if (file == NULL) {
        LOGE("Couldn't create dump file for %s", imageName.c_str());
        return;
    }

    fwrite(data, sizeof(char), dataLen, file);
    fclose(file);

    LOGD("%s has been dumped successfully", imageName.c_str());
}


void MonoDumper::Dump_DLLs(const char *dumpFolder) {
    if (!Mono::mono_assembly_foreach)
        return;

    LOGD("Looking for assembly-csharp...");

    while (!IsReady) {
        sleep(1);
        Mono::mono_assembly_foreach((MonoFunc) Check_AssemblyCSharp, (void *) "Check");
    }

    Mono::mono_assembly_foreach((MonoFunc) Dump_Foreach_Assembly, (void *) dumpFolder);
}