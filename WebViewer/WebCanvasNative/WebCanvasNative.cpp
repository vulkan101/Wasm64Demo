#include "WebCanvasNative.h"
#include <sstream>
#include <GLES3/gl3.h>
#include <emscripten/html5_webgl.h>

EM_BOOL mouse_callback(int _eventType, const EmscriptenMouseEvent* _mouseEvent, void* _userData);
EM_BOOL wheel_callback(int _eventType, const EmscriptenWheelEvent* _wheelEvent, void* _userData);
EM_BOOL ui_callback(int _eventType, const EmscriptenUiEvent* _uiEvent, void* _userData);
EM_BOOL keyboard_callback(int _eventType, const EmscriptenKeyboardEvent* _keyboardEvent, void* _userData);

EM_JS(int, canvas_get_width, (const char* _canvasId),
    {
        const canvas = document.querySelector(UTF8ToString(_canvasId));
        return canvas.clientWidth;
    });

EM_JS(int, canvas_get_height, (const char* _canvasId),
    {
        const canvas = document.querySelector(UTF8ToString(_canvasId));
        return canvas.clientHeight;
    });

struct webCanvas
{
    EMSCRIPTEN_WEBGL_CONTEXT_HANDLE context = 0;
    std::string canvasId;
    mouseEventsDispatcherDelegate mouseEventsDispatcher = nullptr;
    wheelEventDispatcherDelegate wheelEventDispatcher = nullptr;
    uiEventDispatcherDelegate uiEventDispatcher = nullptr;
    keyboardEventDispatcherDelegate keyboardEventDispatcher = nullptr;

    bool initialise()
    {
        EmscriptenWebGLContextAttributes attrs;
        attrs.alpha = 0;
        attrs.depth = 1;
        attrs.stencil = 1;
        attrs.antialias = 1;
        attrs.premultipliedAlpha = 1;
        attrs.preserveDrawingBuffer = 0;
        attrs.powerPreference = EM_WEBGL_POWER_PREFERENCE_DEFAULT; //EM_WEBGL_POWER_PREFERENCE_HIGH_PERFORMANCE
        attrs.failIfMajorPerformanceCaveat = 0;
        attrs.majorVersion = 2;
        attrs.minorVersion = 0;
        attrs.enableExtensionsByDefault = 1;
        attrs.explicitSwapControl = 0;
        attrs.renderViaOffscreenBackBuffer = 0;
        attrs.proxyContextToMainThread = EMSCRIPTEN_WEBGL_CONTEXT_PROXY_DISALLOW;

        emscripten_console_log("Creating webGL context");
        const char* canvasIdStr = canvasId.c_str();
        context = emscripten_webgl_create_context(canvasIdStr, &attrs);
        if (context <= 0)
        {
            emscripten_console_error("Failed to create WebGL context");
            return false;
        }
        emscripten_console_log("WebGL context created");

        emscripten_webgl_make_context_current(context);

        /*emscripten_set_click_callback(canvasIdStr, this, 1, mouse_callback);
        emscripten_set_mousedown_callback(canvasIdStr, this, 1, mouse_callback);
        emscripten_set_mouseup_callback(canvasIdStr, this, 1, mouse_callback);
        emscripten_set_dblclick_callback(canvasIdStr, this, 1, mouse_callback);
        emscripten_set_mousemove_callback(canvasIdStr, this, 1, mouse_callback);
        emscripten_set_mouseenter_callback(canvasIdStr, this, 1, mouse_callback);
        emscripten_set_mouseleave_callback(canvasIdStr, this, 1, mouse_callback);
        emscripten_set_wheel_callback(canvasIdStr, this, 1, wheel_callback);       

        emscripten_set_keypress_callback(EMSCRIPTEN_EVENT_TARGET_WINDOW, this, 1, keyboard_callback);
        emscripten_set_keydown_callback(EMSCRIPTEN_EVENT_TARGET_WINDOW, this, 1, keyboard_callback);
        emscripten_set_keyup_callback(EMSCRIPTEN_EVENT_TARGET_WINDOW, this, 1, keyboard_callback); 
        emscripten_set_resize_callback(EMSCRIPTEN_EVENT_TARGET_WINDOW, this, 1, ui_callback); */

        return true;
    }

    void shutdown()
    {
        emscripten_webgl_destroy_context(context);
    }

    void setGraphicsContext()
    {
        emscripten_webgl_make_context_current(context);
    }

