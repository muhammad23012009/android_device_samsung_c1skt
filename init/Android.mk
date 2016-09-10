LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE_TAGS := optional
LOCAL_C_INCLUDES := system/core/init
LOCAL_CFLAGS := -Wall
LOCAL_SRC_FILES := init_c1skt.cpp
ifneq ($(TARGET_LIBINIT_C1SKT_DEFINES_FILE),)
  LOCAL_SRC_FILES += ../../../../$(TARGET_LIBINIT_C1SKT_DEFINES_FILE)
endif
LOCAL_MODULE := libinit_c1skt

include $(BUILD_STATIC_LIBRARY)
