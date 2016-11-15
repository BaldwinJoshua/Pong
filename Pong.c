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
 * 0.1
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
  volatile unsigned char
  xPos,
  yPos,
  width,    //half-width
  height;   //half-height
};//Player

struct
Ball {
  volatile unsigned char
  xPos,
  yPos;

  volatile signed char
  xVel,
  yVel;
};//Ball

//----------------
//Global Variables
//----------------
unsigned char
playerScores[2] = {0x00, 0x00}; //indexed from 0

unsigned char
maxScoreIndex = 4; //defaults to max score of 5

unsigned char
board[1][1] = {{'a'}}; //still don't know what to do here

unsigned char
maxScoreArr[5] = {1, 2, 3, 4, 5};

unsigned char
X_MIN = 0;

unsigned char 
X_MAX = 47;

unsigned char
Y_MIN = 0;

unsigned char
Y_MAX = 63;

struct Player
players[2];

struct Ball
ball;

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
 * @param{unsigned char} playerNdx
 * @return{void}
 *************************************************/
void
incrementScore (unsigned char playerNdx);

/*********************************************************************
 * Checks to see if the game is over. Returns 0 if not over, 1 or 2 if
 * player 1 or 2 wins respectively
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
  
/*****************************************************************************
 * Resets the game. Resets player positions, player scores, ball position, and
 * gets a new maximum score from getMaxScoreIndex()
 *
 * @return{void}
 ****************************************************************************/
void
resetGame ();

//------------------------
//Ball Function Prototypes
//------------------------

/*************************************
 * Moves the ball to the new position.
 *
 * @return{void}
 ************************************/
void
moveBall ();

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

//--------------------------
//Player Function Prototypes
//--------------------------

/******************************************************************************
 * Moves the player in the direction given. Direction 0 is down, direction 1 is
 * up.
 * 
 * @param{unsigned char} playerNdx
 * @param{unsigned char}
 * @return{void}
 *****************************************************************************/
void
movePlayer (unsigned char playerNdx,
            unsigned char direction);

/*********************************************************
 * Sets the players yPos to be in the middle of the screen
 * 
 * @param{unsigned char} playerNdx
 * @return{void}
 ********************************************************/
void
resetPlayer (unsigned char playerNdx);

/*********************************
 * Displays the player to the OLED
 * 
 * @param{unsigned char} playerNdx
 * @return{void}
 ********************************/
void
displayPlayer (unsigned char playerNdx);

//----
//main
//----
int
main (void) {

  return 0;
}//main

//-----------------------------
//Main Function Implementations
//-----------------------------
unsigned char
getMaxScoreIndex () {
  return 4;
}//getMaxScoreIndex

void
incrementScore (unsigned char playerNdx) {
  playerScores[playerNdx]++;

  return;
}//incrementScore

unsigned char
checkGameOver () {
  if (playerScores[0] == maxScoreArr[maxScoreIndex]) {
    return 1;
  }//if
  else if (playerScores[1] == maxScoreArr[maxScoreIndex]) {
    return 2;
  }//else if
  else {
    return 0;
  }//else
}//checkGameOver

void
resetGame () {
  resetPlayer(0);
  resetPlayer(1);
  resetBall();
  getMaxScoreIndex();
  playerScores = {0x00, 0x00};

  return;
}//resetGame

//-----------------------------
//Ball Function Implementations
//-----------------------------
void
moveBall () {
  if (ball.yPos + ball.yVel > X_MIN && ball.yPos + ball.yVel < X_MAX) {
    ball.yPos += ball.yVel;
  }//if
  else {
    ball.yPos = Y_MAX - (ball.yPos + ball.yPos + X_MAX) % Y_MAX;
  }//else

  return;
}//moveBall

void
resetBall () {
  srand(CCR0 % 100);
  
  ball.xPos = 23;             //counting from 0 default to center of screen
  ball.yPos = rand() % (Y_MAX - 2) + 1;
  
  ball.yVel = rand() % 9 + 1;   //arbitrary max velocity
  srand(CCR0 % 100);            //so xVel not same as yVel
  ball.xVel = rand() % 9 + 1;   //arbitrary max velocity
  if (rand() % 2) {             //sets velocity direction
    ball.xVel *= 1;
  }//if
  else {
    ball.xVel *= -1;
  }//else
  
  return;
}//resetBall

//-------------------------------
//Player Function Implementations
//-------------------------------

void
movePlayer (unsigned char playerNdx, 
            unsigned char direction) {
  if (direction &&
      players[playerNdx].yPos + 1 + players[playerNdx].height < Y_MAX) {
    players[playerNdx].yPos++;
  }//if
  else if (players[playerNdx].yPos - 1 - players[playerNdx].height > Y_MIN) {
    players[playerNdx].yPos--;
  }//else if
  
  return;
}//movePlayer

void
resetPlayer (unsigned char playerNdx) {
  players[playerNdx].yPos = 31;   //counting from 0
  
  return;
}//resetPlayer
//end Pong.c