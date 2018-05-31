
#ifndef LinkedStack_h
#define LinkedStack_h

#include <cassert>

#include "StackInterface.h"
#include "Node.h"

using namespace std;

template<class ItemType>
class LinkedStack : public StackInterface<ItemType> {
    
private:
    Node<ItemType>* topPtr; // Pointer to first node in the chain;
                            // this node contains the stack's top

public:
    // Constructors and destructor:
    LinkedStack();                                   // Default constructor
    LinkedStack(const LinkedStack<ItemType>& aStack);// Copy constructor
    virtual ~LinkedStack();                          // Destructor
    // Stack operations:
    bool isEmpty() const;
    bool push(const ItemType& newItem);
    bool pop();
    ItemType peek() const;
};

template<class ItemType>
LinkedStack<ItemType>::LinkedStack() : topPtr(nullptr) {
}

template<class ItemType>
LinkedStack<ItemType>::LinkedStack(const LinkedStack<ItemType>& aStack) {
    
    // Point to nodes in original chain
    Node<ItemType>* origChainPtr = aStack.topPtr;
    
    if (origChainPtr == nullptr)
        
        topPtr = nullptr;  // Original stack is empty
    
    else {
        // Copy first node
        topPtr = new Node<ItemType>();
        topPtr->setItem(origChainPtr->getItem());
        
        // Point to last node in new chain
        Node<ItemType>* newChainPtr = topPtr;
        
        // Advance original-chain pointer
        origChainPtr = origChainPtr->getNext();
        
        // Copy remaining nodes
        while (origChainPtr != nullptr) {
            
            // Get next item from original chain
            ItemType nextItem = origChainPtr->getItem();
            
            // Create a new node containing the next item
            Node<ItemType>* newNodePtr = new Node<ItemType>(nextItem);
            
            // Link new node to end of new chain
            newChainPtr->setNext(newNodePtr);
            
            // Advance pointer to new last node
            newChainPtr = newChainPtr->getNext();
            
            // Advance original-chain pointer
            origChainPtr = origChainPtr->getNext();
        }
        
        newChainPtr->setNext(nullptr); // Flag end of chain
    }
}

template<class ItemType>
LinkedStack<ItemType>::~LinkedStack() {
    
    // Pop until stack is empty
//    while (!isEmpty())
//    
//        pop();
}

template<class ItemType>
bool LinkedStack<ItemType>::isEmpty() const {
    
    return topPtr == nullptr;
}

template<class ItemType>
bool LinkedStack<ItemType>::push(const ItemType& newItem) {
    
    Node<ItemType>* newNodePtr = new Node<ItemType>(newItem, topPtr);
    
    topPtr = newNodePtr;
    
    newNodePtr = nullptr;
    
    return true;
}

template<class ItemType>
bool LinkedStack<ItemType>::pop() {
    
    bool result = false;
    
    if (!isEmpty()) {
        
        // Stack is not empty; delete top
        Node<ItemType>* nodeToDeletePtr = topPtr;
        
        topPtr = topPtr->getNext();
        
        // Return deleted node to system
        nodeToDeletePtr->setNext(nullptr);
        
        delete nodeToDeletePtr;
        
        nodeToDeletePtr = nullptr;
        
        result = true;
    }
    
    return result;
}

template<class ItemType>
ItemType LinkedStack<ItemType>::peek() const {
    
    assert(!isEmpty()); // Enforce precondition
    
    // Stack is not empty; return top
    
    return topPtr->getItem();
}

#endif

