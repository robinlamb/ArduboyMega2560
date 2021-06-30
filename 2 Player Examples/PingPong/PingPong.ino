 /*

 Arduboy Ping Pong
 Robin Lamb, June 29, 2021
 
 Based on Breakout
 Copyright (C) 2011 Sebastian Goscik
 All rights reserved.

 Modifications by Scott Allen 2016 (after previous changes by ???)

 This library is free software; you can redistribute it and/or
 modify it under the terms of the GNU Lesser General Public
 License as published by the Free Software Foundation; either
 version 2.1 of the License, or (at your option) any later version.
 */

#include <Arduboy2.h>


Arduboy2 arduboy;
BeepPin1 beep;

const unsigned int FRAME_RATE = 18; // Frame rate in frames per second
int dx = -1;        //Initial movement of ball
int dy = -1;        //Initial movement of ball
boolean released = false;     //If the ball has been released by the player
byte xPaddle1 = 54;       //X position of paddle
byte xPaddle2 = 54;  //X position of paddle 2
int xb =xPaddle1 + 5; //Balls starting position
int yb = 60;           //Balls starting position
boolean start=false;    //If in menu or in game
boolean buttonsEnabled = false;
boolean player1Wins = false;
//Ball Bounds used in collision detection
byte leftBall;
byte rightBall;
byte topBall;
byte bottomBall;



byte tick;

void setup()
{
  arduboy.begin();
  beep.begin();
  arduboy.setFrameRate(FRAME_RATE);
  arduboy.initRandomSeed();
}

void loop()
{
  // pause render until it's time for the next frame
  if (!(arduboy.nextFrame()))
    return;

  // Handle the timing and stopping of tones
    beep.timer();

  //Title screen loop switches from title screen
  //and high scores until FIRE is pressed
     while (!start)
  {
    start = titleScreen();
  }
  
   startNewGame();
}

//Move everything to start position
void resetGame(){
    released = false;     //If the ball has been released by the player
    xPaddle1 = 54;       //X position of paddle
    xPaddle2 = 54;  //X position of paddle 2
    xb =xPaddle1 + 5; //Balls starting position
    yb = 60;           //Balls starting position

}

//Clear screen, draw everything, enable buttons
void startNewGame(){
     arduboy.clear();

    drawPaddle1();
    drawPaddle2();

   
    drawBall();


   arduboy.display();
   buttonsEnabled = true;
}

void movePaddle1()
{
  //Move right
  if(xPaddle1 < WIDTH - 12)
  {
    if (arduboy.pressed(RIGHT_BUTTON) && (buttonsEnabled = true))
    {
      xPaddle1 +=2;
    }
  }

  //Move left
  if(xPaddle1 > 0)
  {
    if (arduboy.pressed(LEFT_BUTTON) && (buttonsEnabled = true))
    {
      xPaddle1 -=2;
    }
  }
}

void movePaddle2()
{
  //Move right
  if(xPaddle2 < WIDTH - 12)
  {
    if (arduboy.pressed(RIGHT_BUTTON_2) && (buttonsEnabled = true))
    {
      xPaddle2 +=2;
    }
  }

  //Move left
  if(xPaddle2 > 0)
  {
    if (arduboy.pressed(LEFT_BUTTON_2)  && (buttonsEnabled = true))
    {
      xPaddle2 -=2;
    }
  }
}

