LOCAL_PATH:= $(call my-dir)

include $(CLEAR_VARS)

LOCAL_SRC_FILES:= secril-shim.c
LOCAL_SHARED_LIBRARIES := liblog libbinder libril libcutils
LOCAL_MODULE:= libsecril-shim

include $(BUILD_SHARED_LIBRARY)
