
using Microsoft.AspNetCore.Components;
using Microsoft.AspNetCore.Components.Web;
using Microsoft.AspNetCore.WebUtilities;
using Microsoft.JSInterop;

using System.Text;

namespace WebViewer.Components
{
    public partial class WebView : ComponentBase, IAsyncDisposable
    {
        private static int instanceCount = 0;
        private static bool isInitialising = false;
        private static bool isDisposing = false;
        private static int initialiseQueueCount = 0;        
        private static int disposeQueueCount = 0;        
        private static Guid recentRequentGuid = Guid.Empty;
        private static readonly string canvasId = "webViewRenderCanvas";
        private static WebView? webViewInstance = null;
        private readonly bool enableFPSLogging = false;

        private System.Diagnostics.Stopwatch? timer = null;
        
        private long prevTicks;
        private long prevFpsTicks;
        private double accumulatedTime = 0;
        private double singleFrameTime;
        private static bool engineLogEnabled = true;
        private IJSObjectReference? jsInteropModule;
        private bool restartEngine = false;
        private bool firstFrameRendered = false;
        private LogLevel logLevel;
        Guid instanceGuid = Guid.NewGuid();
        private const int waitTime = 500;


        [Inject]
        public required ILogger<WebView> Logger { get; set; }

        [Inject]
        public required NavigationManager NavigationManager { get; set; }

        [Inject]
        public required IJSRuntime JS { get; set; }

        [Inject]
        public IConfiguration Config { get; set; }

               
        protected override async Task OnInitializedAsync()
        {
            webViewInstance = this;            
			await base.OnInitializedAsync();
        }

        // This function is called by the Blazor framework to decide to whether BuildRenderTree()(Blazor internal function to render the web page) 
        // should be called or not. https://blazor-university.com/components/component-lifecycles/
        // So it should return true, if there is any change in the logicEngine also if there are any changes in the Browser 
        // visibility like Browser minimize or maximize or resize etc. 
        protected override bool ShouldRender()
        {
            return true;
        }

        protected override async Task OnAfterRenderAsync(bool firstRender)
        {
            if (firstRender || restartEngine)
            {
                recentRequentGuid = instanceGuid;                
                initialiseQueueCount += 1;
                
                while (isInitialising || isDisposing || instanceCount > 0)
                {
                    LogDebug($"OnAfterRenderAsync isInitialising:{isInitialising} isDisposing:{isDisposing} InstanceCount:{instanceCount} waiting to initialise {instanceGuid} recent request guid: {recentRequentGuid} queueCount: {initialiseQueueCount}");
                    if (instanceGuid != recentRequentGuid)
                    {
                        initialiseQueueCount -= 1;
                        LogDebug($"Skipping initialisation of {instanceGuid} InstanceCount:{instanceCount}");

                        return;
                    }                        
                    await Task.Delay(waitTime);
                }                
                
                isInitialising = true;                
                
				ReadAppParameters();

				LogDebug($"OnAfterRenderAsync initialising {instanceGuid}");
                
                instanceCount += 1;
                isInitialising = false;
                initialiseQueueCount -= 1;                
                LogDebug($"Initialised instance :{instanceGuid}");

                await Task.Run(async () =>
                {
                    while (true)
                    {
                        await Task.Delay(TimeSpan.FromMilliseconds(15));
                        StateHasChanged();
                    }
                });

            }

            Step();
        }

        public async ValueTask DisposeAsync()
        {
            try
            {
                
                disposeQueueCount += 1;
                
                while (isInitialising || isDisposing)
                {
                    LogWarning($"DisposeAsync isInitialising:{isInitialising} isDisposing:{isDisposing} waiting to dispose :{instanceGuid}  dispose queueCount: {disposeQueueCount}");
                    await Task.Delay(waitTime);
                }               
               
                LogDebug($"DisposeAsync Disposing :{instanceGuid}  dispose queueCount: {disposeQueueCount}");
                
                isDisposing = true;                
                                                                                                
                LogDebug($"Disposed instance :{instanceGuid}");  
                
                disposeQueueCount -= 1;                                
                isDisposing = false;
            }
            catch (Exception ex)
            {                
                isDisposing = false;
                LogError($"Error while disposing instance: {instanceGuid} ", ex.Message );                
            }
        }

