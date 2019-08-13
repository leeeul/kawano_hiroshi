#include "mcmc.hpp"

vector<vector<ofColor>> MCMC::list = vector<vector<ofColor>>();
vector<vector<colAmount>> MCMC::caList = vector<vector<colAmount>>();
vector<ofColor> MCMC::buffer = vector<ofColor>();
vector<colAmount> MCMC::colorPool = vector<colAmount>();

float MCMC::errorSum = 0;

int MCMC::order = -1;

colAmount::colAmount(const ofColor& col)
:col(col), amount(1)
{}

colAmount& colAmount::operator++(){
    ++amount;
    return *this;
}

const ofColor& colAmount::getCol() const{
    return col;
}

int colAmount::getAmount() const{
    return amount;
}

MCMC::MCMC(){
    //do nothing.
    //this class is not supposed to be used for making any instance.
}

void MCMC::parse(const Canvas* canvas, int order){
    if(MCMC::order == -1){
        MCMC::order = order;
    }else if(MCMC::order != order){
        cout<<"you've just tried to parse data with different order"<<endl;
        cout<<"please parse data with consistent order"<<endl;
        return;
    }
    
    const ofColor* pixels = canvas->getPixels();
    if(pixels == nullptr){
        cout<<"pixel list you've just received in parse() function is nullptr"<<endl;
        return;
    }
    const int width = canvas->getWidth();
    const int height = canvas->getHeight();
    //    int offset = width*order;
    
    bufferSet(canvas);
    
    for(int y=order; y<height; ++y){
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
            for(int z=0; z<order-1; ++z){
                idx = y*width + x - (width+1)*(order-1-z);
                temp.push_back(pixels[idx]);
            }
            idx = y*width + x;
            const ofColor& tc = pixels[idx];
            addToPool(tc);
            addToList(temp, tc);
        }
    }
}

void MCMC::init(){
    list.clear();
    caList.clear();
    buffer.clear();
}

void MCMC::addToList(const vector<ofColor>& tList, const ofColor& col){
    for(int i=0; i<list.size(); ++i){
        if(list.at(i) == tList){
            addToCaList(i, col);
            return;
        }
    }
    list.push_back(tList);
    vector<colAmount> temp;
    temp.push_back(colAmount(col));
    caList.push_back(temp);
}

void MCMC::addToCaList(int idx, const ofColor& col){
    vector<colAmount>& list = caList.at(idx);
    for(int i=0; i<list.size(); ++i){
        colAmount& ca = list.at(i);
        const ofColor& savedCol = ca.getCol();
        if(savedCol == col){
            ++ca;
            return;
        }
    }
    list.push_back(colAmount(col));
}

void MCMC::bufferSet(const Canvas* canvas){
    buffer.clear();
    
    int width = canvas->getWidth();
    int height = canvas->getHeight();
    
#define FRONTSET 1
#if FRONTSET
    for(int y=0; y<order; ++y){
        for(int x=0; x<width; ++x){
            const ofColor& col = canvas->get(x, y);
            addToPool(col);
            buffer.push_back(col);
        }
    }
#else
    for(int y=height-order; y<height; ++y){
        for(int x=0; x<width; ++x){
            const ofColor& col = canvas->get(x, y);
            addToPool(col);
            buffer.push_back(col);
        }
    }
#endif
}

void MCMC::canvasDelay(int width, int height){
    for(int y=0; y<height-order; ++y){
        for(int x=0; x<width; ++x){
            vector<ofColor> temp;
            for(int i=0; i<order; ++i){
                int idx = 0 + width*i;
                temp.push_back(buffer[idx]);
            }
            for(int i=0; i<order; ++i){
                int idx = buffer.size()-order+i;
                temp.push_back(buffer[idx]);
            }
            for(int z=0; z<order-1; ++z){
                int tx = width-(order-1)+z;
                int ty = z;
                int idx = ty*width + tx;
                temp.push_back(buffer[idx]);
            }
            int idx_CaList = findIdx(temp);
            ofColor col;
            if(idx_CaList==-1){
                col = getMostCol();//ofColor(0);
            }else{
                col = monteCarlo(idx_CaList);
            }
            buffer.push_back(col);
            buffer.erase(buffer.begin());
        }
    }
}

