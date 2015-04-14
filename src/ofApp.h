#pragma once

#include "ofMain.h"
#include "ofxFFGLPlugin.h"
#include "ofxDelaunay.h"
class ofApp : public ofFFGLPlugin{

	public:
    ofApp(int minInputs = 1, int maxInputs = 1);
    virtual ~ofApp();
		void setup();
		void update();
		void draw();
        void onParameterChanged(ofPtr<ofFFGLParameter>);

    ofFbo fbo;
    string debugText;
    ofxDelaunay trianglate;
    
    float maxR;
    float numStep;
    float n;
    float startTime;
    float theInitSzie;
    float increasement;
    float count;

};
