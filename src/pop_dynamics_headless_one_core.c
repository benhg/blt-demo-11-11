#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <stdint.h>
#include <signal.h>
#include <sys/time.h> 

#define WIDTH 100      // Grid width
#define HEIGHT 100      // Grid height
#define INITIAL_POP 100 // Initial number of individuals
#define MAX_STEPS 1000  // Maximum steps in the simulation
#define SURVIVAL_PROB 0.8 // Probability of survival for each individual
#define REPRODUCTION_PROB 0.1 // Probability of reproduction

// Step count
uint64_t step;

// Signal handling
struct sigaction sigact;

// Grid to represent the ecosystem (0 = empty, 1 = individual present)
int grid[HEIGHT][WIDTH];

// Timer
struct timeval t1, t2;
double elapsedTime;

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

/**
 * Signal handlers
 */
static void signal_handler(int sig){
    if (sig == SIGINT){ printf("Caught signal for Ctrl+C\n");}


    // stop timer
    gettimeofday(&t2, NULL);

    

    printf("Total number of steps executed was %llu\n", step);

    // compute and print the elapsed time in millisec
    elapsedTime = (t2.tv_sec - t1.tv_sec) * 1000.0;      // sec to ms
    elapsedTime += (t2.tv_usec - t1.tv_usec) / 1000.0;   // us to ms
    printf("%llu steps in %f ms. is %f steps / ms\n", step, elapsedTime , (step/elapsedTime));

    exit(0);
}

void init_signals(void){
    sigact.sa_handler = signal_handler;
    sigemptyset(&sigact.sa_mask);
    sigact.sa_flags = 0;
    sigaction(SIGINT, &sigact, (struct sigaction *)NULL);
}

int main() {

    // start timer
    gettimeofday(&t1, NULL);


    srand(time(0)); // Seed the random number generator
    init_signals();

    // Initialize the grid with some individuals
    initialize_grid(INITIAL_POP);

    // Simulate for a number of steps
    // step is global
    for (step = 0; ;step++) {

        simulate_step();

    }

    printf("Computed %llu steps\n", step + 1);

    return 0;
}
