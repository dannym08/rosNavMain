//
//  PathFinding.hpp
//  Navigation
//
//  Created by Danny  on 4/14/17.
//  Copyright © 2017 Danny . All rights reserved.
//

#ifndef PathFinding_hpp
#define PathFinding_hpp

#include "Path.hpp"
#include "Map.hpp"
#include "GlobalConstants.hpp"

class PathFinding {
    private:
        Map* map; //**MAKE SURE NO MEMEORY LEAKS**
        Path path;
        float resolution; // the size of each cell within the map (in meters)
        bool solutionFound;
        vector<bool> visited;
        void reorderHelper(vector<int> &vec); // reorder linked list based off distance to end
    public:
        //PathFinding();
        //PathFinding(int occupancayGrid);
        PathFinding(int occupancyGrid[], int oneL, int twoL, float resolution);// One dimensional length, two dimensional length
        void reorder(); // change links based off distance for shorest distance (end index must be set)
        bool findPath();
        void setPathOnMap();
        bool isSolution();
        void clearVisited();
        void updateMap(int occupancyGird[]);
        vector<int> getPath();
    double calcDistance(int x, int y); // in meters
    
        // set and get functions for the map
        void setOneDLength(int oneD);
        void setTwoDLength(int twoD);
        void setEnd(int index); // called by UI node
        void setCurrentIndex(int index);
        int getOneDLength();
        int getTwoDLength();
    
        //TEST FUNCTIONS
        void printLinkedList();
        void printMap();
        void printIndex();
        void printPath();
    
    
};

#endif /* PathFinding_hpp */
