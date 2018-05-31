
#ifndef Order_h
#define Order_h

#include "Widgets.h"
#include "LinkedStack.h"

using namespace std;

class Order {
    
private:
    int orderNumber;
    int quantity;
    double cost;
    LinkedStack<Widgets> widgets;
    int remainingWidgets;
    
public:
    
#pragma mark - Constructors
    Order() {
        
    }
    
    Order(const Order &entry) {
        
        this->orderNumber = entry.orderNumber;
        this->quantity = entry.quantity;
        this->cost = entry.cost;
        this->widgets = entry.widgets;
        this->remainingWidgets = entry.remainingWidgets;
    }
    
    Order(int orderID, int numberOfWidgets) {
        
        this->orderNumber = orderID;
        this->quantity = numberOfWidgets;
        this->cost = 0;
        this->remainingWidgets = numberOfWidgets;
    }
    
    Order(int orderID, int numberOfWidgets, LinkedStack<Widgets> widgets) {
        
        this->cost = 0;
        this->orderNumber = orderID;
        this->quantity = numberOfWidgets;
        this->addWidgets(numberOfWidgets, widgets);
    }
    
#pragma mark - Setters and getters
    
    int getOrderNumber() {
        
        return this->orderNumber;
    }
    
    double getCost() {
        
        return this->cost;
    }
    
    int getRemainingWidgets() {
        
        return this->remainingWidgets;
    }
    
    void setRemainingWidgets(int entry) {
        
        this->remainingWidgets = entry;
    }
    
    void addWidget(Widgets widget) {
        
        this->widgets.push(widget);
        this->cost = this->cost + (widget.getCost() + (widget.getCost() * 0.5));
        this->remainingWidgets -= 1;
    }
    
    void addWidgets(int numberOfWidgets, LinkedStack<Widgets> stackOfWidgets) {
        
        for (int i = 0; i < this->quantity; i++) {
            
            Widgets currentwidget = stackOfWidgets.peek();
            
            this->cost += currentwidget.getCost();
            this->widgets.push(currentwidget);
            this->remainingWidgets -= 1;
            
            stackOfWidgets.pop();
        }
        
        //Add 50% of the cost
        this->cost += (this->cost * 0.50);
    }
    
#pragma operator overloadings
    friend ostream & operator << (ostream &output, Order orders) {
    
        output<<"Order Details"<<endl;
        output<<"-------------"<<endl;
        output << "OrderID: " << orders.orderNumber << endl;
        output << "Quantity: " << orders.quantity << endl;
        output << "Cost: " << orders.cost << endl << endl;
        
    return output;
}
    
};

#endif