    void getSize(int* _width, int* _height)
    {
        auto canvasIdstr = canvasId.c_str();
        *_width = canvas_get_width(canvasIdstr);
        *_height = canvas_get_height(canvasIdstr);

        // This is required to enforce the size match between webgl buffer size and canvas resolution
        emscripten_set_canvas_element_size(canvasIdstr, *_width, *_height);
    }

    void handleMouseEvent(int _eventType, const EmscriptenMouseEvent* _mouseEvent)
    {
        if (mouseEventsDispatcher == nullptr)
            return;

        mouseEventsDispatcher(_eventType, _mouseEvent->clientX, _mouseEvent->clientY, _mouseEvent->button);
    }

    void handleWheelEvent(const EmscriptenWheelEvent* _wheelEvent)
    {
        if (wheelEventDispatcher == nullptr)
            return;

        wheelEventDispatcher(_wheelEvent->deltaX, _wheelEvent->deltaY, _wheelEvent->deltaZ, _wheelEvent->deltaMode);
    }

    void handleUiEvent(int _eventType, const EmscriptenUiEvent* _uiEvent)
    {
        if (uiEventDispatcher == nullptr)
            return;

        if (_eventType == EMSCRIPTEN_EVENT_RESIZE)
        {
            int width, height;
            getSize(&width, &height);
            glViewport(0, 0, width, height);
            uiEventDispatcher(width, height);
        }
    }

    void reSize(int* _width, int* _height)
    {
        int width, height;
        getSize(&width, &height);
        glViewport(0, 0, width, height);
        *_width = width;
        *_height = height;
    }

    void handleKeyboardEvent(int _eventType, const EmscriptenKeyboardEvent* _keyEvent)
    {
        if (keyboardEventDispatcher == nullptr)
            return;

        //bool isCtrlKey = _keyEvent->ctrlKey == 1;
        //bool isAltKey = _keyEvent->altKey == 1;
        //bool isShiftKey = _keyEvent->shiftKey == 1;

        keyboardEventDispatcher(_eventType, _keyEvent->keyCode, _keyEvent->charCode);
    }
};

static webCanvas webCanvasInstance;

void webCanvas_registerEventsDispatchers(
    mouseEventsDispatcherDelegate _mouseEventsDispatcher,
    wheelEventDispatcherDelegate _wheelEventDispatcher,
    uiEventDispatcherDelegate _uiEventDispatcher,
    keyboardEventDispatcherDelegate _keyboardEventDispatcher)
{
    webCanvasInstance.mouseEventsDispatcher = _mouseEventsDispatcher;
    webCanvasInstance.wheelEventDispatcher = _wheelEventDispatcher;
    webCanvasInstance.uiEventDispatcher = _uiEventDispatcher;
    webCanvasInstance.keyboardEventDispatcher = _keyboardEventDispatcher;
}

bool webCanvas_initialise(const char* canvasId)
{
    std::stringstream ss;
    ss << "#" << canvasId;

    webCanvasInstance.canvasId = ss.str();
    return webCanvasInstance.initialise();
}

void webCanvas_teardown()
{
    webCanvasInstance.shutdown();
}

void webCanvas_setGraphicsContext()
{
    webCanvasInstance.setGraphicsContext();
}

void webCanvas_getSize(int* _width, int* _height)
{
    webCanvasInstance.getSize(_width, _height);
}

void webCanvas_reSize(int* _width, int* _height)
{
    webCanvasInstance.reSize(_width, _height);
}

EM_BOOL mouse_callback(int _eventType, const EmscriptenMouseEvent* _mouseEvent, void* _userData)
{
    auto webCanvasImpl = reinterpret_cast<webCanvas*>(_userData);
    webCanvasImpl->handleMouseEvent(_eventType, _mouseEvent);
    return 0;
}

EM_BOOL wheel_callback(int _eventType, const EmscriptenWheelEvent* _wheelEvent, void* _userData)
{
    auto webCanvasImpl = reinterpret_cast<webCanvas*>(_userData);
    webCanvasImpl->handleWheelEvent(_wheelEvent);
    return 0;
}

EM_BOOL ui_callback(int _eventType, const EmscriptenUiEvent* _uiEvent, void* _userData)
{
    auto webCanvasImpl = reinterpret_cast<webCanvas*>(_userData);
    webCanvasImpl->handleUiEvent(_eventType, _uiEvent);
    return 0;
}

EM_BOOL keyboard_callback(int _eventType, const EmscriptenKeyboardEvent* _keyboardEvent, void* _userData)
{
    auto webCanvasImpl = reinterpret_cast<webCanvas*>(_userData);
    webCanvasImpl->handleKeyboardEvent(_eventType, _keyboardEvent);
    return 0;
}
