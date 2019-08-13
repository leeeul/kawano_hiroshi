#ifndef mcmc_hpp
#define mcmc_hpp

#include <stdio.h>
#include "ofMain.h"
#include "canvas.hpp"

struct colAmount{
    ofColor col;
    int amount;
public:
    colAmount(ofColor);
    colAmount& operator++();
    ofColor getColor();
};

class MCMC{
    MCMC();
//    static ofColor* pixels;
//    static int width;
    static vector<vector<ofColor>> col_list;
    static vector<vector<colAmount>> ca_list;
    static void init();
    static void addToList(vector<ofColor>, ofColor);
    static void addToCaList(int idx, ofColor col);
public:
    static void parse(const Canvas*, int order);
    static Canvas create();
    static void printstat();
    
//    virtual ~MCMC();
};

#endif /* mcmc_hpp */
