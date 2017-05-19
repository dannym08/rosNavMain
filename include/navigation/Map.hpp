//
//  Map.hpp
//  Navigation
//
//  Created by Danny  on 4/11/17.
//  Copyright © 2017 Danny . All rights reserved.
//

#ifndef Map_hpp
#define Map_hpp

#include "GlobalConstants.hpp"

#include <vector>
#include <iostream>

using std::vector;

struct Node {
    Node* next;
    int index; //the index is points to
    mapObject item;
    
    
    Node () {
        next = nullptr;
        item = unknown;
        index = -1; // -1 = unknown
    }
    
    Node (int indexx) {
        item = unknown;
        next = nullptr;
        index = indexx;
    }
    Node(mapObject mObj) {
        item = mObj;
        next = nullptr;
        index = -1;
    }
    
    ~Node() {
        next = nullptr;
        delete this;
    }
    
    void setIndex(int i){
        index = i;
    }
    
    int getIndex() {
        return index;
    }
    //write deconstructor?
};

struct LinkedList {
    Node* headPtr;
    
    LinkedList() {
        headPtr = nullptr;
    }
    
    
    // adds to the second place in the linked list since header has the map object info
    void add(Node* n) {
        Node* head = headPtr;
        if (headPtr == nullptr) {
            headPtr = n;
        } else if (head->next == nullptr) {
            headPtr->next = n;
        } else {
            Node* tempNode = headPtr->next;
            headPtr->next = n;
            n->next = tempNode;
        }

    }
    
    //clears all BUT headPtr since headPtr stores mapObject info
    void clear() {
        Node* node = headPtr;
        if (headPtr == nullptr)
            return;
        
        node->next = nullptr;

    }
    
//    ~LinkedList() {
//        while (headPtr != nullptr) {
//            Node* temp = headPtr;
//            headPtr = headPtr->next;
//            delete temp;
//            temp = nullptr;
//        }
//    }
};

class Map {
    private:
        vector<LinkedList*> map;
        int currentIndex;
        int endIndex;
        int oneDLength; // *STARTS FROM ONE* one dimensonal array length (number of squares in occupancyGrid)
        int twoDLength; // *STARTS FROM ONE* two dimensonal length (just length or width since its a square map)
    
        // Creates empty node on top of
        void emptyLink(); // links node to surrounding node (call after emptyInitialize
        void initialize(vector<mapObject> vec);

        //Node* getLastNode(int linkedListIndex);
    
    public:
        // Map();
        Map(int oLength, int tLength); // 1D and 2D length
        //Map(int oLength, int tLength, int occupancyGrid);
        //~Map();
        void updateMap(int occupancyGird[]);
        vector<int> getAdjPaths(int index);
        void eraseAdjPaths(int index, vector<int>);
    
        void oneToTwoD(int a, int& row, int &collum); // will return values in x and y
        int twoToOneD(int row, int collum);
    
        // set and get functions
        void setCurrentIndex(int start);
        int getCurrentIndex();
        void setEndIndex(int finish);
        int getEndIndex();
        void setMapObject(mapObject mObj, int index);
        mapObject getMapObject(int index);
        int getOneDLength();
        void setOneDLength(int one);
        int getTwoDLength();
        void setTwoDLength(int two);
    
    
        // functions for testing
        void printMap();
        void printIndex();
        void printLinkedList();
    
    
};

#endif /* Map_hpp */
