/*
Buttons 2 player example
Robin Lamb, June 29, 2021

Based on Buttons example
Copyright (C) 2015 David Martinez
All rights reserved.
This code is the most basic barebones code for showing how to use buttons in
Arduboy.

This library is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public
License as published by the Free Software Foundation; either
version 2.1 of the License, or (at your option) any later version.
*/

#include <Arduboy2.h>

// Make an instance of arduboy used for many functions
Arduboy2 arduboy;

// Variables for your game go here.
char title[] = "P1";
char title2[] = "P2";
byte x;
byte y;
byte x2;
byte y2;

// Width of each charcter including inter-character space
#define CHAR_WIDTH 6

// Height of each charater
#define CHAR_HEIGHT 8

// To get the number of characters, we subtract 1 from the length of
// the array because there will be a NULL terminator at the end.
#define NUM_CHARS (sizeof(title) - 1)

// This is the highest value that x can be without the end of the text
// going farther than the right side of the screen. We add one because
// there will be a 1 pixel space at the end of the last character.
// WIDTH and HEIGHT are defined in the Arduboy library.
#define X_MAX (WIDTH - (NUM_CHARS * CHAR_WIDTH) + 1)

// This is the highest value that y can be without the text going below
// the bottom of the screen.
#define Y_MAX (HEIGHT - CHAR_HEIGHT)


// This function runs once in your game.
// use it for anything that needs to be set only once in your game.
void setup() {
  //initiate arduboy instance
  arduboy.begin();

  // here we set the framerate to 30, we do not need to run at default 60 and
  // it saves us battery life.
  arduboy.setFrameRate(30);

  // set sets of text to the middle of the screen, on opposite sides
  x = (CHAR_WIDTH * 2);
  x2 = (WIDTH - (CHAR_WIDTH * 4));
  y = (HEIGHT / 2) - (CHAR_HEIGHT / 2);
  x = (CHAR_WIDTH * 2);
  y2 = (HEIGHT / 2) - (CHAR_HEIGHT / 2);
}


// our main game loop, this runs once every cycle/frame.
// this is where our game logic goes.
void loop() {
  // pause render until it's time for the next frame
  if (!(arduboy.nextFrame()))
    return;

  // the next couple of lines will deal with checking if the D-pad buttons
  // are pressed and move our text accordingly.
  // We check to make sure that x and y stay within a range that keeps the
  // text on the screen.

  // If Player 1's right button is pressed move 1 pixel to the right every frame
  if(arduboy.pressed(RIGHT_BUTTON) && (x < X_MAX)) {
    x++;
  }

  // If Player 1's left button is pressed move 1 pixel to the left every frame
  if(arduboy.pressed(LEFT_BUTTON) && (x > 0)) {
    x--;
  }

  // If Player 1's up button or B button is pressed move 1 pixel up every frame
  if((arduboy.pressed(UP_BUTTON) || arduboy.pressed(B_BUTTON)) && (y > 0)) {
    y--;
  }

  // If Player 1's down button or A button is pressed move 1 pixel down every frame
  if((arduboy.pressed(DOWN_BUTTON) || arduboy.pressed(A_BUTTON)) && (y < Y_MAX)) {
    y++;
  }


  // If Player 2's right button is pressed move 1 pixel to the right every frame
  if(arduboy.pressed(RIGHT_BUTTON_2) && (x < X_MAX)) {
    x2++;
  }

  // If Player 2's left button is pressed move 1 pixel to the left every frame
  if(arduboy.pressed(LEFT_BUTTON_2) && (x > 0)) {
    x2--;
  }

  // If Player 2's up button or B button is pressed move 1 pixel up every frame
  if((arduboy.pressed(UP_BUTTON_2) || arduboy.pressed(B_BUTTON_2)) && (y > 0)) {
    y2--;
  }

  // If Player 2's down button or A button is pressed move 1 pixel down every frame
  if((arduboy.pressed(DOWN_BUTTON_2) || arduboy.pressed(A_BUTTON_2)) && (y < Y_MAX)) {
    y2++;
  }


  // we clear our screen to black
  arduboy.clear();

  // we set our cursor x pixels to the right and y down from the top
  arduboy.setCursor(x, y);

  // then we print to screen what is stored in our title variable we declared earlier
  arduboy.print(title);

  //Set player 2 title
  arduboy.setCursor(x2, y2);
  arduboy.print(title2);

  // then we finaly we tell the arduboy to display what we just wrote to the display.
  arduboy.display();
}
