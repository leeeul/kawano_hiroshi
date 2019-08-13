#ifndef canvasControlloer_hpp
#define canvasControlloer_hpp

#include <stdio.h>
#include "canvas.hpp"
#include "mcmc.hpp"

class CanvasController{
    static CanvasController* instance;
    const int maxLeng_list;
//    int leng; // size of textureList
    Canvas** list;
    Canvas* result;
    ofVec2f size;
    int pixelSize;
    vector<ofColor> colPool; //

    CanvasController(ofVec2f, int);
    void deleteList();
    void deleteInstance();
    void deleteResult();
    virtual ~CanvasController();
    ofColor correctCol(const ofColor&); //
    
    vector<ofTexture> textureList;
    
public:
    static CanvasController* getInstance(ofVec2f, int);
    void releaseInstance();
    
    void parse(int, int);
    void show(int);
    void showResult();
    void create();
    CanvasController& addPool(const ofColor&); //
    
    void allocateTexture(const ofTexture&);
    int getTextureAmount();
};

#endif /* canvasControlloer_hpp */