int MCMC::findIdx(const vector<ofColor>& colList){
    for(int i=0; i<list.size(); ++i){
        if(list.at(i)==colList){
            return i;
        }
    }
    return -1;
//    return (int)ofRandom(list.size());
}

const ofColor& MCMC::monteCarlo(int idx){
    int sum = 0;
    const vector<colAmount>& list = caList.at(idx);
    
    for(int i=0; i<list.size(); ++i){
        sum += list.at(i).getAmount();
    }
    
    int rand = (int)ofRandom(sum);
    
    for(int i=0; i<list.size(); ++i){
        rand -= list.at(i).getAmount();
        if(rand<0){
            return list.at(i).getCol();
        }
    }
    return list.at(list.size()-1).getCol();
}

void MCMC::addToPool(const ofColor& col){
    int leng = colorPool.size();
    for(int i=0; i<leng; ++i){
        colAmount& ca = colorPool.at(i);
        if(ca.getCol() != col) continue;
        ++ca;
        return;
    }
    colAmount ca(col);
    colorPool.push_back(ca);
}

const ofColor MCMC::getMostCol(){
    int leng = colorPool.size();
    int max=-1;
    int idx=0;
    for(int i=0; i<leng; ++i){
        int val = colorPool.at(i).getAmount();
        if(val>max){
            max = val;
            idx = i;
        }
    }
    ofColor mostCol = colorPool.at(idx).getCol();
    
    return mostCol;
}

void MCMC::draw(Canvas* canvas){
    if(list.size()==0){
        cout<<"no data has been parsed yet"<<endl;
        return;
    }
    
    int height = canvas->getHeight();
    int width = canvas->getWidth();
    
    canvasDelay(width, height);
    
    for(int y=0; y<order; ++y){
        for(int x=0; x<width; ++x){
            int idx = y*width + x;
            canvas->set(x, y, buffer[idx]);
        }
    }
    
    errorSum = 0;
    
    for(int y=order; y<height; ++y){
        for(int x=0; x<width; ++x){
            vector<ofColor> temp;
            for(int i=0; i<order; ++i){
                temp.push_back(canvas->get(x, y-order+i));
            }
            for(int i=0; i<order; ++i){
                temp.push_back(canvas->get(x-order+i, y));
            }
            for(int z=0; z<order-1; ++z){
                int idx = y*width + x - (width+1)*(order-1-z);
                temp.push_back(canvas->getPixels()[idx]);
            }
            
            int idx_caList = findIdx(temp);
            ofColor col;
            if(idx_caList == -1){
                col = getMostCol();//ofColor(230,230,230);
                ++errorSum;
            }else{
                col = monteCarlo(idx_caList);
            }
            canvas->set(x, y, col);
        }
    }
    
    cout<< " Error Rate : " << errorSum/(width*height)  <<endl;
    
    //without double buffer
}

void MCMC::printStat(){
    if(list.size()==0){
        cout<<"no member in list"<<endl;
        return;
    }
    
    cout<<"list goes like this..."<<endl;
    cout<<"______________________"<<endl;
    for(int i=0; i<list.size(); ++i){
        cout<<i<<" idx : "<<endl;
        const vector<ofColor>& temp = list.at(i);
        for(int j=0; j<temp.size(); ++j){
            cout<<temp.at(j)<<" / ";
        }
        cout<<endl;
    }
    cout<<endl;
    cout<<endl;
    
    cout<<"caList goes like this..."<<endl;
    cout<<"________________________"<<endl;
    for(int i=0; i<caList.size(); ++i){
        cout<<i<<" idx ca List"<<endl;
        const vector<colAmount>& temp = caList.at(i);
        for(int j=0; j<temp.size(); ++j){
            cout<<temp.at(j).getCol()<<" : "<<temp.at(j).getAmount()<<endl;
        }
    }
    cout<<endl;
    cout<<"///...///"<<endl;
    cout<<endl;
}



