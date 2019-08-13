#include "canvas.hpp"

int Canvas::xytoidx(int x, int y) const{
    int w = size.x/pixelSize;
    return y*w+x;
}

Canvas::Canvas(int width, int height, int pixelSize)
:size(ofVec2f(width, height)),
pixels(nullptr),
pixelSize(pixelSize)
{
    if(width%pixelSize==0 && height%pixelSize==0){
        pixelLeng = int(width/pixelSize*height/pixelSize);
        pixels = new ofColor[pixelLeng];
    }else{
        cout<<"please set the pixelSize correctly."<<endl;
        cout<<"pixelSize must be a divisor of canvas size."<<endl;
    }
}

void Canvas::set(int x, int y, const ofColor& col){
    if(pixels==nullptr)
        return;
    
    pixels[xytoidx(x, y)]
    = col;
}

void Canvas::set(const ofColor* colList, int len){
    if(colList==nullptr)
        return;
    if(len!=pixelLeng){
        cout<<"The length of the list you wish to copy to the canvas is not the same as the one in canvas"<<endl;
        cout<<"please check set(const ofColor*, int) function in Canvas class"<<endl;
        return;
    }
    for(int i=0; i<pixelLeng; ++i){
        pixels[i] = colList[i];
    }
}

void Canvas::setFromMouse(const ofVec2f& mouse, const ofColor& col){
    if(pixels==nullptr)
        return;
    if(mouse.x<0 || mouse.x>size.x)
        return;
    if(mouse.y<0 || mouse.y>size.y)
        return;
    
    int xidx = mouse.x/pixelSize;
    int yidx = mouse.y/pixelSize;
    
    set(xidx, yidx, col);
}

void Canvas::setArea(const ofVec2f& p1, const ofVec2f& p2){
    if(pixels==nullptr)
        return;
    
    ofVec2f mp1, mp2;
    mp1.x = int(p1.x / pixelSize);
    mp1.y = int(p1.y / pixelSize);
    mp2.x = int(p2.x / pixelSize);
    mp2.y = int(p2.y / pixelSize);
    
    for(int y=0; y<getHeight(); ++y){
        for(int x=0; x<getWidth(); ++x){
            float tx = (mp1.x-x)*(mp2.x-x);
            float ty = (mp1.y-y)*(mp2.y-y);
            
            if(tx<0 && ty<0){
                ofColor& col = pixels[xytoidx(x, y)];
                col = ofColor(255,255,255)-col;
            }
        }
    }
}

void Canvas::setAll(const ofColor& col){
    if(pixels==nullptr)
        return;
    
    for(int i=0; i<pixelLeng; ++i){
        pixels[i] = col;
    }
}

const ofColor& Canvas::get(int x, int y) const{
    if(pixels==nullptr)
        return;
    
    return pixels[xytoidx(x, y)];
}

void Canvas::draw(){
    if(pixels==nullptr)
        return;
    
    ofSetRectMode(OF_RECTMODE_CORNER);
    int xMax = size.x/pixelSize;
    int yMax = size.y/pixelSize;
    for(int y=0; y<yMax; ++y){
        for(int x=0; x<xMax; ++x){
            ofVec2f loc = ofVec2f(x, y)*pixelSize;
            ofSetColor(pixels[xytoidx(x, y)]);
            ofDrawRectangle(loc, pixelSize, pixelSize);
        }
    }
}

int Canvas::getLeng(){
    return pixelLeng;
}

Canvas::~Canvas(){
    if(pixels==nullptr){
        return;
    }
    
    delete[] pixels;
    pixels = nullptr;
    cout<<"Canvas's just been deleted"<<endl;
}

const ofColor* Canvas::getPixels() const{
    return pixels;
}

int Canvas::getWidth() const{
    return size.x/pixelSize;
}

int Canvas::getHeight() const{
    return size.y/pixelSize;
}
