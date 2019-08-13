#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    canvas = new Canvas(500, 500, 10);
    canvas->setAll(ofColor(255,0,0));
    
//    vector<int> l1;
//    vector<int> l2;
//    l1.push_back(1);
//    l1.push_back(2);
//    l2.push_back(2);
//    l2.push_back(1);
//    
//    if(l1==l2){
//        cout<<"same"<<endl;
//    }
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
    canvas->draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    canvas->setFromMouse(ofVec2f(x, y), ofColor(0,255,0));
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
