LOCAL_PATH := $(call my-dir)  
include $(CLEAR_VARS)  
LOCAL_LDLIBS := -llog
LOCAL_MODULE    := ndkaudio
LOCAL_SRC_FILES := audio.c
include $(BUILD_SHARED_LIBRARY) 