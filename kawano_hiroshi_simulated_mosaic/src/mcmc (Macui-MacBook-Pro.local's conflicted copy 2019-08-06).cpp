#include "mcmc.hpp"

colAmount::colAmount(ofColor col)
:col(col), amount(1)
{}

colAmount& colAmount::operator++(){
    this->amount ++;
    return *this;
}

ofColor colAmount::getColor(){
    return col;
}

MCMC::MCMC(){
    //do nothing.
    //this class is not supposed to be used for making any instance.
}

void MCMC::parse(const Canvas* canvas, int order){
    init();
    const ofColor* pixels = canvas->getPixels();
    if(pixels == nullptr){
        cout<<"pixels you've just received in parse() function is nullptr"<<endl;
        return;
    }
    const int width = canvas->getWidth();
    const int height = canvas->getHeight();
    int offset = width*order;
    
    for(int y=offset; y<height; ++y){
        for(int x=0; x<width; ++x){
            int idx;
            vector<ofColor> temp;
            for(int z=0; z<order; ++z){
                idx = (y-order+z)*width + x;
                temp.push_back(pixels[idx]);
            }
            for(int z=0; z<order; ++z){
                idx = y*width + (x-order+z);
                temp.push_back(pixels[idx]);
            }
            idx = y*width + x;
            addToList(temp, pixels[idx]);
        }
    }
}

void MCMC::init(){
//    pixels = nullptr;
//    width = 0;
    col_list = vector<vector<ofColor>>();
    ca_list = vector<vector<colAmount>>();
}

void MCMC::addToList(vector<ofColor> tList, ofColor myCol){
    for(int i=0; i<col_list.size(); ++i){
        if(tList == col_list.at(i)){
            addToCaList(i, myCol);
            return;
        }
    }
    col_list.push_back(tList);
    vector<colAmount> temp;
    temp.push_back(colAmount(myCol));
    ca_list.push_back(temp);
}

void MCMC::addToCaList(int idx, ofColor col){
    vector<colAmount>& list = ca_list.at(idx);
    for(int i=0; i<list.size(); ++i){
        colAmount& ca = list.at(i);
        if(ca.getColor() == col){
            ++ca;
            return;
        }
    }
    list.push_back(colAmount(col));
}

void MCMC::printstat()
