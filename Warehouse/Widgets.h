
#ifndef Widgets_h
#define Widgets_h

#include <iostream>

using namespace std;

class Widgets {
    
private:
   double cost;
    
public:
    Widgets() {
        
        this->cost = 0;
    }
    
    Widgets(double entry) {
        
        this->cost = entry;
    }

    void setCost(double entry) {
        
        if (entry <= 0) {
            
            cout<<"Invalid Cost";
            
        } else {
            
            this->cost = entry;
        }
        
    }
    
    double getCost() const {
        
        return this->cost;
    }
    
    friend ostream & operator << (ostream &output, Widgets widget) {
        
        output<<"Widget Details"<<endl;
        output<<"-------------"<<endl;
        output << "Cost: "<< widget.cost<<endl;
        
        return output;
    }
    
};

#endif /* Widgets_h */

