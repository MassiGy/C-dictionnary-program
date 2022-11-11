/*
@Author: MassiGy
@Description: This C program will load a text file containing all the english words to a trie data structure
and then expose some APIs for search and spelling checkers.
*/

#include "../headers/main.h"

int main(void)
{

    node_t *root_list = createTrie();
    initTrie(root_list);

    // read from the words.txt file
    FILE *_file = fopen("../ressources/words.txt", "rt");
    assert(_file != NULL);

    char buffer[34];

    while (!feof(_file))
    {
        fgets(buffer, 32, _file);
        insertStr(root_list, buffer);
    }

    fclose(_file);

    printf("Please enter an english words to check its spelling:\t");
    scanf("%32s", buffer);
    printf("\n");

    if (searchVal(root_list, buffer))
    {
        printf("%s\n", "correctly spelled.");
    }
    else
    {
        fuzzySearch(root_list, buffer);
    }

    destroy_trie(root_list);

    return 0;
}
