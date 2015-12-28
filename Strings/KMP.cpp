#include<stdio.h>

const int max_n = 100000+5;
const int max_p = 100+5;
const int R = 26;
int P;
char txt[max_n];
char pattern[max_p];
int dfa[max_p][R];

inline int map_char(char c)
{
    return c - 'A';
}

void build_dfa()
{
    for(int i=0; i<R; ++i) dfa[0][i] = 0;
    dfa[0][map_char(pattern[0])] = 1;
    int X = 0;
    for(P=1; pattern[P] != '\0'; ++P)
    {
        for(int i=0; i<R; ++i) dfa[P][i] = dfa[X][i];
        dfa[P][map_char(pattern[P])] = P+1;
        X = dfa[X][map_char(pattern[P])];
    }
}

int kmp()
{
    build_dfa();
    int i, state = 0;
    for(i=0; txt[i] != '\0' && state < P; ++i) state = dfa[state][map_char(txt[i])];
    if(state == P) return i - P;
    return -1;
}

int main()
{
    txt[0] = 'A';
    txt[1] = 'B';
    txt[2] = 'C';
    txt[3] = 'D';
    txt[4] = 'A';
    pattern[0] = 'C';
    pattern[1] = 'D';
    pattern[2] = 'A';
    printf("%d\n", kmp());
    return 0;
}
