//
//  Map.cpp
//  Navigation
//
//  Created by Danny  on 4/11/17.
//  Copyright © 2017 Danny . All rights reserved.
//

#include "navigation/Map.hpp"
//#include "GlobalConstants.hpp"
#include <iostream>
#include <iomanip>

using std::endl;
using std::cout;

//////////////////////
/* PRIVATE FUNCTIONS*/
//////////////////////

//Node* Map::getLastNode(int linkedListIndex) {
//    Node* n = map[linkedListIndex]->headPtr;
//    
//    if (n == nullptr) { // this should not happen
//        n = new Node(error);
//        return n;
//    }
//    while (n->next != nullptr) {
//        n = n->next;
//    }
//    
//    return n;
//}

// assumes oneDLength is set
// assumes length is above 9
// Function creates oneDLength ammount of linked lists all with one node in it being the first node (node on the map)
void Map::initialize(vector<mapObject> vec) {
    Node* n;
    LinkedList* linked;
    mapObject m = unknown;
        
    for (int i = 0; i < oneDLength; i++) {
        
        if (vec.size() > 0) // if non empty vector is sent
            m = vec[i];
        
        n = new Node(m);
        n->setIndex(i);
        linked = new LinkedList();
        linked->add(n);
        map.push_back(linked); // first index for each linked list
    }
}

// call after emptyInitialize
// has 9 different casses
void Map::emptyLink() {
    Node* a;
    Node* b;
    Node* c;
    Node* d;
    for (int i = 0; i < oneDLength; i++) {
        LinkedList* n  = map[i]; //the current linked list
        if (i == 0) { // top-left corner case
            a = new Node(i + 1); // right node
            n->add(a);
            b = new Node(twoDLength); //node udner
            n->add(b);
        } else if (i == (twoDLength - 1)) { // top-right corner case
            a = new Node(i - 1); // left node
            n->add(a);
            b = new Node(i + twoDLength); // node under
            n->add(b);
        } else if (i == twoToOneD(twoDLength - 1, 0)) { //bottem-left corner case
            a = new Node(twoToOneD(twoDLength - 2 , 0)); // node above
            n->add(a);
            b = new Node(i + 1); // right node
            n->add(b);
        } else if (i == twoToOneD(twoDLength - 1, twoDLength - 1)) { // bottem-right corner case
            a = new Node(i - 1); // left node
            n->add(a);
            b = new Node(i - twoDLength); // node above
            n->add(b);
        } else if (i > 0 && i < twoDLength) { //top row (excluding corners)
            a = new Node (i - 1); //node to its left
            n->add(a);
            b = new Node(i + 1); // node to its right
            n->add(b);
            c = new Node(i + twoDLength); // node under it
            n->add(c);
        } else if (i > twoToOneD(twoDLength - 1, 0) && i < twoToOneD(twoDLength - 1, twoDLength - 1)) { // bottem row (excluding corners)
            a = new Node (i - 1); //node to its left
            n->add(a);
            b = new Node(i + 1); // node to its right
            n->add(b);
            c = new Node(i - twoDLength); // node on top
            n->add(c);
        } else if (i % twoDLength == 0) { // leftmost collum (but corners since corners will be caught first)
            a = new Node(i - twoDLength); // node above
            n->add(a);
            b = new Node(i + twoDLength); // node under
            n->add(b);
            c = new Node(i + 1); // right node
            n->add(c);
        } else if (i % twoDLength == (twoDLength - 1)) { // rightmost collum
            a = new Node(i - twoDLength);
            n->add(a);
            b = new Node(i + twoDLength);
            n->add(b);
            c = new Node(i - 1);
            n->add(c);
        } else { //all the rest(middle bunch)
            a = new Node(i -twoDLength); // top node
            n->add(a);
            b = new Node(i + twoDLength); // bottom node
            n->add(b);
            c = new Node(i - 1); // left node
            n->add(c);
            d = new Node(i + 1); // right node
            n->add(d);
        }
    }
}

/////////////////////
/* PUBLIC FUNCTION */
/////////////////////

Map::Map(int oLength, int tLength) {
    oneDLength = oLength;
    twoDLength = tLength;
    vector<mapObject> vec;
    initialize(vec);
    emptyLink();
}

