//
//  Path.hpp
//  Navigation
//
//  Created by Danny  on 4/14/17.
//  Copyright © 2017 Danny . All rights reserved.
//

#ifndef Path_hpp
#define Path_hpp

#include <vector>

using std::vector;

class Path{
    private:
        vector<int> path;
        int itemCount; // the last index
public:
        Path();
    
        /*stack functions*/
    
        bool isEmpty();
        void push(int newEntry); // adds to end
        void pop(); // takes off top
        int peek(); // looks at the last item
        void resetPath();
        int getSize();
    
        // test functions
        void printPath();
    
        vector<int> getPath(); // use this to get path once path complete
    
};

#endif /* Path_hpp */
