//
//  Dumper.cpp
//
//  Created by MJ (Ruit) on 2/3/19.
//

#include "Dumper.h"

bool MonoDumper::IsReady = false;

void MonoDumper::Check_AssemblyCSharp(MonoAssembly *assembly, void *user_data) {
    if (Mono::mono_assembly_get_image && Mono::mono_image_get_name) {
        MonoImage *image = Mono::mono_assembly_get_image(assembly);
        if (!image) {
            LOGE("Couldn't find image of assembly %p", assembly);
            return;
        }
        std::string imageName = std::string(Mono::mono_image_get_name(image));
        if (strcmp(imageName.c_str(), "Assembly-CSharp") == 0)
            IsReady = true;
    }
}


void MonoDumper::Dump_Foreach_Assembly(MonoAssembly *assembly, void *user_data) {
    if (Mono::mono_assembly_get_image && Mono::mono_image_get_name) {
        MonoImage *image = Mono::mono_assembly_get_image(assembly);
        if (!image) {
            LOGE("Couldn't find image of assembly %p", assembly);
            return;
        }

        std::string imageName = std::string(Mono::mono_image_get_name(image));
        LOGD("Image name: %s", imageName.c_str());
        char *data = image->raw_data;
        uint32_t dataLen = image->raw_data_len;
        if (data == NULL || dataLen < 1) {
            LOGE("Failed to find data of %s", imageName.c_str());
            return;
        }



        // external storage needs [android.permission.WRITE_EXTERNAL_STORAGE] permission
        std::string path = "/sdcard/dumpdir";
        mkdir(path.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
        LOGD("Dump path: %s", path.c_str());

        std::string dumpPath = path + "/" + imageName + ".dll";
        LOGD("Dumping %s...", dumpPath.c_str());

        FILE *file = fopen(dumpPath.c_str(), "wb");
        if (file == NULL) {
            LOGE("Couldn't create dump file for %s", imageName.c_str());
            return;
        }

        fwrite(data, sizeof(char), dataLen, file);
        fclose(file);
        LOGD("%s has been dumped successfully", imageName.c_str());
    }
}


void MonoDumper::Dump_DLLs() {
    if (!Mono::mono_assembly_foreach)
        return;

    while (!IsReady) {
        sleep(1);
        Mono::mono_assembly_foreach((MonoFunc) Check_AssemblyCSharp, (void *) "Check");
    }

    Mono::mono_assembly_foreach((MonoFunc) Dump_Foreach_Assembly, (void *) "Dump");
}