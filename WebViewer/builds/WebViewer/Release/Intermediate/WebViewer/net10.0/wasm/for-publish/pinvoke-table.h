// GENERATED FILE, DO NOT MODIFY (PInvokeTableGenerator.cs)
#include <mono/utils/details/mono-error-types.h>
#include <mono/metadata/assembly.h>
#include <mono/utils/mono-error.h>
#include <mono/metadata/object.h>
#include <mono/utils/details/mono-logger-types.h>
#include "runtime.h"
#include "pinvoke.h"

int32_t GlobalizationNative_GetCalendars (void *, void *, int32_t);

int32_t GlobalizationNative_GetLocaleInfoInt (void *, uint32_t, void *);

int32_t GlobalizationNative_GetLocaleTimeFormat (void *, int32_t, void *, int32_t);

int32_t GlobalizationNative_NormalizeString (int32_t, void *, int32_t, void *, int32_t);

int32_t SystemNative_Close (void *);

int32_t SystemNative_CloseDir (void *);

int32_t SystemNative_ConvertErrorPalToPlatform (int32_t);

int32_t SystemNative_ConvertErrorPlatformToPal (int32_t);

void * SystemNative_Dup (void *);

int32_t SystemNative_FAllocate (void *, int64_t, int64_t);

int32_t SystemNative_FLock (void *, int32_t);

int32_t SystemNative_FStat (void *, void *);

int32_t SystemNative_FSync (void *);

int32_t SystemNative_FTruncate (void *, int64_t);

void SystemNative_Free (void *);

int32_t SystemNative_GetCryptographicallySecureRandomBytes (void *, int32_t);

void * SystemNative_GetCwd (void *, int32_t);

void * SystemNative_GetEnv (void *);

int32_t SystemNative_GetErrNo ();

uint32_t SystemNative_GetFileSystemType (void *);

void SystemNative_GetNonCryptographicallySecureRandomBytes (void *, int32_t);

int32_t SystemNative_GetReadDirRBufferSize ();

int64_t SystemNative_GetSystemTimeAsTicks ();

void * SystemNative_GetTimeZoneData (void *, void *);

uint64_t SystemNative_GetTimestamp ();

int64_t SystemNative_LSeek (void *, int64_t, int32_t);

int32_t SystemNative_LStat (void *, void *);

void SystemNative_LowLevelMonitor_Acquire (void *);

void * SystemNative_LowLevelMonitor_Create ();

void SystemNative_LowLevelMonitor_Destroy (void *);

void SystemNative_LowLevelMonitor_Release (void *);

void SystemNative_LowLevelMonitor_Signal_Release (void *);

int32_t SystemNative_LowLevelMonitor_TimedWait (void *, int32_t);

void SystemNative_LowLevelMonitor_Wait (void *);

void * SystemNative_Malloc (void *);

void * SystemNative_Open (void *, int32_t, int32_t);

void * SystemNative_OpenDir (void *);

int32_t SystemNative_PRead (void *, void *, int32_t, int64_t);

int64_t SystemNative_PReadV (void *, void *, int32_t, int64_t);

int32_t SystemNative_PWrite (void *, void *, int32_t, int64_t);

int64_t SystemNative_PWriteV (void *, void *, int32_t, int64_t);

int32_t SystemNative_PosixFAdvise (void *, int64_t, int64_t, int32_t);

int32_t SystemNative_Read (void *, void *, int32_t);

int32_t SystemNative_ReadDirR (void *, void *, int32_t, void *);

int32_t SystemNative_ReadLink (void *, void *, int32_t);

int32_t SystemNative_SchedGetCpu ();

void SystemNative_SetErrNo (int32_t);

int32_t SystemNative_Stat (void *, void *);

void * SystemNative_StrErrorR (int32_t, void *, int32_t);

void SystemNative_SysLog (int32_t, void *, void *);

uint32_t SystemNative_TryGetUInt32OSThreadId ();

int32_t SystemNative_Unlink (void *);

int32_t SystemNative_Write (void *, void *, int32_t);

void TestAllocation (int32_t);

void webCanvas_getSize (void *, void *);

int32_t webCanvas_initialise (void *);

void webCanvas_reSize (void *, void *);

void webCanvas_registerEventsDispatchers (void *, void *, void *, void *);

void webCanvas_setGraphicsContext ();

void webCanvas_teardown ();

static PinvokeImport TestAllocation_imports [] = {
    {"TestAllocation", TestAllocation}, // WebViewer
    {NULL, NULL}
};