void moveBall()
{
  //tick++;
  if(released)
  {

      xb += dx;

    yb=yb + dy;

    //Set bounds
    leftBall = xb;
    rightBall = xb + 2;
    topBall = yb;
    bottomBall = yb + 2;

    //If goes off top, Player 2 loses
    if (yb <= 0)
    {
         player1Wins = true;
         start = false;
         playToneTimed(175, 500);
         
        while (!start)
      {
        start = gameOverScreen();
      }
  
      startNewGame();

      
    }

    //If goes off bottom, Player 1 loses
    if (yb >= 64)
    {
       player1Wins = false;
       start = false;
       playToneTimed(175, 500);
           while (!start)
      {
        start = gameOverScreen();
      }
  
      startNewGame();

    }



    //Bounce off left side
    if (xb <= 0)
    {
      xb = 1;
      dx = -dx;
      dy += 1; 
      playTone(523, 250);
    }

    //Bounce off right side
    if (xb >= WIDTH - 2)
    {
      xb = WIDTH - 3;
      dx = -dx;
      dy += 1;
  
      playTone(523, 250);
    }

    //Bounce off Paddle 1
    if (xb+1>=xPaddle1 && xb<=xPaddle1+12 && yb+2>=63 && yb<=64)
    {
      dy = -dy;
      dx += 1;
      playTone(200, 250);
    }

       //Bounce off Paddle 2
    if (xb+1>=xPaddle2 && xb<=xPaddle2+12 && yb+2>=6 && yb<=7)
    {
      dy = -dy;
      dx += 1;
      playTone(200, 250);
    }
  
   }

  else
  {
    //Ball follows paddle
    xb=xPaddle1 + 5;

    //Release ball if FIRE pressed
    if (arduboy.pressed(A_BUTTON))
    {
      released = true;

      //Apply random direction to ball on release
      if (random(0, 2) == 0)
      {
        dx = 1;
      }
      else
      {
        dx = -1;
      }
      //Makes sure the ball heads upwards
      dy = -1;
    }
  }
}

void drawBall()
{
  // arduboy.setCursor(0,0);
  // arduboy.print(arduboy.cpuLoad());
  // arduboy.print("  ");
  arduboy.drawPixel(xb,   yb,   0);
  arduboy.drawPixel(xb+1, yb,   0);
  arduboy.drawPixel(xb,   yb+1, 0);
  arduboy.drawPixel(xb+1, yb+1, 0);

  moveBall();

  arduboy.drawPixel(xb,   yb,   1);
  arduboy.drawPixel(xb+1, yb,   1);
  arduboy.drawPixel(xb,   yb+1, 1);
  arduboy.drawPixel(xb+1, yb+1, 1);
}

void drawPaddle1()
{
  arduboy.drawRect(xPaddle1, 63, 11, 1, 0);
  movePaddle1();
  arduboy.drawRect(xPaddle1, 63, 11, 1, 1);
}

void drawPaddle2()
{
  arduboy.drawRect(xPaddle2, 5, 11, 1, 0);
  movePaddle2();
  arduboy.drawRect(xPaddle2, 5, 11, 1, 1);
}






boolean titleScreen()
{
  //Clears the screen
  arduboy.clear();
  arduboy.setCursor(16,22);
  arduboy.setTextSize(2);
  arduboy.print("PING PONG");
  arduboy.setTextSize(1);
  arduboy.display();


    arduboy.setCursor(10, 53);
    arduboy.print("Player 1 Press A");
    arduboy.display();

    if (arduboy.pressed(A_BUTTON))
    {
      return true;
    }

  return false;
}

boolean gameOverScreen(){
       arduboy.clear();
       arduboy.setCursor(16,22);
       if (player1Wins == true){
        arduboy.print("Player 1 Wins!");
       }
       else {
        arduboy.print("Player 2 Wins!");
       }
       arduboy.setCursor(1, 32);
       arduboy.print("Press A to play again.");
       arduboy.display();
       resetGame();
       buttonsEnabled = false;

    if (arduboy.pressed(A_BUTTON))
    {
      return true;
    }

  return false;

}


// Play a tone at the specified frequency for the specified duration.
void playTone(unsigned int frequency, unsigned int duration)
{
  beep.tone(beep.freq(frequency), duration / (1000 / FRAME_RATE));
}

// Play a tone at the specified frequency for the specified duration using
// a delay to time the tone.
// Used when beep.timer() isn't being called.
void playToneTimed(unsigned int frequency, unsigned int duration)
{
  beep.tone(beep.freq(frequency));
  arduboy.delayShort(duration);
  beep.noTone();
}

