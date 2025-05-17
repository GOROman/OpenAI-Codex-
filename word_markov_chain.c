#include <stdio.h>
#include <stdlib.h>
#include <time.h>

static const char *group0[] = {"わたし", "あなた", "おまえ"};
static const char *group1[] = {"は", "の"};
static const char *group2[] = {"りんご", "みかん", "いちご", "スイカ", "メロン", "さくらんぼ", "かき", "なし", "もも"};
static const char *group3[] = {"が", "を"};
static const char *group4[] = {"好きです", "嫌いです", "食べます", "捨てます", "腐ってます"};

#define SIZE(arr) (sizeof(arr)/sizeof((arr)[0]))

int main(void) {
    const char **groups[] = {group0, group1, group2, group3, group4};
    const size_t sizes[] = {SIZE(group0), SIZE(group1), SIZE(group2), SIZE(group3), SIZE(group4)};
    const int group_count = 5;

    srand((unsigned)time(NULL));

    for (int g = 0; g < group_count; ++g) {
        size_t n = sizes[g];
        const char **words = groups[g];
        int index = rand() % n;
        printf("%s", words[index]);
    }
    putchar('\n');
    return 0;
}
