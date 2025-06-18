#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <conio.h>  

#define WIDTH 20
#define HEIGHT 20

// Game variables
int snakeX[100], snakeY[100]; // Snake body coordinates
int snakeLength;
int foodX, foodY;
int score;
int direction; // 1=up, 2=down, 3=left, 4=right
bool gameOver;

// Function prototypes
void Setup();
void Draw();
void Input();
void Logic();
void ShowStartScreen();
void ShowGameOverScreen();
void PlaceFood();

int main() {
    ShowStartScreen();
    
    Setup();
    
    // Main game loop
    while (!gameOver) {
        Draw();
        Input();
        Logic();
        
        // Slow down the game (adjust this value to change speed)
        for (int i = 0; i < 10000; i++) {
            for (int j = 0; j < 1000; j++) {}
        }
    }
    
    ShowGameOverScreen();
    
    return 0;
}

// Initialize game state
void Setup() {
    gameOver = false;
    direction = 4; // Start moving right
    snakeLength = 1;
    
    // Initial snake position (center of the screen)
    snakeX[0] = WIDTH / 2;
    snakeY[0] = HEIGHT / 2;
    
    score = 0;
    
    // Place first food
    PlaceFood();
}

// Draw the game board
void Draw() {
    system("cls"); // Clear the console
    
    // Draw top border
    for (int i = 0; i < WIDTH + 2; i++)
        printf("#");
    printf("\n");
    
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            // Draw left border
            if (x == 0)
                printf("#");
            
            // Draw snake head
            if (x == snakeX[0] && y == snakeY[0])
                printf("O");
            // Draw snake body
            else {
                bool isBodyPart = false;
                for (int k = 1; k < snakeLength; k++) {
                    if (snakeX[k] == x && snakeY[k] == y) {
                        printf("o");
                        isBodyPart = true;
                        break;
                    }
                }
                
                // Draw food
                if (!isBodyPart) {
                    if (x == foodX && y == foodY)
                        printf("F");
                    else
                        printf(" ");
                }
            }
            
            // Draw right border
            if (x == WIDTH - 1)
                printf("#");
        }
        printf("\n");
    }
    
    // Draw bottom border
    for (int i = 0; i < WIDTH + 2; i++)
        printf("#");
    printf("\n");
    
    // Display score
    printf("Score: %d\n", score);
    printf("Press 'x' to quit\n");
}

// Handle user input
void Input() {
    if (_kbhit()) {
        switch (_getch()) {
            case 'w':
                if (direction != 2) // Prevent moving directly opposite
                    direction = 1;
                break;
            case 's':
                if (direction != 1)
                    direction = 2;
                break;
            case 'a':
                if (direction != 4)
                    direction = 3;
                break;
            case 'd':
                if (direction != 3)
                    direction = 4;
                break;
            case 'x':
                gameOver = true;
                break;
            case 72: // Up arrow
                if (direction != 2)
                    direction = 1;
                break;
            case 80: // Down arrow
                if (direction != 1)
                    direction = 2;
                break;
            case 75: // Left arrow
                if (direction != 4)
                    direction = 3;
                break;
            case 77: // Right arrow
                if (direction != 3)
                    direction = 4;
                break;
        }
    }
}

// Update game state
void Logic() {
    // Move snake body (start from the tail)
    for (int i = snakeLength - 1; i > 0; i--) {
        snakeX[i] = snakeX[i - 1];
        snakeY[i] = snakeY[i - 1];
    }
    
    // Move snake head based on direction
    switch (direction) {
        case 1: // Up
            snakeY[0]--;
            break;
        case 2: // Down
            snakeY[0]++;
            break;
        case 3: // Left
            snakeX[0]--;
            break;
        case 4: // Right
            snakeX[0]++;
            break;
    }
    
    // Check for wall collision
    if (snakeX[0] < 0 || snakeX[0] >= WIDTH || snakeY[0] < 0 || snakeY[0] >= HEIGHT)
        gameOver = true;
    
    // Check for self collision
    for (int i = 1; i < snakeLength; i++) {
        if (snakeX[0] == snakeX[i] && snakeY[0] == snakeY[i])
            gameOver = true;
    }
    
    // Check for food collision
    if (snakeX[0] == foodX && snakeY[0] == foodY) {
        score += 10;
        PlaceFood();
        snakeLength++;
    }
}

// Place food at random location
void PlaceFood() {
    bool validPosition = false;
    
    while (!validPosition) {
        // Generate random position
        foodX = rand() % WIDTH;
        foodY = rand() % HEIGHT;
        
        // Check if position is not on snake
        validPosition = true;
        for (int i = 0; i < snakeLength; i++) {
            if (snakeX[i] == foodX && snakeY[i] == foodY) {
                validPosition = false;
                break;
            }
        }
    }
}

// Display start screen
void ShowStartScreen() {
    system("cls");
    printf("================================\n");
    printf("          SNAKE GAME\n");
    printf("================================\n\n");
    printf("Controls:\n");
    printf("W or Up Arrow    - Move Up\n");
    printf("S or Down Arrow  - Move Down\n");
    printf("A or Left Arrow  - Move Left\n");
    printf("D or Right Arrow - Move Right\n");
    printf("X                - Quit Game\n\n");
    printf("Press any key to start...");
    _getch(); // Wait for key press
}

// Display game over screen
void ShowGameOverScreen() {
    system("cls");
    printf("================================\n");
    printf("          GAME OVER\n");
    printf("================================\n\n");
    printf("Final Score: %d\n\n", score);
    printf("Press any key to exit...");
    _getch(); // Wait for key press
}
