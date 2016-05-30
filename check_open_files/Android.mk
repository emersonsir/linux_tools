LOCAL_PATH:= $(call my-dir)

include $(CLEAR_VARS)
LOCAL_SRC_FILES := \
	check_open_files.cpp \
	utils.cpp
LOCAL_MODULE := cof
LOCAL_MODULE_TAGS := optional
LOCAL_CPPFLAGS += -std=c++11 -fpermissive
LOCAL_LDFLAGS +=
LOCAL_CFLAGS := -D__LINUX__

LOCAL_SHARED_LIBRARIES := \
	liblog \
	libutils \
	libcutils \
	libstlport

LOCAL_C_INCLUDES := \
	bionic \
	external/stlport/stlport

LOCAL_MODULE_PATH := $(TARGET_OUT_VENDOR_EXECUTABLES)
include $(BUILD_EXECUTABLE)
