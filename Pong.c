/**************************************************************************
 * PROJECT: Pong
 * 
 * DESCRIPTION:
 * Runs a pong game fusing the MSP430-G2553 with the sparkfun OLED breakout
 * board
 * 
 * AUTHORS:
 * Michael Fryer
 * Josh Baldwin
 * Tyler Fricks
 *************************************************************************/

//----------
//C Includes
//----------
#include <msp430.h>
#include <cstdlib>

//----------------
//Global Variables
//----------------
unsigned char
playerScores[3] = {0x00, 0x00, 0x00};

unsigned char
maxScoreIndex;

unsigned char
board[1][1] = {{}}; //still don't know what to do here

unsigned char
maxScoreArr[4] = {1, 2, 3, 4};

//------------------------
//Main Function Prototypes
//------------------------
unsigned char
getMaxScoreIndex ();

unsigned char
checkScored ();

void
incrementScore (unsigned char player);

unsigned char
checkGameOver ();

void
displayBoard ();

void
displayScore();

void
resetGame ();

//------------------
//Struct Definitions
//------------------
struct
Player {
  unsigned char
  xPos,
  yPos,
  width,
  height;
};//Player

struct
Ball {
  unsigned char
  xPos,
  yPos;

  signed char
  xVel,
  yVel;
};//Ball

//--------------------------
//Player Function Prototypes
//--------------------------
unsigned char
checkPlayerMove (struct Player* player,
                 unsigned char direction);

void
movePlayer (struct Player* player,
            unsigned char direction);

void
resetPlayer (struct Player* player);

void
displayPlayer (struct Player* player);

//------------------------
//Ball Function Prototypes
//------------------------
unsigned char
checkBallMove (struct Ball* ball,
               struct Player* player);

void
moveBall (struct Ball* ball);

void
resetBall (struct Ball* ball);

void
displayBall (struct Ball* ball);

//----
//main
//----
int
main (void) {

}//main

//-----------------------------
//Main Function Implementations
//-----------------------------

//-----------------------------
//Ball Function Implementations
//-----------------------------

//-------------------------------
//Player Function Implementations
//-------------------------------

//Pong