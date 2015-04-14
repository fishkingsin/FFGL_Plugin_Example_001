#include "ofMain.h"
#include "ofApp.h"

// Here is the main difference between a normal openFrameworks app and a OF FFGL plugin:

// This defines the creation function for our plugin parameters:

// minInputs: minimum number of inputs ( textures )
// maxInputs: maximum number of inputs ( textures )

const int minInputs = 1;
const int maxInputs = 1;

/// Plugin creation call. With Visual Studio __stdcall does not compile
#ifdef OF_FFGL_NOSTDCALL
DWORD createPluginInstance(CFreeFrameGLPlugin **ppInstance)
{
    ofFFGLPlugin * plug = new pluginApp(minInputs, maxInputs);
    *ppInstance = plug;
    return FF_SUCCESS;
}
#else
DWORD __stdcall createPluginInstance(CFreeFrameGLPlugin **ppInstance)
{
    ofFFGLPlugin * plug = new ofApp(minInputs, maxInputs);
    assert(plug != NULL);
    *ppInstance = plug;
    return FF_SUCCESS;
}
#endif

// FFGL Plugin Info Structure
// Insert the info that will appear on the host here
// !!! Do not change fields marked with *

static CFFGLPluginInfo PluginInfo (
   createPluginInstance,                       // * Create method
   "FKPE1",                                     // Plugin unique ID
   "FFGL_Plugin_Example_001",                           // Plugin name
   1,                                          // * API major version number
   1,                                        // * API minor version number
   1,                                          // Plugin major version number
   1,                                         // Plugin minor version number
   FF_EFFECT,                                  // Plugin type FF_SOURCE or FF_EFFECT ( filters )
   "OpenFrameworks + FFGL Plugin Example 001",        // Plugin description
   "by James Kong' - fishkingsin@gmail.com"	// About
   ,0                                          // *
   ,NULL                                       // *
);
