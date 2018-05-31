
#include <iostream>

#include "LinkedStack.h"
#include "Order.h"
#include "Widgets.h"

using namespace std;

enum menuOption {
    
    exitProgram,
    createOrder,
    enterDelivery,
    printOrders,
    printInvrntory
};

void menu(LinkedStack<Widgets>, LinkedStack<Order> &, LinkedStack<Widgets> &);
void performActionForSelection(int, LinkedStack<Widgets>, LinkedStack<Order> &, LinkedStack<Widgets> &);
void createNewOrder(LinkedStack<Order> &, LinkedStack<Widgets>, LinkedStack<Widgets> &);
void delivery(LinkedStack<Widgets> &inventoryStack, LinkedStack<Order> &ordersStack, LinkedStack<Widgets> &delivery);

int main() {
    
    LinkedStack<Widgets> inventory;
    LinkedStack<Order> orders;
    LinkedStack<Widgets> deliveryStack;
    
    menu(inventory, orders, deliveryStack);
}

#pragma mark - Menu Method
void menu(LinkedStack<Widgets> inventory, LinkedStack<Order> &orders, LinkedStack<Widgets> &deliveryStack) {

    int selection = -1;
    
    cout<<"Warehouse Manager v1.0.0"<<endl;
    cout<<"-------------------------"<<endl<<endl;
    
    cout<<"Main Menu"<<endl;
    cout<<"---------"<<endl;
    
    while (selection < exitProgram || selection > printInvrntory) {
        
        cout<<"1. New Order"<<endl;
        cout<<"2. Enter Delivery"<<endl;
        cout<<"3. View Order List"<<endl;
        cout<<"4. View Inventory"<<endl;
        cout<<"0. Logout"<<endl<<endl;
        cout<<"> ";
        cin>>selection;
        cout<<endl;
    }
    
    performActionForSelection(selection, inventory, orders, deliveryStack);
    
}

void performActionForSelection(int selection, LinkedStack<Widgets> inventory, LinkedStack<Order> &orderStack, LinkedStack<Widgets> &deliveryStack) {
    
    switch (selection) {
            
        case createOrder: {

            createNewOrder(orderStack, inventory, deliveryStack);
            break;
        }
            
        case enterDelivery: {
            
            int deliveryWidgets;
            
            cout<<"Enter the quantity of widgets: "<<endl;
            cout<<"> ";
            cin>>deliveryWidgets;
            
            for (int counter = 0; counter < deliveryWidgets; counter++) {
                
                double widgetCost = 0;
                
                cout<<"Widget cost: "<<endl;
                cout<<"> ";
                cin>>widgetCost;
                
                Widgets newWidget = Widgets(widgetCost);
                deliveryStack.push(newWidget);
            }
            
            delivery(inventory, orderStack, deliveryStack);
            
            break;
        }
            
        case printOrders: {
            
            LinkedStack<Order> ordersCopy = LinkedStack<Order>(orderStack);
            
            while (!ordersCopy.isEmpty()) {
                
                cout<<ordersCopy.peek();
                ordersCopy.pop();
            }
            
            menu(inventory, orderStack, deliveryStack);
            break;
        }
            
        case printInvrntory: {
            
            LinkedStack<Widgets> inventoryCopy = LinkedStack<Widgets>(inventory);
            
            while (!inventoryCopy.isEmpty()) {
                
                cout<<inventoryCopy.peek();
                inventoryCopy.pop();
            }
            
            menu(inventory, orderStack, deliveryStack);
            break;
        }
    
        case exitProgram: {
            
            cout<<"Logout"<<endl;
            return;
        }
            
    } // End Switch
}

void createNewOrder(LinkedStack<Order> &ordersStack, LinkedStack<Widgets> inventoryStack, LinkedStack<Widgets> &deliveryStack) {
    
    int orderID;
    int numberOfWidgets;
    
    cout<<"Enter the order number: "<<endl;
    cout<<"> ";
    cin>>orderID;
    
    cout<<"Enter the number of widgets: "<<endl;
    cout<<"> ";
    cin>>numberOfWidgets;
    
    Order newOrder = Order(orderID, numberOfWidgets);

    if (inventoryStack.isEmpty()) {

        ordersStack.push(newOrder);
        
    } else {
        
        LinkedStack<Widgets> widgets;
        
        for (int counter = 0; counter < numberOfWidgets; counter++) {
            
            // Remaining widgets and inventory still has items
            if (newOrder.getRemainingWidgets() > 0 && !(inventoryStack.isEmpty())) {
                
                Widgets test = Widgets();
                test = inventoryStack.peek();
                newOrder.addWidget(test);
                inventoryStack.pop();
                
                // Remaining widgets and inventory is empty
            } else if (newOrder.getRemainingWidgets() > 0 && (inventoryStack.isEmpty())) {
                
                ordersStack.push(newOrder);
                break;
    
                // Order is completed
            } else if (newOrder.getRemainingWidgets() == 0) {
                cout<<"The order has been fullfilled"<<endl;
                
                break;
            } // End If
            
        } // End For
        
    } // End If
    
    cout<<"The order has been created successfuly"<<endl<<endl;
    cout<<newOrder;
    
    // Go back to main menu
    menu(inventoryStack, ordersStack, deliveryStack);
}

void delivery(LinkedStack<Widgets> &inventoryStack, LinkedStack<Order> &ordersStack, LinkedStack<Widgets> &delivery) {
    
    if (ordersStack.isEmpty()) {
        
        // Add widgets to inventory
        while (!delivery.isEmpty()) {
            
            inventoryStack.push(delivery.peek());
            delivery.pop();
        }
        
    } else {
        
        // Add widgets to order
        while (!delivery.isEmpty() && !(ordersStack.isEmpty())) {
            
            Order currentOrder = ordersStack.peek();
            
            int remainingWidgetsInOrder = currentOrder.getRemainingWidgets();
            
            for (int counter = 0; counter <= remainingWidgetsInOrder; counter++) {
                
                if (!delivery.isEmpty()) {
                    
                    Widgets currentWidget = delivery.peek();
                    currentOrder.addWidget(currentWidget);
                    delivery.pop();
                }
                
                if (counter == remainingWidgetsInOrder - 1) {
                    
                    cout<<"The order "<<currentOrder.getOrderNumber()<<" has been fulfilled"<<endl;
                    cout<<currentOrder;
                    ordersStack.pop();
                
                }// End If
                
            } // End For
            
        } // End While
        
    } // End If/Else
    
    menu(inventoryStack, ordersStack, delivery);
    
} // End Function
