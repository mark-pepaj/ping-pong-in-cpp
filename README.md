# ping-pong-in-cpp

## Intro
As the name of the repository suggests, this is the classic ping pong game in C++ using the raylib library which allows you to create a window and draw objects in the window at particular coordinates.  
The game itself is very simple. It consists of two paddles and a square pong. The paddles move up and down using AWSD and the arrow keys and the pong begins with a random combination of left or right and up or down.  
The pong bounces off the paddles but counts as a point for player one if it hits the right wall or a point for player two if it hits the left wall.  
Also, once a paddle reaches the top or bottom of the window, it bounces back in the opposite direction.

## Quick Start
#### Note: Currently the game only supports Mac and Linux.
Both the executable file and the source code are included in the repository.  
Clone the repository, cd into the directory, and run the executable file  
```./pong```

## Implementation
The game is implemented in C++ primarily relying on the raylib library for rendering the window and drawing objects.  
To keep track of the velocity and location of the players and of the pong, I kept variables: playerOneY, playerTwoY, playerOneY_velocity, playerTwoY_velocity, pongX, pongY, pongX_velocity, pongY_velocity.  
Notice that for the players, only the vertical velocity mattered since the paddles only move up and down.  
Also, I kept track of the score with playerOneScore and playerTwoScore.  

### Starting the game:
At first the game would begin as soon as the file was executed.  
To improve the quality of the game, I added a feature that kept the game paused until the space bar is pressed and I displayed these instructions until the space bar is pressed.  


### Score:
As mentioned in the introduction, players can earn points by hitting the pong to their opponents wall.  
If the pong hits your opponents wall, you earn a point.  
The score is printed at the top of the screen for both players.  
When a player reaches 10 points, the game ends and the winner is congradulated on their victory.


### Collisions:
A collision happens when the pong hits the ceiling or the floor or a paddle.
To check if the pong is hitting the ceiling or the floor, we just need to check if the y-coordinate of the pong is the same as the y-coordinate of the ceiling or the floor.  
We already know the height of the window we created and we know the y-coordinate of the pong at al times.  
Similary, collisions with the paddles can be found by checking if the x-coordinate of the pong is the same as the x-coordinate of either of the paddles.  
Here we also need to check if the y-coordinate of the pong is between the top and the bottom of either of the paddles.  

To create the bouncing affect, we can just switch the velocity to the opposite direction (i.g. velocity of 50 pixels/sec becomes -50 pixels/sec). 

