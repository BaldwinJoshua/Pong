+++Player+++
-char xPos
-char yPos
-char width
-char height
+char checkMove(char direction) //returns 0 for no move, returns 1 for move
                                //direction 0 for down, 1 for up
+void move(char direction)      //direction 0 for down, 1 for up
+void resetPlayer()             //sets yPos to center
+void displayPlayer()
---Player---

+++Ball+++
-char xPos
-char yPos
-signed char xVel //negative down, positive up
-signed char yVel //negative left, positive right
+char checkMove(char paddleX,
                char paddleY,
                char paddleWidth,
                char paddleHeight) //returns 0 if can't move
                                      //have to do trig to bounce ball
                                   //returns 1 if can move
+char moveBall()
+void resetBall()   //picks random starting yPos and initial x/y velocities
+void displayBall()
---Ball---

+++Pong+++
-char playerScores[3] //index from 1
-char maxScoreIndex   //[0, 4] index for maxScoreArr
+char board[][]       //not sure how we are going to implement this
+char maxScoreArr[4]  //{1, 2, 3, 4} e.g. best of 1, 3, 5, 7
+int  main()
+char getMaxScoreIndex()  //on screen display for setting best of X points
+char checkScored()   //returns 0 for no, returns 1/2 for player 1/2 score
+void incrementScore(char player) //increments score for player given.
                                  //returns if player not equal to 1 or 2
+char checkGameOver() //returns 0 for not over, returns 1/2 for player 1/2 win
+void displayBoard()
+void displayScore()
+void resetGame()     //gets new best of X points, resets player positions, 
                      //resets player scores, resets ball
---Pong---
