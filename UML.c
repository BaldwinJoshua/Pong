+++Player+++
+unsigned char xPos
+unsigned char yPos
+unsigned char width
+unsigned char height
---Player---

+++Ball+++
+unsigned char xPos
+unsigned char yPos
+signed char xVel
+signed char yVel
---Ball---

+++Pong+++
+unsigned char playerScores[3]
+unsigned char maxScoreIndex
+unsigned char board[][]
+unsigned char maxScoreArr[4]
+int  main()
---Pong---

+++Function Prototypes+++
+unsigned char checkMove(struct Player* player, unsigned char direction)
+void movePlayer(struct Player* player, unsigned char direction)
+void resetPlayer(struct Player* player)
+void displayPlayer(struct Player* player)

+unsigned char checkBallMove(struct Ball* ball, struct Player* player)
+unsigned char moveBall(struct Ball* ball, unsigned char canMove)
+void resetBall(struct Ball* ball)
+void displayBall(struct Ball* ball)

+unsigned char getMaxScoreIndex()
+unsigned char checkScored()
+void incrementScore(unsigned char player)
+unsigned char checkGameOver()
+void displayBoard()
+void displayScore()
+void resetGame()
---Function Prototypes---
