#pragma once

extern "C"
{
    typedef void (*mouseEventsDispatcherDelegate) (int _eventType, int _clientX, int _clientY, int _button);
    typedef void (*wheelEventDispatcherDelegate)(double _deltaX, double _deltaY, double _deltaZ, unsigned int _deltaMode);
    typedef void (*uiEventDispatcherDelegate)(int _width, int _height);
    typedef void (*keyboardEventDispatcherDelegate)(int _eventType, unsigned int _keyCode, unsigned int _charCode);

    void webCanvas_registerEventsDispatchers(
        mouseEventsDispatcherDelegate _mouseEventsDispatcher,
        wheelEventDispatcherDelegate _wheelEventDispatcher,
        uiEventDispatcherDelegate _uiEventDispatcher,
        keyboardEventDispatcherDelegate _keyboardEventDispatcher);
    bool webCanvas_initialise(const char* canvasId);
    void webCanvas_teardown();
    void webCanvas_setGraphicsContext();
    void webCanvas_getSize(int* _width, int* _height);
    void webCanvas_reSize(int* _width, int* _height);
}