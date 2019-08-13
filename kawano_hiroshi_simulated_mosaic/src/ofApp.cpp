#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    size = ofVec2f(500,500);
    pixelSize = 10;
    int pageIdx = 0;
    
    created = false;
    
    canvases = CanvasController::getInstance(size, pixelSize);
    canvases->
    addPool(ofColor(199,37,21))
    .addPool(ofColor(222,194,76)) //yellow
    .addPool(ofColor::darkBlue) //dark blue
    .addPool(ofColor(230,230,230))
    .addPool(ofColor(205,218,231)) //whity blue
    .addPool(ofColor(39,134,42)) //green
    .addPool(ofColor(250,114,2)) //orange
    .addPool(ofColor::black);
    
    ofLoadImage(tex, "mondrian.jpg");
    
    canvases->allocateTexture(tex);
    //you can also add more textures to canvases.
    //i set the maximum texture capacity to 8.
}

//--------------------------------------------------------------
void ofApp::update(){
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    if(created){
        canvases->showResult();
    }else{
        canvases->show(pageIdx);
    }    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if(key=='p'){
        canvases->parse(pageIdx, ORDER);
    }else if(key=='d'){
        canvases->create();
        created = true;
        return;
    }else if(key==OF_KEY_RIGHT){
        pageIdx = pageIdx+1>=canvases->getTextureAmount() ? pageIdx : pageIdx + 1 ;
    }else if(key==OF_KEY_LEFT){
        pageIdx = pageIdx-1<0 ? pageIdx : pageIdx - 1;
    }
    created = false;
}

void ofApp::exit(){
    canvases->releaseInstance();
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
    
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
//    canvas->setFromMouse(ofVec2f(x, y), ofColor(255,255,255));
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
//    canvas->setFromMouse(ofVec2f(x, y), ofColor(255,255,255));
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
//    canvas->setArea(rPoint1, rPoint2);
}
