# CPPND: Capstone Snake Game Example

This is a starter repo for the Capstone project in the [Udacity C++ Nanodegree Program](https://www.udacity.com/course/c-plus-plus-nanodegree--nd213). The code for this repo was inspired by [this](https://codereview.stackexchange.com/questions/212296/player-game-in-c-with-sdl) excellent StackOverflow post and set of responses.

<img src="snake_game.gif"/>

The Capstone Project gives you a chance to integrate what you've learned throughout this program. This project will become an important part of your portfolio to share with current and future colleagues and employers.

In this project, you can build your own C++ application or extend this Snake game, following the principles you have learned throughout this Nanodegree Program. This project will demonstrate that you can independently create applications using a wide range of C++ features.

## Dependencies for Running Locally
* cmake >= 3.7
  * All OSes: [click here for installation instructions](https://cmake.org/install/)
* make >= 4.1 (Linux, Mac), 3.81 (Windows)
  * Linux: make is installed by default on most Linux distros
  * Mac: [install Xcode command line tools to get make](https://developer.apple.com/xcode/features/)
  * Windows: [Click here for installation instructions](http://gnuwin32.sourceforge.net/packages/make.htm)
* SDL2 >= 2.0
  * All installation instructions can be found [here](https://wiki.libsdl.org/Installation)
  >Note that for Linux, an `apt` or `apt-get` installation is preferred to building from source. 
* gcc/g++ >= 5.4
  * Linux: gcc / g++ is installed by default on most Linux distros
  * Mac: same deal as make - [install Xcode command line tools](https://developer.apple.com/xcode/features/)
  * Windows: recommend using [MinGW](http://www.mingw.org/)

## Basic Build Instructions

1. Clone this repo.
2. Make a build directory in the top level directory: `mkdir build && cd build`
3. Compile: `cmake .. && make`
4. Run it: `./SnakeGame`.

## Gameplay and additions

1. High resolution
2. Arrow keys control snake movement: left arrow turns left, right arrow turns right, up arrow speeds up, down arrow slows down
3. Snake begins with 100 "energy", uses energy as it moves.  The faster it moves, the more energy it uses.  Snake gains energy by eating food.  Snake loses energy by moving and by "eating" itself.  If the snake doubles back on itself and cuts itself in half, it will lose half of its energy.
4. When a snake is cut by another snake, its severed tail becomes food that can be eaten, but this food "rots" and disentegrates quickly
5. Running off the edge of the screen will kill the snake immediately
6. When the snake reaches 0 energy, it dies
7. Pressing escape key will exit game

## Rubric points addressed

### Compiling and Testing (All Rubric Points REQUIRED)
| Criteria                                                                                 | Submission Requirements |
|------------------------------------------------------------------------------------------|-------------------------|
| **The submission must compile and run without errors on the Udacity project workspace.** | We strongly recommend using cmake and make, as provided in the starter repos. If you choose another build system, the code must be compiled on the Udacity project workspace.<br/>---<br/>> **`used cmake`**     

### Loops, Functions, I/O - meet at least 2 criteria
| Criteria                                                                                           | Submission Requirements                                                                                         |
|----------------------------------------------------------------------------------------------------|-----------------------------------------------------------------------------------------------------------------|
| **The project demonstrates an understanding of C++ functions and control structures.**             | A variety of control structures are added to the project. <br/><br/>The project code is clearly organized into functions. <br/>---<br/>> **`hopefully everywhere`**     
| ~~The project reads data from a file and process the data, or the program writes data to a file.~~ | ~~The project reads data from an external file or writes data to a file as part of the necessary operation of the program.~~ 
| ~~The project accepts user input and processes the input.~~                                        | ~~In addition to controlling the snake, the game can also receive new types of input from the player.~~             
| **The project uses data structures and immutable variables.**                                      | The project uses arrays or vectors and uses constant variables. <br/>---<br/>> **`game.cpp:96-98`**, _et.al_<br/>> **`game.h:28-31`**                                                 

### Object Oriented Programming - meet at least 3 criteria
| Criteria                                                                                           | Submission Requirements                                                                                         |
|----------------------------------------------------------------------------------------------------|-----------------------------------------------------------------------------------------------------------------|
| One or more classes are added to the project with appropriate access specifiers for class members. | Classes are organized with attributes to hold data and methods to perform tasks.<br/><br/>All class data members are explicitly specified as public, protected, or private.<br/><br/>Member data that is subject to an invariant is hidden from the user and accessed via member methods.     
| ~~Class constructors utilize member initialization lists.~~                                        | ~~All class members that are set to argument values are initialized through member initialization lists.~~
| Classes abstract implementation details from their interfaces.                                     | All class member functions document their effects, either through function names, comments, or formal documentation.<br/><br/>Member functions do not change the program state in undocumented ways.
| **Overloaded functions allow the same function to operate on different parameters.**               | One function is overloaded with different signatures for the same function name.<br/>---<br/>> **`snake.h:25-26`**     
| **Classes follow an appropriate inheritance hierarchy with virtual and override functions.**       | Inheritance hierarchies are logical. One member function in an inherited class overrides a virtual base class member function.<br/>---<br/>> `WorldObject.h:25-40` and overrides in `food.h`, `snake.h`, _etc_    
| **Templates generalize functions or classes in the project.**                                      | One function or class is declared with a template that allows it to accept a generic parameter.<br/>---<br/>> **`game.h:41-42`**     

### Memory Management - meet at least 3 criteria
| Criteria                                                                                  | Submission Requirements                                                                                         |
|-------------------------------------------------------------------------------------------|-----------------------------------------------------------------------------------------------------------------|
| **The project makes use of references in function declarations.**                         | At least two variables are defined as references, or two functions use pass-by-reference in the project code.<br/>---<br/>> **`snake.h:46-49`**     
| ~~The project uses destructors appropriately.~~                                           | ~~At least one class that uses unmanaged dynamically allocated memory, along with any class that otherwise needs to modify state upon the termination of an object, uses a destructor.~~
| ~~The project uses scope / Resource Acquisition Is Initialization (RAII) where appropriate.~~ | ~~The project follows the Resource Acquisition Is Initialization pattern where appropriate, by allocating objects at compile-time, initializing objects when they are declared, and utilizing scope to ensure their automatic destruction.~~
| ~~The project follows the Rule of 5.~~                                                    | ~~For all classes, if any one of the copy constructor, copy assignment operator, move constructor, move assignment operator, and destructor are defined, then all of these functions are defined.~~
| The project uses move semantics to move data instead of copying it, where possible.       | The project relies on the move semantics, instead of copying the object.<br/>---<br/>> **`game.cpp:86, 130`**     
| **The project uses smart pointers instead of raw pointers.**                              | The project uses at least one smart pointer: unique_ptr, shared_ptr, or weak_ptr.<br/>---<br/>> **`game.cpp:15, 70, 155`**     

### Concurrency - meet at least 2 criteria
| Criteria                                         | Submission Requirements                                                                                         |
|--------------------------------------------------|-----------------------------------------------------------------------------------------------------------------|
| **The project uses multithreading.**             | The project uses multiple threads or async tasks in the execution.<br/>---<br/>> **`game.cpp:83-94`**     
| **A promise and future is used in the project.** | A promise and future is used to pass data from a worker thread to a parent thread in the project code.<br/>---<br/>> **`game.cpp:126-142`**     
| ~~A mutex or lock is used in the project.~~      | ~~A mutex or lock (e.g. std::lock_guard or `std::unique_lock) is used to protect data that is shared across multiple threads in the project code.~~
| ~~A condition variable is used in the project.~~ | ~~A std::condition_variable is used in the project code to synchronize thread execution.~~

## CC Attribution-ShareAlike 4.0 International


Shield: [![CC BY-SA 4.0][cc-by-sa-shield]][cc-by-sa]

This work is licensed under a
[Creative Commons Attribution-ShareAlike 4.0 International License][cc-by-sa].

[![CC BY-SA 4.0][cc-by-sa-image]][cc-by-sa]

[cc-by-sa]: http://creativecommons.org/licenses/by-sa/4.0/
[cc-by-sa-image]: https://licensebuttons.net/l/by-sa/4.0/88x31.png
[cc-by-sa-shield]: https://img.shields.io/badge/License-CC%20BY--SA%204.0-lightgrey.svg
