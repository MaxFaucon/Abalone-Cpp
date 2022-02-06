# Abalone Project

## Table of contents
- [General info](#general-info)
	- [Introduction](#introduction)
	- [Technologies](#technologies)
	- [Repository Structure](#repository-structure)
	- [Authors](#authors)
- [Analysis](#analysis)
	- [Class Diagram](#class-diagram)
		- [Color](#color)
		- [Player](#player)
		- [Position](#position)
		- [Hexagon](#hexagon)
		- [Board](#board)
		- [Game](#game)
	- [Details](#details)
- [Implementation](#implementation)
    - [Deviations from the analysis](#deviations-from-the-analysis) 
- [Graphical User Interface](#graphical-user-interface)
## General info

### Introduction
The project aim is to develop the game **Abalone** in groups of two. There will be a console and a graphic version. Abalone is a board game played by 2 players on a hexagonal board. This board contains 61 squares. Each player starts the game with 14 marbles on their side of the board. The object of the game is to knock 6 opposing marbles off the board. 

The project is divided into three parts: 
1. The modeling of the software.
2. The model implementation with the console interface.
3. A graphical user interface.

See the project statement for more details.
### Technologies
The languages, libraries we used :
- C++17
- Catch2 for the tests
- Doxygen for the documentation
### Repository Structure
- `abalone-52006-52977/` : The C++ QT project.
    - `libs/`
        -  `catch2/` : The catch2 library.
    - `src/`
        - `abalonecore/` : Model library for Abalone.
            - `model/` : The model classes implementation.
            - `observer/` : The observer classes implementation
        - `tui/` : Terminal User Interface.
            - `controller/` : The controller class implementation.
            - `main/` : The main class implementation.
            - `view/` : The view class implementation.
    - `tests/` : The test classes.
- `analyse/` : The .mdj version of the class diagram detailed in this README.
- `Images/` : All the images used in this README.
- `.gitignore` : The gitignore file.
- `README.md` : This file.
### Authors
Olivier Dyck and Maximilien Faucon.

## Analysis
This part took us 10-15 hours of work.
All the documentation is detailed in this readme.
### Class Diagram
![Abalone_ClassDiagram.png](/Images/Abalone_ClassDiagram.png)
### Color
Enumeration that represents the differents colors that an hexagon can have.
`NONE` is for the hexagons without marbles.
### Player
Represents a player in the game.
- Attributes :
	- `m_color` : The player's color.
	- `m_ejectedOpponentMarbles` : The number of opposing marbles that the current player has ejected.
- Methods :
	- `Player(color: Color)` : Constructor of Player.
	- `color(): Color` : Getter of color.
	- `ejectedOpponentBalls(): int` : Getter of ejectedOpponentBalls.
### Position
Represents the position of an hexagon on the Board.
- Attributes :
	- `m_x` : The position on the x-axis (rows).
	- `m_y` : The position on the y-axis (columns).
- Methods :
	- `Position(int x, int y)` : Basic constructor of Position.
	- `Position(char x, int y)` : Second constructor of Position but used for the user input. The user will enter a number (column) and a letter (row) and this constructor will convert it into 2 numbers.
	- `x(): int` : Getter of x.
	- `y(): int` : Getter of y.
#### Hexagon
Represents an hexagon on the game board.
For the implementation, we have chosen to make hexagons that can either have a color: white or black or no color (NONE). 
To represent the movement of a marble, it's just two squares that will change color.
- Attributes :
	- `m_color` : The color of the Square.
- Methods :
	- `Hexagon(color: Color)` : Constructor of Hexagon.
	- `color(): Color` : Getter of the hexagon color.
	- `color(color: Color)` : Setter of the hexagon color.
### Board
Represents the game board.
For the implementation, we have chosen to make a bidimensional array of Hexagon instead of an array with 3 axis. 
We made this choice because we found it easier to implement. The difficulty will be in the movements of the marbles. For the moves, we use the ABA-PRO system.

For [More details](#details) on the board and the moves.
- Attributes :
	- `m_hexagons` : A bidimensional array of Hexagon of length 9 (9x9).
- Methods :
	- `Board()` : Constructor of Board. Creates all the hexagons of the Board.
	- `move(position1:Position, position2:Position, currentPlayer:Player): Boolean` : Manages a marble move if the user enter 2 positions (linear move). Returns true if the move was successfull.
	- `move(position1:Position, position2:Position, position3:Position, currentPlayer:Player): Boolean` : Manages a marble move if the user enter 3 positions (lateral move). Returns true if the move was successfull.
	- `hexagonColor(position: Position): Color` : Gives the color of a hexagon at a certain position.
	- `linearMove(position1:Position, position2:Position, currentPlayer:Player)` : Makes a linear move.
	- `possibleLinearMove(position1:Position, position2:Position, currentPlayer:Player): Boolean` : Checks if the linear move is possible.
	- `lateralMove(position1:Position, position2:Position, position3:Position, currentPlayer:Player)` : Makes a lateral move.
	- `possibleLateralMove(position1:Position, position2:Position, position3:Position, currentPlayer:Player): Boolean` : Checks if the lateral move is possible.
### Game
Represents the model of the game. Manages all the methods needed to play the game.
- Attributes :
	- `m_player1` : The first player of the game (Black).
	- `m_player2` : The second player of the game (White).
	- `m_currentPlayer` : Reference to the player who must play.
	- `m_board` : The game board.
- Methods :
	- `Game()` : Constructor of Game.
	- `isOver(): Boolean` : Checks if the game is over.
	- `playTurn(positions: Position[2..3]): Boolean` : Manages a player's turn. `positions` is a board of length 2 or 3 that contains the positions entered by the player.
	- `verifiesPositions(positions:Position[2..3]): Boolean` : Verifies if the inputs entered by the player are possible.
	- `winner(): Player` : Gives the winner of the game.
	- `board(): Board` : Getter of Board.
	- `changeCurrentPlayer()` : Changes the current player.
## Details
In our implementation the abalone board on the [Figure 1](#figure-1) is represented by the bidimensional array on the [Figure 2](#figure-2). 
As in a hexagonal table, each square has 6 neighbors and in a classic table, each square has 8 neighbors, it is necessary to determine which neighbors are allowed.
With the arrows on G6 on the [Figure 2](#figure-2), we can see all the neighbors for a square in a bidimensional array. 
The possible moves will therefore be :
- `-x, y`
- `-x, +y`
- `x, -y`
- `x, +y`
- `+x, -y`
- `+x, y`

&rarr; Unauthorized moves will be `+x, +y` and `-x, -y`.
Also, all extra squares in the bidimensional board will be set to `null`. They will therefore be inaccessible.
#### Figure 1
![Abalone_Board](/Images/Abalone_Board.png) 
#### Figure 2
![Bidimensional_Array](/Images/Bidimensional_Array.jpg)

## Implementation
This part took us approximately 30-40 hours of work.
### Deviations from the analysis : 
- Adding Observer/Observable design pattern.
- **Player** :
    - Adding a setter for `color` (used for the tests).
    - Adding a setter for `ejectedOpponenetMarbles`.
- **Position** :
    - Adding a setter for `x` and `y`. 
- **Board** :
    - Adding a `changeColor` method to change the color of an hexagon.
    - Adding several private methods : `correctLateralPositions`, `correctPositions`, `positionIsInside`, `changePosition`, `nextPosition`. 
- **Game** :
    - Adding a getter for `currentPlayer`. 
    - Adding a `initGame` method to initialize the game.
    - Removal of the `verifiesPositions` method.
    - Adding a private method `makesMove`.
