#include <android/native_activity.h>
#include <android/log.h>
#include <EGL/egl.h>
#include <GLES3/gl3.h>
#include <openxr/openxr.h>

#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, "VR_PRO", __VA_ARGS__)

void android_main(struct android_app* state) {
    LOGI("NATIVE VR STARTING...");
    
    // Минимальная проверка OpenXR
    XrInstance instance;
    XrInstanceCreateInfo ci = {XR_TYPE_INSTANCE_CREATE_INFO};
    // Пустое имя для быстрого теста сборки
    xrCreateInstance(&ci, &instance);

    while (true) {
        glClearColor(0.2f, 0.3f, 0.4f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
    }
}

extern "C" {
    void ANativeActivity_onCreate(ANativeActivity* activity, void* savedState, size_t savedStateSize) {
        LOGI("ACTIVITY CREATED");
    }
}
