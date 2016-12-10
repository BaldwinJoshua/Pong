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
	score;
};//Player

struct
Ball {
	volatile unsigned char
	xPos,
	yPos,
	radius;   //makes a 3x3 ball cube

	volatile signed char
	xVel,
	yVel;
};//Ball

//------------------
//Global Definitions
//------------------
#define T_DELAY       4
#define CHIP_SELECT   BIT0
#define RESET         BIT1
#define DATA_COMMAND  BIT2
#define CLOCK         BIT3
#define MOSI          BIT4
#define _BV(n)        1 << n
#define LCD_WIDTH     64
#define LCD_HEIGHT    48
#define SCOREY		  0
#define MAX_SCORE	  7

//----------------
//Global Variables
//----------------

volatile
unsigned int
JOYSTICK_VALUES[2] = {0x300, 0x300}; //joy stick values

volatile
unsigned char
SCREEN_MEMORY[] = {

		// ROW0, BYTE0 to BYTE63
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,

		// ROW1, BYTE64 to BYTE127
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,

		// ROW2, BYTE128 to BYTE191
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,

		// ROW3, BYTE192 to BYTE255
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,

		// ROW4, BYTE256 to BYTE319
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,

		// ROW5, BYTE320 to BYTE383
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

volatile
unsigned char
X_MIN = 0,
X_MAX = LCD_WIDTH - 1,
Y_MIN = 0,
Y_MAX = LCD_HEIGHT - 1,
PLAYER_WIDTH = 1,   //half width
PLAYER_HEIGHT = 5;  //half height

volatile
struct Player
PLAYER_ARRAY[2];

volatile
struct Ball
BALL;

//------------------------
//Main Function Prototypes
//------------------------

/*****************************************************************************
 * Resets the game. Resets player positions, player scores, ball position, and
 * gets a new maximum score from getMaxScoreIndex()
 *
 * @return{void}
 ****************************************************************************/
void
resetGame ();

/*********************************
 *
 *
 * @param{char} send
 * @return{void}
 ********************************/
void
spi_transfer (char send);

/*********************************
 *
 *
 * @param{char} add
 * @return{void}
 ********************************/
void
send_command (char add);

/*********************************
 *
 *
 * @param{char} add
 * @return{void}
 ********************************/
void
setPageAddress (char add);

/*********************************
 *
 *
 * @param{char} add
 * @return{void}
 ********************************/
void
setColumnAddress (char add);

/*********************************
 *
 *
 * @param{char} send
 * @return{void}
 ********************************/
void
send_data (char send);

/*********************************
 *
 *
 * @return{void}
 ********************************/
void
display ();

/*********************************
 *
 *
 * @return{void}
 ********************************/
void
clear ();

/*********************************
 *
 *
 * @param{char} x
 * @param{char} y
 * @param{char} mode
 * @return{void}
 ********************************/
void
pixel (char x,
		char y,
		unsigned char mode);

/*********************************
 *
 *
 * @param{char} x0
 * @param{char} y0
 * @param{char} x1
 * @param{char} y1
 * @param{char} mode
 * @return{void}
 ********************************/
void
line (char x0,
		char y0,
		char x1,
		char y1,
		unsigned char mode);

/*********************************
 *
 *
 * @return{void}
 ********************************/
void
init();

/*********************************
 * Gets the values of both of the controllers
 *
 * @return{void}
 ********************************/
void
getADC ();

//------------------------
//Ball Function Prototypes
//------------------------

/*****************************************************************
 * Moves the ball to the new position. Returns 1 if someone scored
 *
 * @return{char}
 ****************************************************************/
char
moveBall ();

/*****************************************************************
 * Draws the ball to the new position.
 *
 * @param{unsigned char} mode
 * @return{void}
 ****************************************************************/
void
drawBall (unsigned char mode);

/******************************************************************************
 * Resets the ball to middle of board. Creates random yPos and random xVel/yVel
 *
 * @return{void}
 *****************************************************************************/
void
resetBall ();

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
 * Sets player location on OLED
 *
 * @param{unsigned char} playerNdx
 * @return{void}
 ********************************/
void
setPlayer (unsigned char playerNdx, unsigned char mode);

/*********************************
 * Draws score for each palyer
 *
 * @param{unsigned char} mode
 * @return{void}
 ********************************/
void
drawScore(unsigned char mode);

/*********************************
 * Reset score for each palyer
 *
 * @return{void}
 ********************************/
void
resetScore();

//-----------------------------
//Main Function Implementations
//-----------------------------

void
resetGame () {
	setPlayer(0,1);
	setPlayer(1,1);
	resetPlayer(0);
	resetPlayer(1);
	setPlayer(0,0);
	setPlayer(1,0);
	resetBall();

	return;
}//resetGame

void
spi_transfer(char send){
	int
	l;

	P2OUT &= ~CHIP_SELECT;     // Drop CHIP_SELECT low
	__delay_cycles(T_DELAY);
	for(l = 0; l < 8; l++) { // Send/receive bits
		if (send & BIT7) {  //set or clear MOSI bit
			P2OUT |= MOSI;
		}//if
		else {
			P2OUT &= ~MOSI;
		}//else
		__delay_cycles(T_DELAY);
		P2OUT |= CLOCK;     //Clock up
		__delay_cycles(T_DELAY / 2);
		__delay_cycles(T_DELAY / 2);
		P2OUT &= ~CLOCK;      // clock down
		send <<= 1;

		__delay_cycles(T_DELAY);
	}//for
	P2OUT |= CHIP_SELECT;      //Pull CHIP_SELECT high

	return;
}//spi_transfer

void
send_command (char send) {
	P2OUT &= ~DATA_COMMAND; // Turn command pin low to send commands.
	spi_transfer(send);
	P2OUT |= DATA_COMMAND;

	return;
}//send_command

void
setPageAddress (char add) {
	add = 0xb0 | add;
	send_command(add);

	return;
}//setPageAddress

void
setColumnAddress (char add) {
	send_command((0x10 | (add >> 4)) + 0x02);
	send_command((0x0f & add));

	return;
}//setColumnAddress

void
send_data (char send) {
	P2OUT |= DATA_COMMAND; // Turn command pin high to send commands.
	spi_transfer(send);
	P2OUT &= ~DATA_COMMAND;

	return;
}//send_data

void
display () {
	char
	i, j;

	for (i = 0; i < 6; i++) {
		setPageAddress(i);
		setColumnAddress(0);
		for (j = 0; j < 0x40; j++) {
			send_data(SCREEN_MEMORY[i * 0x40 + j]);
		}//for
	}//for

	return;
}//display

void
clear () {
	char
	i, j;

	for (i = 0; i < 6; i++) {
		setPageAddress(i);
		setColumnAddress(0);
		for (j = 0; j < 0x40; j++) {
			send_data(0);
		}//for
	}//for
}//clear

void
pixel (char x, char y, unsigned char mode) {
	if ((x >= LCD_WIDTH) || (y >= LCD_HEIGHT)) {
		return;
	}//if

	if (mode == 1) {
		SCREEN_MEMORY[x + (y / 8) * LCD_WIDTH] ^= _BV((y % 8));
	}//if
	else {
		SCREEN_MEMORY[x + (y / 8) * LCD_WIDTH] |= _BV((y % 8));
	}//else
}//pixel

void
line (char x0, char y0, char x1, char y1, unsigned char mode) {
	char
	steep = abs(y1 - y0) > abs(x1 - x0);

	if (steep) {
		volatile char
		temp = x0;

		x0 = y0;
		y0 = temp;

		temp = x1;
		x1 = y1;
		y1 = temp;
	}//if

	if (x0 > x1) {
		volatile char
		temp = x0;

		x0 = x1;
		x1 = temp;

		temp = y0;
		y0 = x1;
		y1 = temp;
	}//if

	char
	dx = x1 - x0,
	dy = abs(y1 - y0),
	err = dx / 2,
	ystep;

	if (y0 < y1) {
		ystep = 1;
	}//if
	else {
		ystep = -1;
	}//else

	for (; x0 < x1; x0++) {
		if (steep) {
			pixel(y0, x0, mode);
		}//if
		else {
			pixel(x0, y0, mode);
		}//else

		err -= dy;
		if (err < 0) {
			y0 += ystep;
			err += dx;
		}//if
	}//for
}//line

void
init () {
	volatile unsigned char
	txbuf[24];

	char
	i = 0;

	P2OUT &= ~RESET;
	__delay_cycles(50000);
	P2OUT |= RESET;

	txbuf[0] = 0xAE;
	txbuf[1] = 0xD5;
	txbuf[2] = 0x80;
	txbuf[3] = 0xA8;
	txbuf[4] = 0x2F;
	txbuf[5] = 0xD3;
	txbuf[6] = 0x00;
	txbuf[7] = 0x40 | 0x00; // startline
	txbuf[8] = 0x8D;
	txbuf[9] = 0x14;
	txbuf[10] = 0xA6;
	txbuf[11] = 0xA4;
	txbuf[12] = 0xA0 | 0x1;
	txbuf[13] = 0xC0;
	txbuf[14] = 0xDA;
	txbuf[15] = 0x12;
	txbuf[16] = 0x81;
	txbuf[17] = 0x8F;
	txbuf[18] = 0xD9;
	txbuf[19] = 0xF1;
	txbuf[20] = 0xDB;
	txbuf[21] = 0x40;
	txbuf[22] = 0xAF;

	for(i = 0; i < 23; i++){
		send_command(txbuf[i]);
	}//for

	return;
}//init

void
getADC () {
	char
	k;

	for (k = 2; k >= 1; k--) {
		ADC10CTL0 &= 0xFD;
		ADC10CTL1 = (0x1000u * (3 - k));        // 3 - k because want 1 and 2
		ADC10CTL0 |= ENC + ADC10SC;             // Sampling and conversion start
		while (ADC10CTL1 & ADC10BUSY);          // ADC10BUSY?
		JOYSTICK_VALUES[2 - k] = ADC10MEM;      // 2 - k because want 0 and 1
	}//for

	return;
}//getADC

//-----------------------------
//Ball Function Implementations
//-----------------------------
char
moveBall () {
	// Y-Axis stuff (floor and ceiling)
	if (BALL.yPos + BALL.yVel - 1 < Y_MIN ||
			BALL.yPos + BALL.yVel > Y_MAX) {
		BALL.yVel *= -1;
	}//if

	// X-Axis stuff (paddles)
	if(BALL.xPos + BALL.xVel <= 2){
		if(BALL.yPos < PLAYER_ARRAY[0].yPos + PLAYER_HEIGHT &&
				BALL.yPos > PLAYER_ARRAY[0].yPos - PLAYER_HEIGHT){
			BALL.xVel *= -1;
		}// if
		else{
			PLAYER_ARRAY[1].score += 1;
			if(PLAYER_ARRAY[1].score >= MAX_SCORE){
				drawScore(1);
				resetScore();
			}

			resetGame();
		}// else
	}// if

	if(BALL.xPos + BALL.xVel >= 62){
		if(BALL.yPos < PLAYER_ARRAY[1].yPos + PLAYER_HEIGHT &&
				BALL.yPos > PLAYER_ARRAY[1].yPos - PLAYER_HEIGHT){
			BALL.xVel *= -1;
		}// if
		else{
			PLAYER_ARRAY[0].score += 1;
			if(PLAYER_ARRAY[0].score >= MAX_SCORE){
				drawScore(1);
				resetScore();
			}
			resetGame();
		}// else
	}// if

	BALL.xPos += BALL.xVel;
	BALL.yPos += BALL.yVel;

	return 1;
}//moveBall

void
drawBall (unsigned char mode){
	pixel(BALL.xPos, BALL.yPos, mode);
	pixel(BALL.xPos, BALL.yPos - 1, mode);
	pixel(BALL.xPos - 1, BALL.yPos - 1, mode);
	pixel(BALL.xPos - 1, BALL.yPos, mode);
}// drawBall

void
resetBall () {
	srand(JOYSTICK_VALUES[0]);

	BALL.xPos = X_MAX / 2;        //counting from 0 default to center of screen
	BALL.yPos = rand() % (Y_MAX - 2) + 1;

	BALL.yVel = rand() % 2 + 1;   //arbitrary max velocity

	srand(JOYSTICK_VALUES[1]);            //so xVel not same as yVel

	BALL.xVel = rand() % 2 + 1;   //arbitrary max velocity

	if (!(rand() % 2)) {          //sets velocity direction
		BALL.xVel *= -1;
	}//if

	return;
}//resetBall

//-------------------------------
//Player Function Implementations
//-------------------------------

void
movePlayer (unsigned char playerNdx,
		unsigned char direction) {
	if (direction &&
			(PLAYER_ARRAY[playerNdx].yPos + PLAYER_HEIGHT + 2) <= Y_MAX) {
		PLAYER_ARRAY[playerNdx].yPos += 2;
	}//if
	else if ((PLAYER_ARRAY[playerNdx].yPos - PLAYER_HEIGHT - 2) >= Y_MIN) {
		PLAYER_ARRAY[playerNdx].yPos -= 2;
	}//else if

	return;
}//movePlayer

void
resetPlayer (unsigned char playerNdx) {
	PLAYER_ARRAY[playerNdx].yPos = Y_MAX / 2;   //counting from 0

	return;
}//resetPlayer

void
setPlayer (unsigned char playerNdx, unsigned char mode) {
	line(PLAYER_ARRAY[playerNdx].xPos, PLAYER_ARRAY[playerNdx].yPos - PLAYER_HEIGHT,
			PLAYER_ARRAY[playerNdx].xPos, PLAYER_ARRAY[playerNdx].yPos + PLAYER_HEIGHT, mode);
	line(PLAYER_ARRAY[playerNdx].xPos - 1, PLAYER_ARRAY[playerNdx].yPos - PLAYER_HEIGHT,
			PLAYER_ARRAY[playerNdx].xPos - 1, PLAYER_ARRAY[playerNdx].yPos + PLAYER_HEIGHT, mode);

	return;
}//setPlayer

void
drawScore(unsigned char mode){
	unsigned char scoreX = (LCD_WIDTH)/2;
	volatile unsigned char i;

	for(i = 0; i < PLAYER_ARRAY[0].score; i++)
	{
		scoreX -= 3;
		line(scoreX, SCOREY, scoreX, SCOREY+3,mode);
	}

	scoreX = (LCD_WIDTH)/2;

	for(i = 0; i < PLAYER_ARRAY[1].score; i++)
	{
		scoreX += 3;
		line(scoreX, SCOREY, scoreX, SCOREY+3,mode);
	}
}//drawScore

void
resetScore(){
	PLAYER_ARRAY[0].score = 0;
	PLAYER_ARRAY[1].score = 0;
}

//----
//main
//----
int
main (void) {
	WDTCTL = WDTPW | WDTHOLD;  // Stop watchdog timer
	ADC10CTL0 = SREF_1 + ADC10SHT_2 + REFON + ADC10ON;
	P2DIR |= (MOSI + CLOCK + CHIP_SELECT + DATA_COMMAND + RESET);    // 0-MOSI 1-CLOCK 2-CHIP_SELECT
	P2OUT |= (CHIP_SELECT + DATA_COMMAND + RESET);         // CS initially High
	P2OUT &= ~(CLOCK + MOSI);     // CLK and MOSI initially low

	BALL.radius = 1;                  //set ball radius
	resetBall();
	PLAYER_ARRAY[0].xPos = X_MIN + 1; //set left paddle xPos
	PLAYER_ARRAY[1].xPos = X_MAX;     //set right paddle xPos

	init();
	pixel(BALL.xPos, BALL.yPos, 1);
	pixel(BALL.xPos, BALL.yPos - 1, 1);
	pixel(BALL.xPos - 1, BALL.yPos - 1, 1);
	pixel(BALL.xPos - 1, BALL.yPos, 1);

	unsigned char
	k;

	for (k = 0; k < 2; k++) {
		resetPlayer(k);
		line(PLAYER_ARRAY[k].xPos, PLAYER_ARRAY[k].yPos - PLAYER_HEIGHT, PLAYER_ARRAY[k].xPos, PLAYER_ARRAY[k].yPos + PLAYER_HEIGHT, 0);
		line(PLAYER_ARRAY[k].xPos - 1, PLAYER_ARRAY[k].yPos - PLAYER_HEIGHT, PLAYER_ARRAY[k].xPos - 1, PLAYER_ARRAY[k].yPos + PLAYER_HEIGHT, 0);
	}//for

	while (1) {
		getADC();

		for (k = 0; k < 2; k++) {//checks both players to see if their joysticks are pressed
			if (JOYSTICK_VALUES[k] < 500) {
				setPlayer(k, 1);
				movePlayer(k, 0);
				setPlayer(k, 0);
			}//if
			else if (JOYSTICK_VALUES[k] > 800) {
				setPlayer(k, 1);
				movePlayer(k, 1);
				setPlayer(k, 0);
			}//else if
		}//for

		drawBall(1);
		moveBall();
		drawBall(0);

		line(LCD_WIDTH/2, 0, LCD_WIDTH/2, LCD_HEIGHT, 0);
		drawScore(0);

		__delay_cycles(T_DELAY);
		display();
	}//while

	return 0;
}//main
//end Pong.c
