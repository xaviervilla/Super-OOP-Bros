//
//  PhysicsController.hpp
//  SuperOOPBros
//
//  Created by Maxime Moison on 3/23/18.
//  Copyright © 2018 Maxime Moison. All rights reserved.
//

#ifndef PhysicsController_hpp
#define PhysicsController_hpp

#include "MovingObject.hpp"

#define DEFAULT_GRAVITY -.002
#define LOW_GRAVITY -.001
#define DEFAULT_DRAG -1
#define DEFAULT_SPEED 0.012
#define SLOW_SPEED 0.004
#define EXTREME_SPEED 0.1

class PhysicsController {
    float gravity;
    void applyGravity(MovingObject* obj);
    float gameSpeed;
public:
    PhysicsController();
    PhysicsController(float gravity, float speed);
    void applyforces(MovingObject* obj);
    void setSpeed(float);
    void setGravity(float);
    float getSpeed();
    void reset();
};

#endif /* PhysicsController_hpp */
