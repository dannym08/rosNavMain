//
//  PathFinding.cpp
//  Navigation
//
//  Created by Danny  on 4/14/17.
//  Copyright © 2017 Danny . All rights reserved.
//

#include "navigation/PathFinding.hpp"
#include <cmath>
#include <iostream>

using std::cout;
using std::endl;

///////////////////////
/* PRIVATE FUNCTIONS */
///////////////////////

void PathFinding::reorderHelper(vector<int> &vec) {
    int index, dis, temp;
    int endIndex = map->getEndIndex();
    vector<int> distancesFromEnd;
    
    for (int i = 0; i < vec.size(); i++) { // initialize end distance
        dis = calcDistance(vec[i], endIndex);
        distancesFromEnd.push_back(dis);
    }
    
    for (int i = 0; i < distancesFromEnd.size(); i++) {
        //highest = distancesFromEnd[i];
        index = i;
        
        for (int x = (i + 1); x < distancesFromEnd.size(); x++) {
            if (distancesFromEnd[index] < distancesFromEnd[x]) {
                //highest = distancesFromEnd[x];
                index = x;
            }
        }
        
        if (index != i) { // swap both vectors
            temp = distancesFromEnd[i];
            distancesFromEnd[i] = distancesFromEnd[index];
            distancesFromEnd[index] = temp;
            
            temp = vec[i];
            vec[i] = vec[index];
            vec[index] = temp;
        }
    }
    
}

//////////////////////
/* PUBLIC FUNCTIONS */
//////////////////////

PathFinding::PathFinding(int occupancyGrid[], int oneL, int twoL, float resolution){
    map = new Map(oneL, twoL);
    updateMap(occupancyGrid);
    this->resolution = resolution;
    solutionFound = false;
    
    for (int i = 0; i < oneL; i++) {
        visited.push_back(false);
    }

}

/* 
    Reorders map based of end index.
    endIndex must be set before calling reorder.
*/
void PathFinding::reorder() {
    vector<int> temp;
    int len = map->getOneDLength();
    
    for (int i = 0; i < len; i++) {
        temp = map->getAdjPaths(i);
        reorderHelper(temp);
        map->eraseAdjPaths(i, temp);
    }
}

/*
    Make sure current and end index are both set.
    The path knows its down once it tries to pop off the intial starting index.
 */
bool PathFinding::findPath() {
    bool pathFound = false; // if path is found or not
    bool next;
    bool outOfOptions = false; // when path is empty and we pop
    int startIndex = 0;
    int currentIndex = map->getCurrentIndex();
    int count, vecSize, tempLoc = 0;
    mapObject tempObj;
    vector<int> adjList;
    
    startIndex = currentIndex; // used for checking
    path.push(currentIndex);
    visited[currentIndex] = true;  
    
    while (!pathFound && !outOfOptions) {
        
        if (currentIndex == map->getEndIndex()) {
            pathFound = true;
            return pathFound;
        }
            
        count = 0; 
        adjList = map->getAdjPaths(currentIndex);
        vecSize = (int)adjList.size();
        next = false;
        
        //cout << "Current Location: " << currentIndex << endl;

    
        while (count < vecSize && !next) { // finds next index if there is one
            tempLoc = adjList[count];
            tempObj = map->getMapObject(tempLoc);
            
            if (tempObj == wall)
                visited[tempLoc] = true; // sets wall to true to avoid it
            else if (tempObj == space && !visited[tempLoc]) {
                next = true;
                visited[tempLoc] = true;
                //path.push(tempLoc);
            }
            else if (tempObj == unknown && !visited[tempLoc]){
                next = true;
                visited[tempLoc] = true;
                //path.push(tempLoc);
            }
            else if (tempObj == endPosition) {
                next = true;
                pathFound = true;
                //path.push(tempLoc);
                visited[tempLoc] = true;
            }
            //cout << "Temp Loc " << tempLoc << " Path Size " << path.getSize() << endl;
            
            count++;
        }
        //cout << "I OUT OF LOOP" << endl;
        if (next) {
            currentIndex = tempLoc;
           // cout << "PUSHED: " << currentIndex << endl;
            path.push(currentIndex);
        } else { // no new options were found
            if (path.peek() == startIndex){
                path.pop(); // get starting index off of path
                outOfOptions = true;
            }
            else { // if you have somthing to pop off, pop off
                //cout << "POPPED: " << path.peek() << endl;
                path.pop();
                //cout << "Called pop" << endl;
                currentIndex = path.peek();
                //cout << "AFTER POP: " << currentIndex << endl;
            }
          
        }
    
    }
    solutionFound = pathFound;
    return pathFound;
}

// will ignore the first and last because those represent the start
// and endpoints

void PathFinding::setPathOnMap() {
    vector<int> temp = path.getPath();
    int size = (int)temp.size();
    
    for (int i = 1; i < (size - 1); i++)
        map->setMapObject(pathObj, temp[i]);
}

bool PathFinding::isSolution(){
    return solutionFound;
}

void PathFinding::clearVisited() {
    int oneL = getOneDLength();
    
//    if (visited.size() != oneL)
//        visited.resize(oneL);
//    
    for (int i = 0; i < oneL; i++){
        visited[i] = false;
    }
}

void PathFinding::updateMap(int occupancyGird[]){
    map->updateMap(occupancyGird);
}


vector<int> PathFinding::getPath() {
    return path.getPath();
}


// calculates distance in meters from current point to goal (diagonal distance, not distance of path)
double PathFinding::calcDistance(int x, int y) {
    double temp1, temp2;
    int x1, x2, y1, y2;
    
    map->oneToTwoD(x, x1, y1);
    map->oneToTwoD(y, x2, y2);

    x = abs(x1 - x2);
    y = abs(y1 - y2);
    
    //cout << x << " " << y << endl;
    
    temp1 = x * resolution;
    temp2 = y * resolution;
    
    //cout << temp1 << " " << temp2 << endl;
    
    temp1 = temp1 * temp1;
    temp2 = temp2 * temp2;
    
    temp1 = temp1 + temp2;
    temp2 = sqrt(temp1);
    
    return temp2;
}

//////////////////////////
// SET FUNCTIONS ON MAP //
//////////////////////////

void PathFinding::setOneDLength(int oneD) {
    map->setOneDLength(oneD);
}

void PathFinding::setTwoDLength(int twoD) {
    map->setTwoDLength(twoD);
}

void PathFinding::setEnd(int index) {
    map->setEndIndex(index);
    reorder();
}

void PathFinding::setCurrentIndex(int index){
    map->setCurrentIndex(index);
}

int PathFinding::getOneDLength() {
    return map->getOneDLength();
}

int PathFinding::getTwoDLength() {
    return map->getTwoDLength();
}

/////////////////
//Test Funciton//
/////////////////

void PathFinding::printLinkedList() {
    map->printLinkedList();
}

void PathFinding::printMap() {
    map->printMap();
}

void PathFinding::printIndex() {
    map->printIndex();
}

void PathFinding::printPath() {
    path.printPath();
}

