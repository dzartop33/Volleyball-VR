#include <android/native_activity.h>
#include <android/log.h>
#include <EGL/egl.h>
#include <GLES3/gl3.h>

#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, "VR_NATIVE", __VA_ARGS__)

void android_main(struct android_app* state) {
    LOGI("NATIVE START");
    while (true) {
        // Здесь будет VR цикл
    }
}

extern "C" {
    void ANativeActivity_onCreate(ANativeActivity* activity, void* savedState, size_t savedStateSize) {
        LOGI("Activity Created");
    }
}
