#include <android/native_activity.h>
#include <android/log.h>
#include <GLES3/gl3.h>

#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, "VR_NATIVE", __VA_ARGS__)

// Главная функция нативной активности Android
extern "C" {
    void ANativeActivity_onCreate(ANativeActivity* activity, void* savedState, size_t savedStateSize) {
        LOGI("SUCCESS: Native Volleyball App Created!");
        
        // В следующих шагах мы добавим сюда цикл отрисовки
        // Пока просто красим экран в зеленый цвет успеха
        glClearColor(0.0f, 0.8f, 0.2f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
    }
}