// wallCutoff is set in global constants (change that in that file)
void Map::updateMap(int occupancyGrid[]) {
    
    for (int i = 0; i < oneDLength; i++) {
        if (occupancyGrid[i] == -1)
            map[i]->headPtr->item = unknown;
        else if (occupancyGrid[i] < wallCutoff)
             map[i]->headPtr->item = space;
        else if (occupancyGrid[i] >= wallCutoff)
             map[i]->headPtr->item = wall;
        else
            map[i]->headPtr->item = error;
    }
}

vector<int> Map::getAdjPaths(int index) {
    vector<int> vec;
    Node* node = map[index]->headPtr;
    
    if (node == nullptr){
        return vec;
    }
    
    node = node->next;
    
    while (node!= nullptr) {
        vec.push_back(node->index);
        node = node -> next;
    }
    
    return vec;
}

// erase & set adj path
void Map::eraseAdjPaths(int index, vector<int> vec) {
    map[index]->clear();
    
//    Node* n = map[index]->headPtr;
//    std::cout << "Test" << std::endl;
//    while (n != nullptr){
//        std::cout << "1" << std::endl;
//    }
    
    Node* temp;
    for (int i = 0; i < vec.size(); i++) {
        temp = new Node(vec[i]);
        //temp->next = nullptr;
        map[index]->add(temp);
    }
}

// assumes oneDLength and twoDLength is set
// row and collum start at 0
int Map::twoToOneD(int row, int collum) {
    int a = (row * twoDLength) + collum;
    return a;
}

// assumes oneDLength and twoDLength is set
// row and collum start at zero
void Map::oneToTwoD(int a, int& row, int& collum) {
    row = a / twoDLength; //sets row number
    collum = a % twoDLength; //sets collum number
}

void Map::setCurrentIndex(int current) {
    currentIndex = current;
    map[currentIndex]->headPtr->item = currentPosition;
}

int Map::getCurrentIndex() {
    return currentIndex;
}

void Map::setEndIndex(int finish) {
    endIndex = finish;
    map[endIndex]->headPtr->item = endPosition;
}

int Map::getEndIndex() {
    return endIndex;
}

int Map::getOneDLength() {
    return oneDLength;
}

void Map::setOneDLength(int one){
    oneDLength = one;
}

int Map::getTwoDLength() {
    return twoDLength;
}

void Map::setTwoDLength(int two) {
    twoDLength = two;
}

void Map::setMapObject(mapObject mObj, int index) {
    map[index]->headPtr->item = mObj;
    
}

mapObject Map::getMapObject(int index) {
    return (map[index]->headPtr->item);
}


/////////////////////
/* Test Functions */
/////////////////////


// The first one printed is the space with (object) the following are the possilble places you can move from the first one
void Map::printLinkedList() {
    Node* n;
    for (int i = 0; i < oneDLength; i++) {
        int count = 0;
        n = map[i]->headPtr;
        cout << "Index " << i << ": ";
        while (n != nullptr) {
            if (count > 0)
                cout << "->";
            cout << " " << n->index  << "(" << n->item << ")" << " "; // prints out index and and mapObject
            n = n->next;
            count++;
        }
        cout << endl;
    }
}

void Map::printMap() {
    cout << "Printing out map index(object)" << endl;
    cout << "------------------------------" << endl;
    for (int i = 0; i < twoDLength; i++) {
        cout << endl;
        for (int x = 0; x < twoDLength; x++) {
            int index = (i * twoDLength) + x;
            
//            if (x == 0)
//                cout << std::setw(6) << index << "(" << map[index]->headPtr->item << ")"; // setw is on index only
//            else
                cout << std::setw(6) << index << "(" << map[index]->headPtr->item << ")";// setw is on index only
        }
    }
    cout << endl;
}

void Map::printIndex() {
    cout << "Map Index" << endl;
    cout << "------------------------------" << endl;
    cout << "Unkown: " << unknown << endl;
    cout << "Space: " << space << endl;
    cout << "Wall: " << wall << endl;
    cout << "Current/start position: " << currentPosition << endl;
    cout << "End position: " << endPosition << endl;
    cout << "Path: " << pathObj << endl;
    cout << "------------------------------" << endl;
}