static PinvokeImport libSystem_Globalization_Native_imports [] = {
    {"GlobalizationNative_GetCalendars", GlobalizationNative_GetCalendars}, // System.Private.CoreLib
    {"GlobalizationNative_GetLocaleInfoInt", GlobalizationNative_GetLocaleInfoInt}, // System.Private.CoreLib
    {"GlobalizationNative_GetLocaleTimeFormat", GlobalizationNative_GetLocaleTimeFormat}, // System.Private.CoreLib
    {"GlobalizationNative_NormalizeString", GlobalizationNative_NormalizeString}, // System.Private.CoreLib
    {NULL, NULL}
};

static PinvokeImport libSystem_IO_Compression_Native_imports [] = {
    {NULL, NULL}
};

static PinvokeImport libSystem_Native_imports [] = {
    {"SystemNative_Close", SystemNative_Close}, // System.Private.CoreLib
    {"SystemNative_CloseDir", SystemNative_CloseDir}, // System.Private.CoreLib
    {"SystemNative_ConvertErrorPalToPlatform", SystemNative_ConvertErrorPalToPlatform}, // System.Console, System.Private.CoreLib
    {"SystemNative_ConvertErrorPlatformToPal", SystemNative_ConvertErrorPlatformToPal}, // System.Console, System.Private.CoreLib
    {"SystemNative_Dup", SystemNative_Dup}, // System.Console
    {"SystemNative_FAllocate", SystemNative_FAllocate}, // System.Private.CoreLib
    {"SystemNative_FLock", SystemNative_FLock}, // System.Private.CoreLib
    {"SystemNative_FStat", SystemNative_FStat}, // System.Private.CoreLib
    {"SystemNative_FSync", SystemNative_FSync}, // System.Private.CoreLib
    {"SystemNative_FTruncate", SystemNative_FTruncate}, // System.Private.CoreLib
    {"SystemNative_Free", SystemNative_Free}, // System.Private.CoreLib
    {"SystemNative_GetCryptographicallySecureRandomBytes", SystemNative_GetCryptographicallySecureRandomBytes}, // System.Private.CoreLib
    {"SystemNative_GetCwd", SystemNative_GetCwd}, // System.Private.CoreLib
    {"SystemNative_GetEnv", SystemNative_GetEnv}, // System.Private.CoreLib
    {"SystemNative_GetErrNo", SystemNative_GetErrNo}, // System.Private.CoreLib
    {"SystemNative_GetFileSystemType", SystemNative_GetFileSystemType}, // System.Private.CoreLib
    {"SystemNative_GetNonCryptographicallySecureRandomBytes", SystemNative_GetNonCryptographicallySecureRandomBytes}, // System.Private.CoreLib
    {"SystemNative_GetReadDirRBufferSize", SystemNative_GetReadDirRBufferSize}, // System.Private.CoreLib
    {"SystemNative_GetSystemTimeAsTicks", SystemNative_GetSystemTimeAsTicks}, // System.Private.CoreLib
    {"SystemNative_GetTimeZoneData", SystemNative_GetTimeZoneData}, // System.Private.CoreLib
    {"SystemNative_GetTimestamp", SystemNative_GetTimestamp}, // System.Private.CoreLib
    {"SystemNative_LSeek", SystemNative_LSeek}, // System.Private.CoreLib
    {"SystemNative_LStat", SystemNative_LStat}, // System.Private.CoreLib
    {"SystemNative_LowLevelMonitor_Acquire", SystemNative_LowLevelMonitor_Acquire}, // System.Private.CoreLib
    {"SystemNative_LowLevelMonitor_Create", SystemNative_LowLevelMonitor_Create}, // System.Private.CoreLib
    {"SystemNative_LowLevelMonitor_Destroy", SystemNative_LowLevelMonitor_Destroy}, // System.Private.CoreLib
    {"SystemNative_LowLevelMonitor_Release", SystemNative_LowLevelMonitor_Release}, // System.Private.CoreLib
    {"SystemNative_LowLevelMonitor_Signal_Release", SystemNative_LowLevelMonitor_Signal_Release}, // System.Private.CoreLib
    {"SystemNative_LowLevelMonitor_TimedWait", SystemNative_LowLevelMonitor_TimedWait}, // System.Private.CoreLib
    {"SystemNative_LowLevelMonitor_Wait", SystemNative_LowLevelMonitor_Wait}, // System.Private.CoreLib
    {"SystemNative_Malloc", SystemNative_Malloc}, // System.Private.CoreLib
    {"SystemNative_Open", SystemNative_Open}, // System.Private.CoreLib
    {"SystemNative_OpenDir", SystemNative_OpenDir}, // System.Private.CoreLib
    {"SystemNative_PRead", SystemNative_PRead}, // System.Private.CoreLib
    {"SystemNative_PReadV", SystemNative_PReadV}, // System.Private.CoreLib
    {"SystemNative_PWrite", SystemNative_PWrite}, // System.Private.CoreLib
    {"SystemNative_PWriteV", SystemNative_PWriteV}, // System.Private.CoreLib
    {"SystemNative_PosixFAdvise", SystemNative_PosixFAdvise}, // System.Private.CoreLib
    {"SystemNative_Read", SystemNative_Read}, // System.Private.CoreLib
    {"SystemNative_ReadDirR", SystemNative_ReadDirR}, // System.Private.CoreLib
    {"SystemNative_ReadLink", SystemNative_ReadLink}, // System.Private.CoreLib
    {"SystemNative_SchedGetCpu", SystemNative_SchedGetCpu}, // System.Private.CoreLib
    {"SystemNative_SetErrNo", SystemNative_SetErrNo}, // System.Private.CoreLib
    {"SystemNative_Stat", SystemNative_Stat}, // System.Private.CoreLib
    {"SystemNative_StrErrorR", SystemNative_StrErrorR}, // System.Console, System.Private.CoreLib
    {"SystemNative_SysLog", SystemNative_SysLog}, // System.Private.CoreLib
    {"SystemNative_TryGetUInt32OSThreadId", SystemNative_TryGetUInt32OSThreadId}, // System.Private.CoreLib
    {"SystemNative_Unlink", SystemNative_Unlink}, // System.Private.CoreLib
    {"SystemNative_Write", SystemNative_Write}, // System.Console, System.Private.CoreLib
    {NULL, NULL}
};

