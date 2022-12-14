#include "./sys_headers.h"

#define FILE_LINE_COUNT 10000
#define WORD_PER_LINE 1
#define ALPHABET_LETTER_COUNT 26
#define ASCII_ORD_OFFSET 97

struct node
{
    /* data */
    char val;
    struct node *store;
};

typedef struct node node_t;

// TRIES FUNTIONS
void initTrie(node_t *root_list);
node_t *createTrie();
void printTrie(node_t *root_list);
void insertStr(node_t *root_list, char *data);
bool searchVal(node_t *root_list, char *query);
void fuzzySearch(node_t *root_list, char *falsy_query);
bool is_leaf(node_t *root_list);
void destroy_trie(node_t *root_list);