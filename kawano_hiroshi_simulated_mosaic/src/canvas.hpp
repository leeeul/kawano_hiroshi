#ifndef canvas_hpp
#define canvas_hpp

#include <stdio.h>
#include "ofMain.h"

class Canvas{
    ofVec2f size;
    int pixelLeng;
    ofColor* pixels;
    float pixelSize;
    
    int xytoidx(int x, int y) const;
    int getLeng();
    
public:
    Canvas(int width, int height, int pixelSize);
    void setFromMouse(const ofVec2f& mouse, const ofColor& col);
    void setArea(const ofVec2f& p1, const ofVec2f& p2);
    void set(int x, int y, const ofColor& col);
    void set(const ofColor*, int len);
    void setAll(const ofColor& col);
    const ofColor& get(int x, int y) const;
    void draw();
    const ofColor* getPixels() const;
    int getWidth() const;
    int getHeight() const;
    virtual ~Canvas();
};

#endif
