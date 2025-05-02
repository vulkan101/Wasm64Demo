function getQueryParam(param) {
    const urlParams = new URLSearchParams(window.location.search);
    return urlParams.get(param);
}

// Function to load a CSS file based on the 'theme' query parameter
function loadCSS(dev) {
    const link = document.createElement('link');
    link.rel = 'stylesheet';
    link.type = 'text/css';
    if (dev) {        
        link.href ='css/dev_app.css'; // Dynamically set CSS file based on query parameter        
    } else {
        // Load a default css if no 'debug' parameter is provided        
        link.href = 'css/app.css'; // Load a default CSS file        
    }
    document.head.appendChild(link);
}

// Load the CSS based on the 'debug' query parameter
const devParam = getQueryParam('dev');
var isDev = (devParam?.toLowerCase?.() === 'true');
loadCSS(isDev);