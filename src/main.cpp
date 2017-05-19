//
//  main.cpp
//  Navigation
//
//  Created by Danny  on 4/11/17.
//  Copyright © 2017 Danny . All rights reserved.
//

#include <iostream> // for testing and printing to terminal
#include "navigation/Map.hpp"
#include "navigation/Path.hpp"
#include "navigation/PathFinding.hpp"

#include <ctime> // for rand
#include <stdlib.h> // for rand


using namespace std;

const int oneDLength = 225; // LONGER ONE
const int twoDLength = 15; // SHORTER ONE
const float resolution = .4;

int main(int argc, const char* argv[]) {
    int occupancyGrid[oneDLength] = {0};
    
    PathFinding pf(occupancyGrid, oneDLength, twoDLength, resolution);
    
    pf.setCurrentIndex(6);
    pf.setEnd(210);
    pf.printIndex();
    pf.findPath();
    //pf.setPathOnMap();
    pf.printMap();
    
    

    pf.printPath();
    
    
    return 0;
}
