/*
 *  main.cpp
 *  Project1
 *
 *  Created by Brady Law on 9/21/10.
 *  Copyright 2010 Brady Law. All rights reserved.
 */

#include "BubbleGame/BubbleGame.h"

int main (int argc, char** argv) {
    BubbleGame::game.Init(&argc, argv, 800, 600);
    return 0;
}
