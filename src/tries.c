/*
@Author: MassiGy
@Description: This C program will load a text file containing all the english words to a trie data structure
and then expose some APIs for search and spelling checkers.
*/

#include "../headers/tries.h"
#include "../headers/stringManipulation.h"
#include "../headers/singleLinkedLists.h"

int main(void)
{

    node_t *root_list = createTrie();
    initTrie(root_list);

    // read from the words.txt file
    FILE *_file = fopen("./ressources/words.txt", "rt");
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

void initTrie(node_t *root_list)
{
    assert(root_list != NULL);

    for (int i = 0; i < ALPHABET_LETTER_COUNT; ++i)
    {
        // init our trie with the english alphabet
        root_list[i].val = (char)(i + ASCII_ORD_OFFSET);
    }
}

node_t *createTrie()
{
    // allocate memory for a trie
    node_t *root_list = malloc(sizeof(node_t) * ALPHABET_LETTER_COUNT);
    assert(root_list != NULL);

    for (int i = 0; i < ALPHABET_LETTER_COUNT; ++i)
    {
        // make the next pointer to null
        root_list[i].store = NULL;
    }

    // return the address
    return root_list;
}

void printTrie(node_t *root_list)
{

    if (root_list == NULL)
        return;

    int i = 0;

    while (i < ALPHABET_LETTER_COUNT)
    {
        // print each el val;
        if (root_list[i].val >= ASCII_ORD_OFFSET && root_list[i].val <= ASCII_ORD_OFFSET + ALPHABET_LETTER_COUNT)
        {
            printf("%s\n", &(root_list[i].val));
        }

        // foreach el print his store which is a trie
        printTrie(root_list[i].store);
        i++;
    }
}

void insertStr(node_t *root_list, char *data)
{
    assert(root_list != NULL);

    // find the place of the first char of the string data in the current trie
    // index = ord - offset
    int first_data_letter_index = (int)(data[0]) - ASCII_ORD_OFFSET;

    // start traversing the trie from the index all the way down inserting the data

    int data_length = strlen(data);
    node_t *traversal = &(root_list[first_data_letter_index]);

    int i = 1;
    while (i < data_length)
    {
        if (traversal->store == NULL)
        {
            // create it
            traversal->store = createTrie();
        }

        // insert the next latter on the data string
        traversal->store[(int)(data[i]) - ASCII_ORD_OFFSET].val = data[i];

        traversal = &(traversal->store[(int)(data[i]) - ASCII_ORD_OFFSET]);

        i++;
    }
}

bool searchVal(node_t *root_list, char *query)
{
    assert(root_list != NULL);

    // set the resault val;
    bool resault = true;

    // get the index of the first val on the root_list
    int first_query_letter_index = (int)(query[0]) - ASCII_ORD_OFFSET;

    if (root_list[first_query_letter_index].store == NULL)
    {
        return !resault;
    }

    // set a traversal pointer
    node_t *traversal = &(root_list[first_query_letter_index]);

    // go through the trie until we matched all the query or the query is not there;
    int query_length = strlen(query);
    int i = 1;

    while (i < query_length && resault)
    {
        if (traversal->store[(int)(query[i]) - ASCII_ORD_OFFSET].val != query[i])
        {
            resault = false;
        }

        traversal = &(traversal->store[(int)(query[i]) - ASCII_ORD_OFFSET]);

        i++;
    }

    return resault;
}

void fuzzySearch(node_t *root_list, char *falsy_query)
{
    assert(root_list != NULL);

    // the break point will turn to true when we encounter the letter that is in the query but not in our trie
    bool break_point = false;

    // walktrough the trie until we hit the break point
    int first_query_letter_index = (int)(falsy_query[0]) - ASCII_ORD_OFFSET;

    node_t *traversal = &(root_list[first_query_letter_index]);

    int counter = 1; // cuz we are already at the first letter el

    while (!break_point)
    {
        // since our non initialized value are equal to '', we can check the breakpoint by
        if (traversal->store[(int)(falsy_query[counter] - ASCII_ORD_OFFSET)].val != falsy_query[counter])
        {
            break_point = true;
        }
        else
        {
            traversal = &(traversal->store[(int)(falsy_query[counter] - ASCII_ORD_OFFSET)]);
            counter++;
        }
    }
    // save the correct part of the query;
    char truthy_query_part[counter];
    for (int j = 0; j < counter; j++)
    {
        truthy_query_part[j] = *(falsy_query + j);
    }
    truthy_query_part[counter] = '\0';

    // make a new list where we will store our fuzzy matches
    list_t *resault_list = NULL;

    // traverse the trie searching for the rest of the  falsy_query;

    char rest_falsy_query[strlen(falsy_query) - counter];

    strcpy(rest_falsy_query, (falsy_query + counter + 1));

    // traversal is pointing to the element where the breakpoint was found
    node_t *current_list = traversal->store;

    int i = 0;
    int prev_i = 0;
    char pivot_letter[1];
    char str[strlen(falsy_query) - counter];

    while (i < ALPHABET_LETTER_COUNT)
    {

        // pivot letter will walkthrough all the current list letters
        pivot_letter[0] = (char)(i + ASCII_ORD_OFFSET);

        str[0] = pivot_letter[0];

        // check if the pivot letter ++ rest_falsy_qeury is on the trie,
        //  assuming the the pivot letter is not equal to the breakpoint letter
        concat(str, pivot_letter, rest_falsy_query);

        if (pivot_letter[0] != traversal->val && searchVal(current_list, str))
        {

            if (resault_list == NULL)
            {

                resault_list = createNode(str);
            }
            else
            {
                resault_list = push(resault_list, str);
            }
        }

        i = prev_i + 1;
        prev_i++;
    }

    printf("\nPrinting possible fuzzy matches:\n");

    list_t *temp = resault_list;

    while (temp != NULL)
    {
        /* code */
        printf("\t%s%s\n", truthy_query_part, temp->str);
        temp = temp->next;
    }

    if (resault_list != NULL)
        destroy(resault_list);
}

bool is_leaf(node_t *root_list)
{
    assert(root_list != NULL);

    bool isLeaf = true;

    for (int i = 0; i < ALPHABET_LETTER_COUNT; ++i)
    {
        if (root_list[i].store != NULL)
        {
            isLeaf = false;
            break;
        }
    }
    return isLeaf;
}

void destroy_trie(node_t *root_list)
{
    // for each node of the list, free the store
    // do this up to buttom recursively until the trie is a leaf.
    if (root_list == NULL)
        return;
        
    if (is_leaf(root_list))
    {
        free(root_list);
        root_list = NULL;
        return;
    }

    for (int i = 0; i < ALPHABET_LETTER_COUNT; ++i)
    {
        destroy_trie((root_list[i].store));
    }

}


