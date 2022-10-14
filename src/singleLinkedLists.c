#include "../headers/sys_headers.h"
#include "../headers/singleLinkedLists.h"

// list_t functions

list_t *destroy(list_t *head)
{
    assert(head != NULL);

    list_t *temp;

    while (head != NULL)
    {
        temp = head;
        head = head->next;
        free(temp);
    }

    return head;
}

list_t *createNode(char *data)
{
    list_t *item = malloc(sizeof(list_t));

    assert(item != NULL);

    strcpy(item->str, data);
    item->next = NULL;
    return item;
}

void printList(list_t *head)
{
    list_t *walker = head;

    assert(walker != NULL);

    while (walker != NULL)
    {
        printf("%p -> %s\n", walker, walker->str);
        walker = walker->next;
    }
}

list_t *push(list_t *head, char *data)
{
    assert(head != NULL);

    list_t *walker = head;

    while (walker->next != NULL)
    {
        walker = walker->next;
    }

    walker->next = createNode(data);
    return head;
}
