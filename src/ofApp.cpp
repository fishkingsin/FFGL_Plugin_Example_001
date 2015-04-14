#include "ofApp.h"
#include <dlfcn.h> // for getExecutableFile() and related

extern CFFGLPluginInfo* g_CurrPluginInfo;
//--------------------------------------------------------------
ofApp::ofApp(int minInputs, int maxInputs )
{
    maxR = 50;
    addFloatParameter("Radius",&maxR,1,100);
    numStep = 10;
    addFloatParameter("Step",&numStep,1,360);
    n = 100;
    addFloatParameter("NumberOfCircle",&n,1,360);
    theInitSzie = 50;
    addFloatParameter("theInitSzie",&theInitSzie,1,100);
    increasement = 0.25;
    addFloatParameter("Increasment",&increasement,0,0.5);
    
//    addFloatParameter("Repetitions",	// name of parameter ( as it will appear in host )
//                      &numRepeats,      // address of the float this parameter will point to
//                      1,				// minimum value
//                      20				// maximum value
//                      );
    initParameters();
}
const char* getExecutableFile()
{
    Dl_info exeInfo;
    dladdr((void*) getExecutableFile, &exeInfo); // quite a weird construct but totally legit :)
    return exeInfo.dli_fname;
}


//--------------------------------------------------------------
ofApp::~ofApp()
{
    
}
//--------------------------------------------------------------

void ofApp::setup(){
    string strExecFile(getExecutableFile());
    int found = strExecFile.find_last_of("/");
    string strPath = strExecFile.substr(0, found) + "/data/";
    
    // Change the working directory to that of the data folder
    //chdir(strPath.c_str());
    ofSetDataPathRoot(strPath.c_str());
    fbo.allocate(ofGetWidth(), ofGetHeight());
    
    char buffer[10];
    sprintf(buffer, "%d.%03d", g_CurrPluginInfo->GetPluginExtendedInfo()->PluginMajorVersion,
            g_CurrPluginInfo->GetPluginExtendedInfo()->PluginMinorVersion);
    debugText = string("FFGL Test 2014\n plugin V") + string(buffer);

}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){

    ofTexture * tex = inputTextures[0];
    if( !tex )        return;
    fbo.begin();
    ofClear(0);
    trianglate.reset();
    
    int centerX = ofGetWidth()*0.5;
    int centerY = ofGetHeight()*0.5;
    float step = 0;
    count+=increasement;
    numStep=sin((ofGetElapsedTimef()-startTime)*increasement*TWO_PI)*360;
    float initSzie = theInitSzie;
    ofNoFill();
    for(int i = 0 ; i < n ; i++)
    {
        step+=numStep;
        float x = sin(((step)/n)*TWO_PI)*maxR*(step/n)*0.25 + ofGetWidth()*0.5;
        float y = cos(((step)/n)*TWO_PI)*maxR*(step/n)*0.25 + ofGetHeight()*0.5;
        ofPushStyle();
        ofCircle(x, y,50* MAX(1,centerX - ofDist(centerX, centerY, x,y))/centerX);
        ofPopStyle();
        trianglate.addPoint(ofPoint(x,y));
    }
    ofPushStyle();
    ofNoFill();
    trianglate.triangulate();
    trianglate.draw();
    ofPopStyle();

    fbo.end();
        ofSetColor( 255, 255, 255 );
    fbo.draw(0, 0);
}
void ofApp::onParameterChanged(ofPtr<ofFFGLParameter>)
{
    // Do something if you wish
}