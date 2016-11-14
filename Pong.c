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

//------------------
//Struct Definitions
//------------------
struct
Player {
  volitile unsigned char
  xPos,
  yPos,
  width,
  height;
};//Player

struct
Ball {
  volitile unsigned char
  xPos,
  yPos;

  volitile signed char
  xVel,
  yVel;
};//Ball

//----------------
//Global Variables
//----------------
unsigned char
playerScores[3] = {0x00, 0x00, 0x00}; //indexed from 1

unsigned char
maxScoreIndex = 2; //defaults to max score of 3

unsigned char
board[1][1] = {{}}; //still don't know what to do here

unsigned char
maxScoreArr[4] = {1, 2, 3, 4, 5};

Player
players[2] = Player();

Ball
ball = Ball();

//--------------------------
//Player Function Prototypes
//--------------------------

/****************************************************************************
 * Checks if the player can move in the direction given. Direction 0 is down, 
 * direction 1 is up. Returns 0 if can't move and 1 if can move.
 *
 * @param{char} playerNdx
 * @param{unsigned char} direction
 * @return{unsigned char}
 ***************************************************************************/
unsigned char
checkPlayerMove (char playerNdx,
                 unsigned char direction);

/******************************************************************************
 * Moves the player in the direction given. Direction 0 is down, direction 1 is
 * up.
 * 
 * @param{char} playerNdx
 * @param{unsigned char}
 * @return{void}
 *****************************************************************************/
void
movePlayer (char playerNdx,
            unsigned char direction);

/*********************************************************
 * Sets the players yPos to be in the middle of the screen
 * 
 * @param{char} playerNdx
 * @return{void}
 ********************************************************/
void
resetPlayer (char playerNdx);

/*********************************
 * Displays the player to the OLED
 * 
 * @param{char} playerNdx
 * @return{void}
 ********************************/
void
displayPlayer (char playerNdx);

//------------------------
//Ball Function Prototypes
//------------------------

/*******************************************************************************
 * Checks if the ball can be moved. Returns 0 if can't be moved (have to do trig
 * to calculate new position, e.g. bounces off paddle or wall), returns 1 if can
 * be moved (space is open)
 *
 * @param{char} playerNdx
 * @return{unsigned char}
 ******************************************************************************/
unsigned char
checkBallMove (char playerNdx);

/************************************
 * Moves the ball to the new position
 * 
 * @param{unsigned char} canMove
 * @return{void}
 ***********************************/
void
moveBall (unsigned char canMove);

/******************************************************************************
 * Resets the ball to middle of board. Creates random yPos and random xVel/yVel
 * 
 * @return{void}
 *****************************************************************************/
void
resetBall ();

/*******************************
 * Displays the ball to the OLED
 * 
 * @return{void}
 ******************************/
void
displayBall ();

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
