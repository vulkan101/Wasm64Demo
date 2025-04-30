
let shutdownRestartAreaInnerHtml = '<button id="engine-shutdown" class="engine-shutdown">Engine Shutdown</button><button id="engine-restart" class="engine-restart">Engine Restart</button>';
let showRemoveAddButtons = true;
let maxLogLines = 1000;
let isEngineReady = false;
let isEngineDisposed = true;
let instanceCounter = 0;
const allLogs = [];
const errorLogs = [];
let showOnlyErrors = false;
shutdownRestartAreaInnerHtml = '<button id="engine-shutdown" class="engine-shutdown">Engine Shutdown</button><button id="engine-restart" class="engine-restart">Engine Restart</button><button id="remove-app">Remove-3DViewer</button><button id="add-app">Add-3DViewer</button>';
let instanceCount = 1;

// Insert content based on the 'content' parameter
insertContent(isDev);

//Comment this line to simulate AIM use case(Adding and removing web-viewer on demand)
initialiseWebViewer();

// Function to insert content into the div
function insertContent(dev) {
    if (dev) {
        const logAreaDiv = document.getElementById('logArea');
        // Insert the content into the div
        //<input type="checkbox" id="showEngineLog" checked />
        //<label for="showEngineLog"> Show engine log</label>
        //<input type="checkbox" id="onlyErrors" />
        //<label for="onlyErrors">Only errors</label><br>
        //<textarea id="log-output" placeholder="Log" resize="none" readonly="true" style="width: 100%"></textarea>
        logAreaDiv.innerHTML = '<input type="checkbox" id="showEngineLog" checked /> <label for="showEngineLog">Show engine log</label><input type="checkbox" id="onlyErrors" name="onlyErrors" /><label for="onlyErrors">Only errors</label> <br><textarea id="log-output" placeholder="Log" resize="none" readonly="true" style="width: 100%"></textarea>';
                
    }
}
function removeWebViewer() {
    
    var blazorApps = document.getElementsByClassName('blazorApp');

    while (blazorApps[0]) {
        blazorApps[0].parentNode.removeChild(blazorApps[0]);
    }
}
function logMessage(message, isError) {
    if (message === "" || message === "{}") {
        return;
    }
    
    if (isError) {
        allLogs.push(message);
        errorLogs.push(message);
    }
    else {
        allLogs.push(message);
    }

    if (allLogs.length > maxLogLines) {
        allLogs.splice(0, allLogs.length - maxLogLines);
    }

    if (errorLogs.length > maxLogLines) {
        errorLogs.splice(0, errorLogs.length - maxLogLines);
    }

    writeToWindow();
}
function writeToWindow() {
    const textEdit = document.getElementById('log-output');

    if (textEdit == null)
        return;

    if (showOnlyErrors) {
        textEdit.value = errorLogs.join('\n');
    }
    else {
        textEdit.value = allLogs.join('\n');
    }

    textEdit.scrollTop = textEdit.scrollHeight;
}
async function initialiseWebViewer() {
    
    const leftZoneDiv = document.getElementById("blazor-app");

    //Remove previous instance,if any
    removeWebViewer();
    
    isEngineReady == false;

    //Start blazor if required
    if (window.Blazor && window.Blazor.isInitialized) {
        //Do nothing
    } else {
        //Start Blazor
        Blazor.start();
        window.Blazor.isInitialized = true;
    }
    
    //Add Web-Viewer
    const webView = document.createElement("web-viewer");
    webView.setAttribute("id", "blazor-component");
    webView.setAttribute("class", "blazorApp");

    webView.innerHTML = "This is some text inside the web-viewer element.";

    leftZoneDiv.appendChild(webView);                
}

function registerCanvasEvents(target) {
    target.setAttribute("tabindex", "0");
    registerEventsOnCanvas(target, sendJsonRpcToEngine);
}

function randomNumberBetween(min, max) { // min and max included 
    return Math.floor(Math.random() * (max - min + 1) + min);
}


