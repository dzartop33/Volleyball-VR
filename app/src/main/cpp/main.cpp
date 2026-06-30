#include <android/native_activity.h>
#include <android/log.h>
#include <EGL/egl.h>
#include <GLES3/gl3.h>
#include <openxr/openxr.h>
#include <openxr/openxr_platform.h>
#include <vector>
#include <string>

#define LOG_TAG "VR_NATIVE"
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)

// --- ГРАФИЧЕСКИЕ ДАННЫЕ ---
const char* vertexShaderSource = 
    "#version 300 es\n"
    "layout(location = 0) in vec3 aPos;\n"
    "uniform mat4 uMVP;\n"
    "void main() {\n"
    "   gl_Position = uMVP * vec4(aPos, 1.0);\n"
    "}\0";

const char* fragmentShaderSource = 
    "#version 300 es\n"
    "precision mediump float;\n"
    "out vec4 FragColor;\n"
    "void main() {\n"
    "   FragColor = vec4(0.4, 0.3, 0.2, 1.0);\n" // Цвет паркета
    "}\0";

struct Engine {
    XrInstance instance;
    XrSession session;
    XrSystemId systemId;
    XrSpace worldSpace;
    EGLDisplay display;
    EGLContext context;
    EGLSurface surface;
    GLuint program;
};

// Функция для инициализации OpenXR Сессии
void create_xr_session(struct Engine* engine) {
    // 1. Привязка графики (Graphics Binding для OpenGL ES)
    // В нативном коде без библиотек-оберток это требует инициализации EGL
    XrGraphicsBindingOpenGLESAndroidKHR graphicsBinding = {XR_TYPE_GRAPHICS_BINDING_OPENGL_ES_ANDROID_KHR};
    graphicsBinding.display = engine->display;
    graphicsBinding.config = (void*)0; // Упрощенно
    graphicsBinding.context = engine->context;

    XrSessionCreateInfo sessionInfo = {XR_TYPE_SESSION_CREATE_INFO};
    sessionInfo.next = &graphicsBinding;
    sessionInfo.systemId = engine->systemId;

    if (xrCreateSession(engine->instance, &sessionInfo, &engine->session) != XR_SUCCESS) {
        LOGI("Failed to create XR Session");
    }

    // 2. Создание пространства (Пол / Stage)
    XrReferenceSpaceCreateInfo spaceInfo = {XR_TYPE_REFERENCE_SPACE_CREATE_INFO};
    spaceInfo.referenceSpaceType = XR_REFERENCE_SPACE_TYPE_STAGE;
    spaceInfo.poseInReferenceSpace = {{0,0,0,1}, {0,0,0}};
    xrCreateReferenceSpace(engine->session, &spaceInfo, &engine->worldSpace);
    
    LOGI("XR Session and Stage Space: OK");
}

void android_main(struct android_app* state) {
    Engine engine = {};
    
    // ИНИЦИАЛИЗАЦИЯ ИНСТАНСА (из 1.3)
    XrInstanceCreateInfo createInfo = {XR_TYPE_INSTANCE_CREATE_INFO};
    strncpy(createInfo.applicationInfo.applicationName, "PixelVolleyball", XR_MAX_APPLICATION_NAME_SIZE);
    createInfo.applicationInfo.apiVersion = XR_CURRENT_API_VERSION;
    xrCreateInstance(&createInfo, &engine.instance);

    XrSystemGetInfo systemInfo = {XR_TYPE_SYSTEM_GET_INFO};
    systemInfo.formFactor = XR_FORM_FACTOR_HEAD_MOUNTED_DISPLAY;
    xrGetSystem(engine.instance, &systemInfo, &engine.systemId);

    // Входим в цикл
    LOGI("VR Loop Started. Waiting for Headset...");

    while (true) {
        // Здесь мы будем опрашивать xrWaitFrame
        // И рассчитывать матрицы вида uView для каждой линзы
        // на основе положения головы.
        
        // 1. xrWaitFrame (Ждем готовности шлема)
        // 2. xrBeginFrame (Начинаем рисовать)
        // 3. Рисуем пол для левого глаза
        // 4. Рисуем пол для правого глаза
        // 5. xrEndFrame (Отправляем в шлем)
    }
}

extern "C" {
    void ANativeActivity_onCreate(ANativeActivity* activity, void* savedState, size_t savedStateSize) {
        LOGI("NativeActivity: Ready for VR Motion Tracking");
    }
}
