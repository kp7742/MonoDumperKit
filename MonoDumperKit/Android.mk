LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE    := MonoDumperKit
LOCAL_SRC_FILES := src/main.cpp src/Utils.cpp src/mono.cpp src/dumper.cpp 


LOCAL_LDLIBS  += -llog

include $(BUILD_SHARED_LIBRARY)