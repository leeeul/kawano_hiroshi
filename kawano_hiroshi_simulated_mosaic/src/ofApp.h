#pragma once

#include "ofMain.h"
#include "canvasController.hpp"
#include "mcmc.hpp"

#define ORDER 2
class ofApp : public ofBaseApp{
    ofVec2f size;
    int pixelSize;
    
    CanvasController* canvases;
    //canvases have to be released, when this program ends.
    ofTexture tex;
    int pageIdx;
    
    bool created;
    
public:
    void setup();
    void update();
    void draw();
    
    void keyPressed(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void exit();
};

