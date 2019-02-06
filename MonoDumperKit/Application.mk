APP_ABI      := armeabi-v7a x86
APP_PLATFORM := android-18
APP_STL      := c++_static
APP_OPTIM    := release
APP_PIE      := true

APP_CPPFLAGS := -std=c++14 -Wall -Werror -fpermissive -fpic
APP_CPPFLAGS += -fno-rtti -fno-exceptions
APP_CPPFLAGS += -DNDEBUG

APP_BUILD_SCRIPT := Android.mk