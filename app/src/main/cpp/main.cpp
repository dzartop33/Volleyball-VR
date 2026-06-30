#include <android/native_activity.h>
#include <android/log.h>
#include <EGL/egl.h>
#include <GLES3/gl3.h>
#include <openxr/openxr.h>
#include <openxr/openxr_platform.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>

#define LOG_TAG "VR_NATIVE"
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)

struct Engine {
    XrInstance instance;
    XrSession session;
    XrSpace worldSpace;
    // Графические ресурсы
    GLuint program;
    GLuint vao;
};

// --- ФУНКЦИЯ ОТРИСОВКИ ОДНОГО ГЛАЗА ---
void render_eye(Engine* engine, glm::mat4 projection, glm::mat4 view) {
    glUseProgram(engine->program);
    
    // Рассчитываем MVP матрицу (Model-View-Projection)
    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 mvp = projection * view * model;
    
    GLint mvpLoc = glGetUniformLocation(engine->program, "uMVP");
    glUniformMatrix4fv(mvpLoc, 1, GL_FALSE, &mvp[0][0]);

    glBindVertexArray(engine->vao);
    glDrawArrays(GL_TRIANGLES, 0, 6); // Рисуем площадку
}

void android_main(struct android_app* state) {
    Engine engine = {};
    LOGI("VR Engine 1.5: Rendering Active.");

    // Бесконечный цикл VR
    while (true) {
        // 1. Ждем сигнала от шлема (WaitFrame)
        // 2. Опрашиваем положение головы
        // 3. Для каждого глаза (Left/Right):
        //    - Вычисляем матрицы GLM
        //    - Вызываем render_eye(...)
        // 4. Отправляем готовое изображение в линзы (EndFrame)
        
        // Для теста: просто очистка экрана в синий
        glClearColor(0.0f, 0.2f, 0.5f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }
}

extern "C" {
    void ANativeActivity_onCreate(ANativeActivity* activity, void* savedState, size_t savedStateSize) {
        LOGI("NativeActivity: Rendering Engine Ready.");
    }
}
