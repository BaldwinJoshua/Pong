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
 *
 * VERSION:
 * 0.0
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
playerScores[3] = {0x00, 0x00, 0x00}; //indexed from 1

unsigned char
maxScoreIndex = 2; //defaults to max score of 3

unsigned char
board[1][1] = {{'a'}}; //still don't know what to do here

unsigned char
maxScoreArr[5] = {1, 2, 3, 4, 5};

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

/****************************************************************************
 * Checks if the player can move in the direction given. Direction 0 is down,
 * direction 1 is up. Returns 0 if can't move and 1 if can move.
 *
 * @param{struct Player*} player
 * @param{unsigned char} direction
 * @return{unsigned char}
 ***************************************************************************/
unsigned char
checkPlayerMove (struct Player* player,
                 unsigned char direction);

/******************************************************************************
 * Moves the player in the direction given. Direction 0 is down, direction 1 is
 * up.
 *
 * @param{struct Player*} player
 * @param{unsigned char}
 * @return{void}
 *****************************************************************************/
void
movePlayer (struct Player* player,
            unsigned char direction);

/*********************************************************
 * Sets the players yPos to be in the middle of the screen
 *
 * @param{struct Player*} player
 * @return{void}
 ********************************************************/
void
resetPlayer (struct Player* player);

/*********************************
 * Displays the player to the OLED
 *
 * @param{struct Player*} player
 * @return{void}
 ********************************/
void
displayPlayer (struct Player* player);

//------------------------
//Ball Function Prototypes
//------------------------

/*******************************************************************************
 * Checks if the ball can be moved. Returns 0 if can't be moved (have to do trig
 * to calculate new position, e.g. bounces off paddle or wall), returns 1 if can
 * be moved (space is open)
 *
 * @param{struct Ball*} ball
 * @param{struct Player*} player
 * @return{unsigned char}
 ******************************************************************************/
unsigned char
checkBallMove (struct Ball* ball,
               struct Player* player);

/************************************
 * Moves the ball to the new position
 *
 * @param{struct Ball*} ball
 * @param{unsigned char} canMove
 * @return{void}
 ***********************************/
void
moveBall (struct Ball* ball,
          unsigned char canMove);

/******************************************************************************
 * Resets the ball to middle of board. Creates random yPos and random xVel/yVel
 *
 * @param{struct Ball*} ball
 * @return{void}
 *****************************************************************************/
void
resetBall (struct Ball* ball);

/*******************************
 * Displays the ball to the OLED
 *
 * @param{struct Ball*} ball
 * @return{void}
 ******************************/
void
displayBall (struct Ball* ball);

//------------------------
//Main Function Prototypes
//------------------------

/*********************************************************
 * Gets user input for the max score the game should go to
 *
 * @return{unsigned char}
 ********************************************************/
unsigned char
getMaxScoreIndex ();

/****************************************************************************
 * Checks to see if either of the players scored. Returns 0 if no one scored,
 * returns 1 or 2 if player 1 or 2 scored respectively
 *
 * @return{unsigned char}
 ***************************************************************************/
unsigned char
checkScored ();

/**************************************************
 * Increments the score of the player that is given
 *
 * @param{unsigned char} player
 * @return{void}
 *************************************************/
void
incrementScore (unsigned char player);

/*********************************************************************
 * Checks to see if the game is over. Returns 0 if not over, 1 if over
 *
 * @return{unsigned char}
 ********************************************************************/
unsigned char
checkGameOver ();

/********************************
 * Displays the board to the OLED
 *
 * @return{void}
 *******************************/
void
displayBoard ();

/*********************************
 * Displays the scores to the OLED
 *
 * @reutrn{void}
 ********************************/
void
displayScore();
  
/***************************************************************************
 * Resets the game. Resets player positions, play scores, ball position, and
 * gets a new maximum scorefrom getMaxScoreIndex()
 *
 * @return{void}
 **************************************************************************/
void
resetGame ();

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

//end Pong.c
