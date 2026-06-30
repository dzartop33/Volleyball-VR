#include <android/native_activity.h>
#include <android/log.h>
#include <EGL/egl.h>
#include <GLES3/gl3.h>
#include <string.h>

// Подключаем OpenXR (теперь пути в build.yml настроены верно)
#include <openxr/openxr.h>
#include <openxr/openxr_platform.h>

#define LOG_TAG "VR_NATIVE"
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)

/**
 * ЧИСТЫЙ КОД 1.5 FIXED
 * Мы инициализируем OpenXR Instance для Quest 3s.
 */

void android_main(struct android_app* state) {
    LOGI("NATIVE VR: Starting Engine...");

    // Базовая инициализация OpenXR
    XrInstance instance;
    XrInstanceCreateInfo createInfo = {XR_TYPE_INSTANCE_CREATE_INFO};
    strcpy(createInfo.applicationInfo.applicationName, "VBall");
    createInfo.applicationInfo.apiVersion = XR_CURRENT_API_VERSION;

    XrResult res = xrCreateInstance(&createInfo, &instance);
    if (res == XR_SUCCESS) {
        LOGI("SUCCESS: OpenXR Instance Created!");
    } else {
        LOGI("ERROR: OpenXR Failed with code %d", (int)res);
    }

    // Главный цикл (пока просто очистка экрана)
    while (true) {
        glClearColor(0.0f, 0.5f, 0.7f, 1.0f); // Бирюзовый цвет успеха
        glClear(GL_COLOR_BUFFER_BIT);
        // Здесь шлем будет ждать ввода
    }
}

extern "C" {
    void ANativeActivity_onCreate(ANativeActivity* activity, void* savedState, size_t savedStateSize) {
        LOGI("NativeActivity Created Successfully");
    }
}
