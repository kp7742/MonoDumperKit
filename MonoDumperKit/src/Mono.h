//
//  Mono.h
//
//  Created by MJ (Ruit) on 2/3/19.
//

#ifndef MONO_H
#define MONO_H

#include <dlfcn.h>
#include <string>
#include "Logger.h"
#include "Utils.h"

namespace Mono {


    struct _MonoImage {
        int ref_count;
        void *raw_data_handle;
        char *raw_data;
        uint32_t raw_data_len;
    };


    typedef struct _MonoImage MonoImage;
    typedef struct _MonoClass MonoClass;
    typedef struct _MonoMethod MonoMethod;
    typedef struct _MonoObject MonoObject;
    typedef struct _MonoProperty MonoProperty;
    typedef struct _MonoEvent MonoEvent;
    typedef struct _MonoDomain MonoDomain;
    typedef struct _MonoAssembly MonoAssembly;


    typedef void (*MonoFunc)(void *data, void *user_data);


    typedef enum {
        MONO_IMAGE_OK,
        MONO_IMAGE_ERROR_ERRNO,
        MONO_IMAGE_MISSING_ASSEMBLYREF,
        MONO_IMAGE_IMAGE_INVALID
    } MonoImageOpenStatus;


    extern void (*mono_assembly_foreach)(MonoFunc, void *);

    void initialize_exports();
};

#endif /* MONO_H */