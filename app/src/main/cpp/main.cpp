#include <android/native_activity.h>
#include <android/log.h>
#include <EGL/egl.h>
#include <GLES3/gl3.h>
#include <vector>

#define LOG_TAG "VR_NATIVE"
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)

// --- ШЕЙДЕРЫ (Код для видеокарты) ---
// Этот код превращает 3D координаты в пиксели на экране
const char* vertex_shader_source = 
    "#version 300 es\n"
    "layout(location = 0) in vec3 aPos;\n"
    "uniform mat4 uProjection;\n"
    "uniform mat4 uView;\n"
    "void main() {\n"
    "   gl_Position = uProjection * uView * vec4(aPos, 1.0);\n"
    "}\0";

const char* fragment_shader_source = 
    "#version 300 es\n"
    "precision mediump float;\n"
    "out vec4 FragColor;\n"
    "void main() {\n"
    "   FragColor = vec4(0.3, 0.2, 0.1, 1.0);\n" // Цвет паркета (коричневый)
    "}\0";

struct Engine {
    EGLDisplay display;
    EGLSurface surface;
    EGLContext context;
    GLuint program;
    GLuint vao, vbo;
};

// Функция для подготовки площадки (создаем прямоугольник)
void init_court(struct Engine* engine) {
    // 1. Компиляция шейдеров
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertex_shader_source, NULL);
    glCompileShader(vertexShader);

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragment_shader_source, NULL);
    glCompileShader(fragmentShader);

    engine->program = glCreateProgram();
    glAttachShader(engine->program, vertexShader);
    glAttachShader(engine->program, fragmentShader);
    glLinkProgram(engine->program);

    // 2. Создание геометрии (Координаты площадки 9x18 метров)
    float vertices[] = {
        -4.5f, 0.0f, -9.0f,
         4.5f, 0.0f, -9.0f,
         4.5f, 0.0f,  9.0f,
        -4.5f, 0.0f, -9.0f,
         4.5f, 0.0f,  9.0f,
        -4.5f, 0.0f,  9.0f
    };

    glGenVertexArrays(1, &engine->vao);
    glGenBuffers(1, &engine->vbo);
    glBindVertexArray(engine->vao);
    glBindBuffer(GL_ARRAY_BUFFER, engine->vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
}

void draw_frame(struct Engine* engine) {
    if (engine->display == NULL) return;

    glClearColor(0.1f, 0.1f, 0.2f, 1.0f); // Темный фон
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glUseProgram(engine->program);
    glBindVertexArray(engine->vao);
    glDrawArrays(GL_TRIANGLES, 0, 6); // Рисуем площадку

    eglSwapBuffers(engine->display, engine->surface);
}

void android_main(struct android_app* state) {
    LOGI("VR Engine-less: Rendering Court...");
    // В следующих шагах добавим инициализацию EGL и цикл событий
}

extern "C" {
    void ANativeActivity_onCreate(ANativeActivity* activity, void* savedState, size_t savedStateSize) {
        LOGI("NativeActivity: Ready for GL Shaders");
    }
}
