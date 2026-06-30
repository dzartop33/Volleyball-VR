#include <android/native_activity.h>
#include <android/log.h>
#include <EGL/egl.h>
#include <GLES3/gl3.h>
#include <openxr/openxr.h>
#include <openxr/openxr_platform.h>

#define LOG_TAG "VR_NATIVE"
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)

/**
 * ВЕРСИЯ 1.3: OPENXR INITIALIZATION
 * Мы запрашиваем у Quest 3s доступ к стереоскопическим линзам.
 */

struct Engine {
    XrInstance instance;
    XrSession session;
    XrSystemId systemId;
};

void init_openxr(struct Engine* engine) {
    LOGI("Initializing OpenXR...");
    
    // 1. Создание инстанса OpenXR
    XrInstanceCreateInfo createInfo = {XR_TYPE_INSTANCE_CREATE_INFO};
    strncpy(createInfo.applicationInfo.applicationName, "PixelVolleyball", XR_MAX_APPLICATION_NAME_SIZE);
    createInfo.applicationInfo.apiVersion = XR_CURRENT_API_VERSION;

    if (xrCreateInstance(&createInfo, &engine->instance) != XR_SUCCESS) {
        LOGI("Failed to create OpenXR Instance");
        return;
    }

    // 2. Получение System ID (ID шлема)
    XrSystemGetInfo systemInfo = {XR_TYPE_SYSTEM_GET_INFO};
    systemInfo.formFactor = XR_FORM_FACTOR_HEAD_MOUNTED_DISPLAY;
    xrGetSystem(engine->instance, &systemInfo, &engine->systemId);

    LOGI("OpenXR Instance and System ID: OK");
}

void android_main(struct android_app* state) {
    Engine engine = {};
    init_openxr(&engine);
    
    while (true) {
        // Здесь будет цикл рендеринга в обе линзы
    }
}

extern "C" {
    void ANativeActivity_onCreate(ANativeActivity* activity, void* savedState, size_t savedStateSize) {
        LOGI("NativeActivity: Ready for OpenXR");
    }
}
