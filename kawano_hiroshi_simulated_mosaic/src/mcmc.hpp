#ifndef mcmc_hpp
#define mcmc_hpp

#include <stdio.h>
#include "ofMain.h"
#include "canvas.hpp"

struct colAmount{
    ofColor col;
    int amount;
    
public:
    colAmount(const ofColor&);
    colAmount& operator++();
    const ofColor& getCol() const;
    int getAmount() const;
};

class MCMC{
    MCMC(); //this class is not supposed to be used for making any instance.
    static vector<vector<ofColor>> list;
    static vector<vector<colAmount>> caList;
    static vector<ofColor> buffer;
    static vector<colAmount> colorPool;
    static int order;
    static float errorSum;
    
    static void init();
    static void addToList(const vector<ofColor>&, const ofColor&);
    static void addToCaList(int idx, const ofColor& col);
    
    static void bufferSet(const Canvas*);
    static void canvasDelay(int width, int height);
    static int findIdx(const vector<ofColor>&);
    static const ofColor& monteCarlo(int idx);
    static void addToPool(const ofColor&);
    static const ofColor getMostCol();
public:
    static void parse(const Canvas*, int order);
    static void draw(Canvas*);
    static void printStat();
    
//    virtual ~MCMC();
};

#endif /* mcmc_hpp */
