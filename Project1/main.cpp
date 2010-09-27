/*
 *  main.cpp
 *  Project1
 *
 *  Created by Brady Law on 9/21/10.
 *  Copyright 2010 Brady Law. All rights reserved.
 *
 */

#include "ShooterGame/ShooterGame.h"

int main(int argc, char** argv)
{
    ShooterGame::game.Init(&argc, argv, 800, 600);
    return 0;
}
