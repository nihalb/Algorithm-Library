#include<stdio.h>
#include<iostream>
#include<string>

using namespace std;

struct trie
{
    trie()
    {
        words = 0;
        prefixes = 0;
        for(int i=0; i<26; ++i) children[i] = NULL;
    }
    int words;
    int prefixes;
    trie* children[26];
};

inline int map_char(char c)
{
    return c - 'a';
}

void add_word(trie* t, string w)
{
    t->prefixes++;
    trie* curr = t;
    for(string::iterator it = w.begin(); it != w.end(); ++it)
    {
        int idx = map_char(*it);
        if(!curr->children[idx]) curr->children[idx] = new trie();
        curr = curr->children[idx];
        curr->prefixes++;
    }
    curr->words++;
}

int count_prefixes(trie* t, string w, bool full_word)
{
    trie* curr = t;
    for(string::iterator it = w.begin(); it != w.end(); ++it)
    {
        curr = curr->children[map_char(*it)];
        if(!curr) return 0;
    }
    return full_word ? curr->words : curr->prefixes;
}

int main()
{
    trie t;
    add_word(&t, "adam");
    add_word(&t, "am");
    add_word(&t, "ada");
    printf("%d\n", count_prefixes(&t, "", false));
    printf("%d\n", count_prefixes(&t, "ad", false));
    printf("%d\n", count_prefixes(&t, "ad", true));
    printf("%d\n", count_prefixes(&t, "ada", false));
    printf("%d\n", count_prefixes(&t, "ada", true));
    return 0;
}
