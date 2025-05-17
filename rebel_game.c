#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

/*
 * Rebel School Adventure
 * A simple text-based game with a mischievous vibe.
 * Break windows, dodge the teachers, and see how long you last.
 */

#define MAX_NAME_LEN 32
#define MAX_INPUT_LEN 16

typedef struct {
    char name[MAX_NAME_LEN];
    int stamina;     /* Energy to perform actions */
    int chaos;       /* Level of trouble caused */
    int caught;      /* Flag if player is caught */
} GameState;

/* Display player's current status */
static void show_status(const GameState *g) {
    printf("\n-- %s's Status --\n", g->name);
    printf("Stamina: %d\n", g->stamina);
    printf("Chaos:   %d\n", g->chaos);
}

/* Display the action menu */
static void show_menu(void) {
    puts("\nChoose your next mischief:");
    puts("1. Break a classroom window");
    puts("2. Spray graffiti in the hallway");
    puts("3. Sneak past the teacher");
    puts("4. Hide and regain stamina");
    puts("0. Give up and go home");
    printf("> ");
}

/* Random chance helper */
static int percent_chance(int percent) {
    return (rand() % 100) < percent;
}

/* Handle the player's chosen action */
static void do_action(int choice, GameState *g) {
    switch (choice) {
    case 1:
        if (g->stamina < 5) {
            puts("Too tired to throw a rock.");
            break;
        }
        puts("You hurl a rock! Crash!!");
        g->stamina -= 5;
        g->chaos += 10;
        if (percent_chance(20)) {
            puts("A teacher heard the noise! You're caught!");
            g->caught = 1;
        }
        break;
    case 2:
        if (g->stamina < 3) {
            puts("No energy to spray paint.");
            break;
        }
        puts("You tag the wall with rebellious art.");
        g->stamina -= 3;
        g->chaos += 7;
        if (percent_chance(15)) {
            puts("A hall monitor spots you! You're busted!");
            g->caught = 1;
        }
        break;
    case 3:
        puts("You attempt a stealthy move...");
        if (percent_chance(70)) {
            puts("Success! Nobody saw you.");
        } else {
            puts("Oops! A teacher blocks your path!");
            g->caught = 1;
        }
        break;
    case 4:
        puts("You take a breather behind the gym.");
        g->stamina += 4;
        if (g->stamina > 20)
            g->stamina = 20;
        break;
    case 0:
        puts("You decide to head home. Maybe tomorrow.");
        g->caught = 1; /* End the game */
        break;
    default:
        puts("Invalid choice.");
        break;
    }
}

int main(void) {
    GameState g = {"Rebel", 20, 0, 0};
    char input[MAX_INPUT_LEN];

    srand((unsigned)time(NULL));

    printf("Enter your name: ");
    if (fgets(g.name, sizeof(g.name), stdin)) {
        g.name[strcspn(g.name, "\n")] = '\0';
    }
    if (g.name[0] == '\0')
        strcpy(g.name, "Rebel");

    puts("Welcome to the Night School Adventure!");

    while (!g.caught && g.chaos < 100) {
        show_status(&g);
        show_menu();
        if (!fgets(input, sizeof(input), stdin))
            break;
        int choice = atoi(input);
        do_action(choice, &g);
        if (g.stamina <= 0) {
            puts("You're exhausted and collapse. Game over!");
            g.caught = 1;
        }
    }

    if (g.chaos >= 100 && !g.caught) {
        puts("You caused enough chaos for one night. Time to bail!");
    }

    puts("Thanks for playing!");
    return 0;
}

