
struct list
{
    char *str;
    struct list *next;
};

typedef struct list list_t;

/*LIST OPERATIONS*/
void printList(list_t *head);
list_t *createNode(char *data);
list_t *push(list_t *head, char *data);
list_t *destroy(list_t *head);