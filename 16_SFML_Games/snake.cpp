#include <SFML/Graphics.hpp>
#include <time.h>
using namespace sf;

const int GRID_WIDTH = 30;// number of cells in width
const int GRID_HEIGHT = 20;// number of cells in height 
const int CELL_SIZE=16; // size of each cell in pixels
const int WINDOW_WIDTH = CELL_SIZE * GRID_WIDTH; // Total window width in pixels
const int WINDOW_HEIGHT = CELL_SIZE * GRID_HEIGHT; // total window height in pixels 

int direction,num=4; // direction of snake movement and initial lenght of the snake

struct Snake // structure of snake segment 
{ 
    int x,y;
} snakeSegments[100]; //  snake can have up to 100 segments 

struct Fruit // structer of fruit
{ 
    int x,y;
} fruit;

void Tick() // function that update game state each tick 
 {
    // move each part of the snake to the position of th part before it 
    for (int i=num;i>0;--i)
     {snakeSegments[i].x=snakeSegments[i-1].x; snakeSegments[i].y=snakeSegments[i-1].y;}

    // update position of the snake head based on the direction
    if (direction==0) snakeSegments[0].y+=1;  // move down    
    if (direction==1) snakeSegments[0].x-=1;  // move left      
    if (direction==2) snakeSegments[0].x+=1;  // move right 
    if (direction==3) snakeSegments[0].y-=1;  // move up


    // check if head of the snake collided with fruit 
    if ((snakeSegments[0].x==fruit.x) && (snakeSegments[0].y==fruit.y)) 
     {num++; // increase the lenght of the snake 
    fruit.x=rand()%GRID_WIDTH; // generate random fruit position  
    fruit.y=rand()%GRID_HEIGHT;}

    // wrap snake around ths screen edges
    if (snakeSegments[0].x>GRID_WIDTH) snakeSegments[0].x=0;  
    if (snakeSegments[0].x<0) snakeSegments[0].x=GRID_WIDTH;
    if (snakeSegments[0].y>GRID_HEIGHT) snakeSegments[0].y=0;  
    if (snakeSegments[0].y<0) snakeSegments[0].y=GRID_HEIGHT;
 
    // check if the snake head collides with its body
    for (int i=1;i<num;i++)
     if (snakeSegments[0].x==snakeSegments[i].x && snakeSegments[0].y==snakeSegments[i].y)  num=i;
 }

int snake()
{  
    srand(time(0)); // random seed

    // create sfml window 
    RenderWindow window(VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Snake Game!");

    // load textures for snake and fruit 
    Texture snakeTexture,fruitTexture;
    snakeTexture.loadFromFile("images/snake/white.png");
    fruitTexture.loadFromFile("images/snake/red.png");

    // create sprites for them 
    Sprite sprite1(snakeTexture);
    Sprite sprite2(fruitTexture);

    Clock clock;
    float timer=0, delay=0.1;

    fruit.x=10; // set position for the fruit 
    fruit.y=10; 
    
    while (window.isOpen())
    {
        float time = clock.getElapsedTime().asSeconds();
        clock.restart();
        timer+=time; 

        Event e;
        while (window.pollEvent(e))
        {
            if (e.type == Event::Closed)      
                window.close();
        }

        if (Keyboard::isKeyPressed(Keyboard::Left)) direction=1;   
        if (Keyboard::isKeyPressed(Keyboard::Right)) direction=2;    
        if (Keyboard::isKeyPressed(Keyboard::Up)) direction=3;
        if (Keyboard::isKeyPressed(Keyboard::Down)) direction=0;

        if (timer>delay) {timer=0; Tick();}

   ////// draw  ///////
    window.clear();

    for (int i=0; i<GRID_WIDTH; i++) 
      for (int j=0; j<GRID_HEIGHT; j++) 
        { sprite1.setPosition(i*CELL_SIZE, j*CELL_SIZE);  window.draw(sprite1); }

    for (int i=0;i<num;i++)
        { sprite2.setPosition(snakeSegments[i].x*CELL_SIZE, snakeSegments[i].y*CELL_SIZE);  window.draw(sprite2); }
   
    sprite2.setPosition(fruit.x*CELL_SIZE, fruit.y*CELL_SIZE);  window.draw(sprite2);    

    window.display();
    }

    return 0;
}
