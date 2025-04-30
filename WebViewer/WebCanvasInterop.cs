using System.Reflection;
using System.Runtime.InteropServices;

namespace WebViewer
{
    public static class WebCanvasInterop
    {
        private static readonly IntPtr mouseEventsDispatcherPtr = RetrieveFunctionPointer("MouseEventsDispatcher");
        private static readonly IntPtr wheelEventDispatcherPtr = RetrieveFunctionPointer("WheelEventDispatcher");
        private static readonly IntPtr resizeEventDispatcherPtr = RetrieveFunctionPointer("ResizeEventDispatcher");
        private static readonly IntPtr keyboardEventHandlerPtr = RetrieveFunctionPointer("KeyboardEventDispatcher");

        private static MouseEventsHandlerDelegate? mouseEventsHandler;
        private static WheelEventHandlerDelegate? wheelEventHandler;
        private static ResizeEventHandlerDelegate? resizeEventHandler;
        private static KeyboardEventHandlerDelegate? keyboardEventHandler;

        private static bool initialised = false;

        public delegate void MouseEventsHandlerDelegate(int _eventType, int _clientX, int _clientY, int _button);
        public delegate void WheelEventHandlerDelegate(double _deltaX, double _deltaY, double _deltaZ, uint _deltaMode);
        public delegate void ResizeEventHandlerDelegate(int _width, int _height);
        public delegate void KeyboardEventHandlerDelegate(int _eventType, uint _keyCode, uint _charCode);

        public static bool Initialise(
            string _canvasId, 
            MouseEventsHandlerDelegate _mouseEventsHandler, 
            WheelEventHandlerDelegate _wheelEventHandler,
            ResizeEventHandlerDelegate _resizeEventHandler,
            KeyboardEventHandlerDelegate _keyboardEventHandler)
        {
            ArgumentNullException.ThrowIfNull(_canvasId);

            if (_canvasId.Length == 0)
                throw new ArgumentException("string len cannot be zero", nameof(_canvasId));

            ArgumentNullException.ThrowIfNull(_mouseEventsHandler);
            ArgumentNullException.ThrowIfNull(_wheelEventHandler);
            ArgumentNullException.ThrowIfNull(_resizeEventHandler);
            ArgumentNullException.ThrowIfNull(_keyboardEventHandler);

            mouseEventsHandler = _mouseEventsHandler;
            wheelEventHandler = _wheelEventHandler;
            resizeEventHandler = _resizeEventHandler;
            keyboardEventHandler = _keyboardEventHandler;

            webCanvas_registerEventsDispatchers(
                mouseEventsDispatcherPtr,
                wheelEventDispatcherPtr,
                resizeEventDispatcherPtr,
                keyboardEventHandlerPtr);

            initialised = webCanvas_initialise(_canvasId);
            return initialised;
        }

        public static void SetGraphicsContext()
        {
            if (!initialised)
                throw new ApplicationException("WebCanvas not initialised");

            webCanvas_setGraphicsContext();
        }

        public static void GetSize(out int _width, out int _height)
        {
            if (!initialised)
                throw new ApplicationException("WebCanvas not initialised");

            webCanvas_getSize(out _width, out _height);
        }

        public static void ReSize(out int _width, out int _height)
        {
            if (!initialised)
                throw new ApplicationException("WebCanvas not initialised");

            webCanvas_reSize(out _width, out _height);

        }

        public static void Teardown()
        {
            if (!initialised)
                return;

            webCanvas_teardown();
        }

        private static IntPtr RetrieveFunctionPointer(string _methodName)
        {
            if (string.IsNullOrEmpty(_methodName))
                throw new ArgumentNullException(nameof(_methodName));

            var interopType = typeof(WebCanvasInterop);
            
            if (interopType == null)
                throw new ArgumentNullException(nameof(interopType));

            var bindingFlags = BindingFlags.NonPublic | BindingFlags.Static;
            MethodInfo methodInfo = interopType.GetMethod(_methodName, bindingFlags);

            if (methodInfo == null)
                throw new ArgumentNullException(nameof(methodInfo));

            return methodInfo.MethodHandle.GetFunctionPointer();
        }

        [UnmanagedCallersOnly]
        private static void MouseEventsDispatcher(int _eventType, int _clientX, int _clientY, int _button)
        {
            mouseEventsHandler?.Invoke(_eventType, _clientX, _clientY, _button);
        }

        [UnmanagedCallersOnly]
        private static void WheelEventDispatcher(double _deltaX, double _deltaY, double _deltaZ, uint _deltaMode)
        {
            wheelEventHandler?.Invoke(_deltaX, _deltaY, _deltaZ, _deltaMode);
        }

        [UnmanagedCallersOnly]
        private static void ResizeEventDispatcher(int _width, int _height)
        {
            resizeEventHandler?.Invoke(_width, _height);
        }

        [UnmanagedCallersOnly]
        private static void KeyboardEventDispatcher(int _eventType, uint _keyCode, uint _charCode/*, bool _isCtrl, bool _isShift, bool _isAlt*/)
        {
            keyboardEventHandler?.Invoke(_eventType, _keyCode, _charCode/*, _isCtrl, _isShift, _isAlt*/);
        }

        [DllImport("webCanvasNative")]
        [DefaultDllImportSearchPaths(DllImportSearchPath.AssemblyDirectory)]
        private static extern bool webCanvas_initialise(string _canvasId);

        [DllImport("webCanvasNative")]
        [DefaultDllImportSearchPaths(DllImportSearchPath.AssemblyDirectory)]
        private static extern void webCanvas_registerEventsDispatchers(
            IntPtr _mouseEventsDispatcherPtr, 
            IntPtr _wheelEventDispatcherPtr,
            IntPtr _resizeEventDispatcherPtr,
            IntPtr _keyboardEventDispatcherPtr);

        [DllImport("webCanvasNative")]
        [DefaultDllImportSearchPaths(DllImportSearchPath.AssemblyDirectory)]
        private static extern void webCanvas_teardown();

        [DllImport("webCanvasNative")]
        [DefaultDllImportSearchPaths(DllImportSearchPath.AssemblyDirectory)]
        private static extern void webCanvas_getSize(out int _width, out int _height);

        [DllImport("webCanvasNative")]
        [DefaultDllImportSearchPaths(DllImportSearchPath.AssemblyDirectory)]
        private static extern void webCanvas_reSize(out int _width, out int _height);

        [DllImport("webCanvasNative")]
        [DefaultDllImportSearchPaths(DllImportSearchPath.AssemblyDirectory)]
        private static extern void webCanvas_setGraphicsContext();

	}
}