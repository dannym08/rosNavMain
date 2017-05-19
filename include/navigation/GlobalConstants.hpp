//
//  GlobalConstants.hpp
//  Navigation
//
//  Created by Danny  on 4/11/17.
//  Copyright © 2017 Danny . All rights reserved.
//

#ifndef globalConstants_hpp
#define globalConstants_hpp

enum mapObject {unknown = -1, space = 0, wall = 1, currentPosition = 2, endPosition = 3, pathObj = 4, error = 9};

const int wallCutoff = 50; // (100 - wallCutoff)% of indicies being walls 
#endif /* globalConstants_hpp */
