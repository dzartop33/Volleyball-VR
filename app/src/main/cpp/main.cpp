#include <android/native_activity.h>
#include <android/log.h>
#include <EGL/egl.h>
#include <GLES3/gl3.h>

#define LOG_TAG "VR_NATIVE"
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)

/**
 * ВЕРСИЯ 1.1: ЦИКЛ ОТРИСОВКИ
 * Мы инициализируем графический движок и красим экран в цвет неба.
 */

struct Engine {
    EGLDisplay display;
    EGLSurface surface;
    EGLContext context;
    int32_t width;
    int32_t height;
};

// Функция для заливки экрана цветом
void draw_frame(struct Engine* engine) {
    if (engine->display == NULL) return;

    // Цвет школьного спортзала (бежево-синий) или просто небо
    glClearColor(0.5f, 0.8f, 1.0f, 1.0f); // Голубой
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // В следующих шагах здесь появятся команды glDrawArrays для кубов
    
    eglSwapBuffers(engine->display, engine->surface);
}

void android_main(struct android_app* state) {
    LOGI("VR Engine-less: Cycle Started");
    
    // Этот цикл будет работать до закрытия игры
    while (true) {
        // Мы будем опрашивать события Quest тут
        // И рисовать кадр:
        // draw_frame(&engine);
    }
}

extern "C" {
    void ANativeActivity_onCreate(ANativeActivity* activity, void* savedState, size_t savedStateSize) {
        LOGI("NativeActivity Ready to Render");
    }
}
