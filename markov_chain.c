#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* Simple Markov chain text generator
 * Demonstrates Shannon's model from "A Mathematical Theory of Communication".
 * States are characters, transitions define the probability of the next state.
 */

#define STATES 4

static const char symbols[STATES] = {'A', 'B', 'C', 'D'};

/* Transition probability matrix.
 * Each row sums to 1.0. For simplicity we use double precision.
 */
static const double transition[STATES][STATES] = {
    /* From A */ {0.1, 0.6, 0.2, 0.1},
    /* From B */ {0.3, 0.1, 0.4, 0.2},
    /* From C */ {0.25, 0.25, 0.25, 0.25},
    /* From D */ {0.5, 0.2, 0.2, 0.1}
};

/* Randomly select the next state based on probabilities */
static int next_state(int current) {
    double r = (double)rand() / RAND_MAX;
    double cumulative = 0.0;
    for (int i = 0; i < STATES; ++i) {
        cumulative += transition[current][i];
        if (r < cumulative)
            return i;
    }
    return STATES - 1; /* Fallback */
}

int main(void) {
    srand((unsigned)time(NULL));

    int current = 0; /* Start from state 'A' */
    const int steps = 20; /* Length of generated sequence */

    for (int i = 0; i < steps; ++i) {
        putchar(symbols[current]);
        current = next_state(current);
    }
    putchar('\n');

    return 0;
}