        private void ReadAppParameters()
        {            
            //Default log level is Warning
            logLevel = LogLevel.Warning;
            var dev = ExtractQueryParam("dev");            
            bool.TryParse(dev, out bool isDev);
            logLevel = isDev ? LogLevel.Information : logLevel;

            var debug = ExtractQueryParam("debug");
            bool.TryParse(debug, out bool isDebug);
            logLevel = isDebug ? LogLevel.Debug : logLevel;
        }
        private string? ExtractQueryParam(string paramName)
        {
            var uri = NavigationManager.ToAbsoluteUri(NavigationManager.Uri);

            if (QueryHelpers.ParseQuery(uri.Query).TryGetValue(paramName, out var paramValue))
                return paramValue.First();

            return null;
        }

        
        private string AppendDateTime(string message, string type)
        {
            message = string.Format("{0:G}", DateTime.Now) + " : [" + type + "]" + message;  // "3/9/2008 4:05:07 PM"
            return message;
        }
        private void LogDebug(string message, params object?[] args)
        {
            if (logLevel <= LogLevel.Debug)
            {
                message = AppendDateTime(message, "Debug");
                Logger.LogDebug(message, args);
                WriteToLogWindow(message, false, args);
            }
        }
        private void LogInformation(string message, params object?[] args)
        {
            if (logLevel <= LogLevel.Information)
            {
                message = AppendDateTime(message, "Info");
                Logger.LogInformation(message, args);
                WriteToLogWindow(message, false, args);
            }
        }
        private void LogWarning(string message, params object?[] args)
        {
            if (logLevel <= LogLevel.Warning)
            {
                message = AppendDateTime(message, "Warning");
                message = $"{message} instance: {instanceGuid}";
                Logger.LogWarning(message, args);
                WriteToLogWindow(message, false, args);
            }
        }
        internal void LogError(string message, params object?[] args)
        {
            if (logLevel <= LogLevel.Error)
            {
                message = AppendDateTime(message, "Error");
                message = $"{message} instance: {instanceGuid}";
                Logger.LogError(message, args);
                WriteToLogWindow(message, true, args);
            }
        }
        private void LogCritical(string message, params object?[] args)
        {
            if (logLevel <= LogLevel.Critical)
            {
                message = AppendDateTime(message, "Critical");
                message = $"{message} instance: {instanceGuid}";
                Logger.LogCritical(message, args);
                WriteToLogWindow(message, true, args);
            }
        }
                
        internal void SendCommandResult(string message)
        {
            _ = webViewInstance?.InvokeJSCallback("commandResultCallback", message);
            LogInformation(message);
        }

        internal void SendCommandError(string message)
        {
            _ = webViewInstance?.InvokeJSCallback("errorCallback", message);
            LogError(message);
        }
        internal void SendCommandNotification(string message)
        {
            _ = webViewInstance?.InvokeJSCallback("notificationCallback", message);
            LogInformation(message);

        }

        internal void WriteToLogWindow(string message, bool isError, params object?[] args)
        {
            try
            {
                if (jsInteropModule == null || webViewInstance == null)
                    return;

                StringBuilder sb = new StringBuilder();
                sb.Append(message);
                foreach (var arg in args)
                {
                    sb.Append(arg);
                }
                JS.InvokeVoidAsync("logMessage", sb.ToString(), isError);
            }
            catch (Exception ex)
            {
                LogError("Unexpected error", ex.Message);
            }
        }
        private void Step()
        {
            // Rather aggressive memory allocation testing...
			TestAllocationInterop.Allocate(1);			           
        }

        #region JS Communication Interop        
        public async ValueTask InvokeJSCallback(string callbackName, string result)
        {
            if (jsInteropModule == null)
            {
                LogError("JS Engine Interop Module is not initialized.");
                return;
            }

            await jsInteropModule.InvokeVoidAsync(callbackName, result);
        }
        #endregion

        
    }
}