static PinvokeImport webCanvasNative_imports [] = {
    {"webCanvas_getSize", webCanvas_getSize}, // WebViewer
    {"webCanvas_initialise", webCanvas_initialise}, // WebViewer
    {"webCanvas_reSize", webCanvas_reSize}, // WebViewer
    {"webCanvas_registerEventsDispatchers", webCanvas_registerEventsDispatchers}, // WebViewer
    {"webCanvas_setGraphicsContext", webCanvas_setGraphicsContext}, // WebViewer
    {"webCanvas_teardown", webCanvas_teardown}, // WebViewer
    {NULL, NULL}
};

static PinvokeTable pinvoke_tables[] = {
    {"TestAllocation", TestAllocation_imports, 1},
    {"libSystem.Globalization.Native", libSystem_Globalization_Native_imports, 4},
    {"libSystem.IO.Compression.Native", libSystem_IO_Compression_Native_imports, 0},
    {"libSystem.Native", libSystem_Native_imports, 49},
    {"webCanvasNative", webCanvasNative_imports, 6}
};

InterpFtnDesc wasm_native_to_interp_ftndescs[7] = {};

void
wasm_native_to_interp_System_Private_CoreLib_System_Threading_ThreadPool_BackgroundJobHandler () {
    typedef void (*InterpEntry_T0) (int*);

    if (!(InterpEntry_T0)wasm_native_to_interp_ftndescs [0].func) {
        mono_wasm_marshal_get_managed_wrapper ("System.Private.CoreLib", "System.Threading", "ThreadPool", "BackgroundJobHandler", 100673061, 0);
    }

    ((InterpEntry_T0)wasm_native_to_interp_ftndescs [0].func) ((int*)wasm_native_to_interp_ftndescs [0].arg);
}

int32_t
wasm_native_to_interp_System_Private_CoreLib_Internal_Runtime_InteropServices_ComponentActivator_GetFunctionPointer (void * arg0, void * arg1, void * arg2, void * arg3, void * arg4, void * arg5) {
    typedef void (*InterpEntry_T1) (int*, int*, int*, int*, int*, int*, int*, int*);
    int32_t result;

    if (!(InterpEntry_T1)wasm_native_to_interp_ftndescs [1].func) {
        mono_wasm_marshal_get_managed_wrapper ("System.Private.CoreLib", "Internal.Runtime.InteropServices", "ComponentActivator", "GetFunctionPointer", 100663453, 6);
    }

    ((InterpEntry_T1)wasm_native_to_interp_ftndescs [1].func) ((int*)&result, (int*)&arg0, (int*)&arg1, (int*)&arg2, (int*)&arg3, (int*)&arg4, (int*)&arg5, (int*)wasm_native_to_interp_ftndescs [1].arg);
    return result;
}

void
wasm_native_to_interp_WebViewer_WebViewer_WebCanvasInterop_KeyboardEventDispatcher (int32_t arg0, uint32_t arg1, uint32_t arg2) {
    typedef void (*InterpEntry_T2) (int*, int*, int*, int*);

    if (!(InterpEntry_T2)wasm_native_to_interp_ftndescs [2].func) {
        mono_wasm_marshal_get_managed_wrapper ("WebViewer", "WebViewer", "WebCanvasInterop", "KeyboardEventDispatcher", 100663313, 3);
    }

    ((InterpEntry_T2)wasm_native_to_interp_ftndescs [2].func) ((int*)&arg0, (int*)&arg1, (int*)&arg2, (int*)wasm_native_to_interp_ftndescs [2].arg);
}

