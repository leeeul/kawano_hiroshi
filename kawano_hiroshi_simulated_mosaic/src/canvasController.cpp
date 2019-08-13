#include "canvasController.hpp"
#define cc CanvasController

cc* cc::instance = nullptr;

cc::cc(ofVec2f size, int pixelSize)
:
maxLeng_list(8),
list(new Canvas*[maxLeng_list]),
size(size),
pixelSize(pixelSize),
result(new Canvas(size.x, size.y, pixelSize))
{
    for(int i=0; i<maxLeng_list; ++i){
        list[i] = nullptr;
    }
    colPool = vector<ofColor>();
    textureList = vector<ofTexture>();
    result->setAll(ofColor(255,255,255));
}

cc* cc::getInstance(ofVec2f size, int pixelSize){
    if(instance == nullptr){
        instance = new cc(size, pixelSize);
    }
    
    return instance;
}

void cc::parse(int idx, int order){
    if(idx>=textureList.size()){
        cout<<"no texture at "<<idx<<" index."<<endl;
        return;
    }
    
    ofPixels pix;
    textureList.at(idx).readToPixels(pix);
    
    bool b = (pix.getWidth()==size.x) && (pix.getHeight()==size.y);
    if(!b)
        pix.resize(size.x, size.y);
    
    
    if(list[idx]==nullptr){
        list[idx] = new Canvas(size.x, size.y, pixelSize);
        int w = size.x/pixelSize;
        int h = size.y/pixelSize;
        int tempLeng = int(w*h);
        ofColor* colList = new ofColor[tempLeng];
        for(int y=0; y<h; ++y){
            for(int x=0; x<w; ++x){
                int tidx = y*w + x;
                const ofColor& col = correctCol(pix.getColor(x*pixelSize+pixelSize*0.5, y*pixelSize+pixelSize*0.5));
            colList[tidx] = col;
            }
        }
    
        list[idx] -> set(colList, tempLeng);
        delete[] colList;
        colList = nullptr;
    }
    
    MCMC::parse(list[idx], order);
}

ofColor cc::correctCol(const ofColor& col){
    int poolLeng = colPool.size();
    if(poolLeng<=0){
        return ofColor(0,0,0);
    }
    
    int md2 = 2e5;
    int idx = 0;
    for(int i=0; i<poolLeng; ++i){
        const ofColor& tCol = colPool.at(i);
        int dr = tCol.r-col.r;
        int dg = tCol.g-col.g;
        int db = tCol.b-col.b;
        int result = dr*dr + dg*dg + db*db;
        if(result>=md2) continue;
        md2 = result;
        idx = i;
    }
    return colPool.at(idx);
}

cc& cc::addPool(const ofColor& col){
    colPool.push_back(col);
    return *this;
}

void cc::show(int idx){
    if(idx<0 || idx>=textureList.size()){
        cout<<"no canvas data at "<<idx<<" index"<<endl;
        return;
    }
    
    if(list[idx]==nullptr){ //not parsed yet
        ofSetColor(255);
        textureList.at(idx).draw(0, 0, size.x, size.y);
    }else{
        list[idx]->draw();
    }
}

void cc::allocateTexture(const ofTexture& tex){
    int l = textureList.size();
    if(l>=maxLeng_list){
        cout<<"not enough length of list in CanvasController"<<endl;
        cout<<"please set the maxLeng_list larger"<<endl;
        return;
    }
    
    textureList.push_back(tex);
}

void cc::showResult(){
    if(result==nullptr){
        result = new Canvas(size.x, size.y, pixelSize);
        result->setAll(ofColor(255,255,255));
    }
    result->draw();
}

void cc::create(){
    if(result==nullptr){
        result = new Canvas(size.x, size.y, pixelSize);
    }
    MCMC::draw(result);
}

cc::~cc(){
}

void cc::releaseInstance(){
    deleteList();
    deleteResult();
    deleteInstance();
}

void cc::deleteList(){
    if(list==nullptr)
        return;
    
    for(int i=0; i<maxLeng_list; ++i){
        if(list[i] == nullptr) continue;
        delete list[i];
        list[i] = nullptr;
    }
    delete[] list;
    list = nullptr;
}

void cc::deleteInstance(){
    if(instance==nullptr)
        return;
    
    delete instance;
    instance = nullptr;
}

void cc::deleteResult(){
    if(result==nullptr)
        return;
    
    delete result;
    result = nullptr;
}

int cc::getTextureAmount(){
    return textureList.size();
}

