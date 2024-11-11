#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define WIDTH 100      // Grid width
#define HEIGHT 100      // Grid height
#define INITIAL_POP 100 // Initial number of individuals
#define MAX_STEPS 1000  // Maximum steps in the simulation
#define SURVIVAL_PROB 0.8 // Probability of survival for each individual
#define REPRODUCTION_PROB 0.1 // Probability of reproduction

// Grid to represent the ecosystem (0 = empty, 1 = individual present)
int grid[HEIGHT][WIDTH];

// Function to initialize the grid with some individuals
void initialize_grid(int initial_population) {
    int count = 0;
    while (count < initial_population) {
        int x = rand() % WIDTH;
        int y = rand() % HEIGHT;
        if (grid[y][x] == 0) {
            grid[y][x] = 1;
            count++;
        }
    }
}

// Function to display the current state of the grid
void display_grid() {
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            printf("%c ", grid[y][x] == 0 ? '.' : '#');
        }
        printf("\n");
    }
}

// Function to perform one step of the simulation
void simulate_step() {
    int new_grid[HEIGHT][WIDTH] = {0}; // Create a temporary grid for the next step

    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            if (grid[y][x] == 1) {
                // Check survival: if the individual survives (with probability)
                if ((rand() % 100) < (SURVIVAL_PROB * 100)) {
                    new_grid[y][x] = 1;
                }

                // Check reproduction: if reproduction happens (with probability)
                if ((rand() % 100) < (REPRODUCTION_PROB * 100)) {
                    // Try to reproduce in adjacent cells
                    for (int dy = -1; dy <= 1; dy++) {
                        for (int dx = -1; dx <= 1; dx++) {
                            if (y + dy >= 0 && y + dy < HEIGHT && x + dx >= 0 && x + dx < WIDTH && new_grid[y + dy][x + dx] == 0) {
                                new_grid[y + dy][x + dx] = 1; // Place a new individual in the empty space
                                break;
                            }
                        }
                    }
                }
            }
        }
    }

    // Copy the new grid back to the original grid
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            grid[y][x] = new_grid[y][x];
        }
    }
}

int main() {
    srand(time(0)); // Seed the random number generator

    // Initialize the grid with some individuals
    initialize_grid(INITIAL_POP);

    // Simulate for a number of steps
    int step;
    for (step = 0; step < MAX_STEPS; step++) {

        simulate_step();

    }

    printf("Computed %d steps\n", step + 1);

    return 0;
}