void
wasm_native_to_interp_WebViewer_WebViewer_WebCanvasInterop_MouseEventsDispatcher (int32_t arg0, int32_t arg1, int32_t arg2, int32_t arg3) {
    typedef void (*InterpEntry_T3) (int*, int*, int*, int*, int*);

    if (!(InterpEntry_T3)wasm_native_to_interp_ftndescs [3].func) {
        mono_wasm_marshal_get_managed_wrapper ("WebViewer", "WebViewer", "WebCanvasInterop", "MouseEventsDispatcher", 100663310, 4);
    }

    ((InterpEntry_T3)wasm_native_to_interp_ftndescs [3].func) ((int*)&arg0, (int*)&arg1, (int*)&arg2, (int*)&arg3, (int*)wasm_native_to_interp_ftndescs [3].arg);
}

void
wasm_native_to_interp_WebViewer_WebViewer_WebCanvasInterop_ResizeEventDispatcher (int32_t arg0, int32_t arg1) {
    typedef void (*InterpEntry_T4) (int*, int*, int*);

    if (!(InterpEntry_T4)wasm_native_to_interp_ftndescs [4].func) {
        mono_wasm_marshal_get_managed_wrapper ("WebViewer", "WebViewer", "WebCanvasInterop", "ResizeEventDispatcher", 100663312, 2);
    }

    ((InterpEntry_T4)wasm_native_to_interp_ftndescs [4].func) ((int*)&arg0, (int*)&arg1, (int*)wasm_native_to_interp_ftndescs [4].arg);
}

void
wasm_native_to_interp_System_Private_CoreLib_System_Threading_TimerQueue_TimerHandler () {
    typedef void (*InterpEntry_T5) (int*);

    if (!(InterpEntry_T5)wasm_native_to_interp_ftndescs [5].func) {
        mono_wasm_marshal_get_managed_wrapper ("System.Private.CoreLib", "System.Threading", "TimerQueue", "TimerHandler", 100673076, 0);
    }

    ((InterpEntry_T5)wasm_native_to_interp_ftndescs [5].func) ((int*)wasm_native_to_interp_ftndescs [5].arg);
}

void
wasm_native_to_interp_WebViewer_WebViewer_WebCanvasInterop_WheelEventDispatcher (double arg0, double arg1, double arg2, uint32_t arg3) {
    typedef void (*InterpEntry_T6) (int*, int*, int*, int*, int*);

    if (!(InterpEntry_T6)wasm_native_to_interp_ftndescs [6].func) {
        mono_wasm_marshal_get_managed_wrapper ("WebViewer", "WebViewer", "WebCanvasInterop", "WheelEventDispatcher", 100663311, 4);
    }

    ((InterpEntry_T6)wasm_native_to_interp_ftndescs [6].func) ((int*)&arg0, (int*)&arg1, (int*)&arg2, (int*)&arg3, (int*)wasm_native_to_interp_ftndescs [6].arg);
}

static UnmanagedExport wasm_native_to_interp_table[] = {
    {"BackgroundJobHandler#0:System.Private.CoreLib:System.Threading:ThreadPool", 100673061, wasm_native_to_interp_System_Private_CoreLib_System_Threading_ThreadPool_BackgroundJobHandler},
    {"GetFunctionPointer#6:System.Private.CoreLib:Internal.Runtime.InteropServices:ComponentActivator", 100663453, wasm_native_to_interp_System_Private_CoreLib_Internal_Runtime_InteropServices_ComponentActivator_GetFunctionPointer},
    {"KeyboardEventDispatcher#3:WebViewer:WebViewer:WebCanvasInterop", 100663313, wasm_native_to_interp_WebViewer_WebViewer_WebCanvasInterop_KeyboardEventDispatcher},
    {"MouseEventsDispatcher#4:WebViewer:WebViewer:WebCanvasInterop", 100663310, wasm_native_to_interp_WebViewer_WebViewer_WebCanvasInterop_MouseEventsDispatcher},
    {"ResizeEventDispatcher#2:WebViewer:WebViewer:WebCanvasInterop", 100663312, wasm_native_to_interp_WebViewer_WebViewer_WebCanvasInterop_ResizeEventDispatcher},
    {"TimerHandler#0:System.Private.CoreLib:System.Threading:TimerQueue", 100673076, wasm_native_to_interp_System_Private_CoreLib_System_Threading_TimerQueue_TimerHandler},
    {"WheelEventDispatcher#4:WebViewer:WebViewer:WebCanvasInterop", 100663311, wasm_native_to_interp_WebViewer_WebViewer_WebCanvasInterop_WheelEventDispatcher}
};
