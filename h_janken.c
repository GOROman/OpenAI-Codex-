#include <stdio.h>
#include <stdlib.h>
#include <time.h>

enum Hand { ROCK = 1, PAPER, SCISSORS };

int main(void) {
    int player;
    int npc;

    srand((unsigned)time(NULL));

    printf("=== Hなじゃんけん ===\n");
    printf("1: グー\n");
    printf("2: パー\n");
    printf("3: チョキ\n");
    printf("好きなのを選んでくれ。常識なんてクソ喰らえだ！\n");

    if (scanf("%d", &player) != 1 || player < ROCK || player > SCISSORS) {
        printf("おいおい、ふざけすぎだぜ。\n");
        return 1;
    }

    npc = (rand() % 3) + 1;
    const char *names[] = {"", "グー", "パー", "チョキ"};

    printf("お前: %s\n", names[player]);
    printf("相手: %s\n", names[npc]);

    if (player == npc) {
        printf("あいこだ。裸一貫出直してこい！\n");
    } else if ((player == ROCK && npc == SCISSORS) ||
               (player == PAPER && npc == ROCK) ||
               (player == SCISSORS && npc == PAPER)) {
        printf("お前の勝ちだ。やるじゃねえか！\n");
    } else {
        printf("お前の負けだ。もっとHに攻めろよ！\n");
    }
    return 0;
}
