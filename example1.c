#include<stdio.h>
#include<stdlib.h>
#include <string.h>

struct node {
    int id;
    char name[30];
    struct node *next;
};

struct node *first = NULL;


void addNodeToPosition(struct node *prevNode, int id, char name[30]);
struct node *findNodeAtPosition(int position);
struct node *findNodeById(int id);
void insertAfterId(int id, char name[30]);
void deleteNodeAfterId(int id);

/*
 * Add a new node at a given position in the linked list
 * @param prevNode The previous (to given position) node in the linked list
 * @param id The id of the new node
 * @param name The name of the new node
 * @return void
 * */
void addNodeToPosition(struct node *prevNode, int id, char name[30]) {
    if (prevNode == first) {
        struct node *newNode = (struct node *) malloc(sizeof(struct node));
        newNode->id = id;
        strcpy(newNode->name, name);
        newNode->next = first;
        first = newNode;
        return;
    }
    //Check if the previous node is NULL and if the next node is NULL
    if (prevNode->next == NULL) {
        printf("The given previous node cannot be NULL");
        return;
    })
    //Allocate memory for the new node
    struct node *newNode = (struct node *) malloc(sizeof(struct node));
    //Assign the data to the new node
    newNode->id = id;
    strcpy(newNode->name, name);
    //Make the next of the new node as the next of the previous node
    newNode->next = prevNode->next;
    //Make the next of the previous node as the new node
    prevNode->next = newNode;
}

/*
 * Find a node at a given position in the linked list
 * @param position The position of the node to find
 * @return struct node* The node at the given position
 * */
struct node *findNodeAtPosition(int position) {
    struct node *temp = first;
    int i = 1;
    while (temp != NULL && i < position) {
        temp = temp->next;
        i++;
    }
    return temp;
}

/*
 * Find a node by its id in the linked list
 * @param id The id of the node to find
 * @return struct node* The node with the given id
 * */
struct node *findNodeById(int id) {
    struct node *temp = first;
    while (temp != NULL) {
        if (temp->id == id) {
            return temp;
        }
        temp = temp->next;
    }
    return NULL;
}

/*
 * Insert a new node after a given id in the linked list
 * @param id The id of the node after which the new node will be inserted
 * @param name The name of the new node
 * @return void
 * */
void insertAfterId(int id, char name[30]) {
    struct node *prevNode = findNodeById(id);
    if (prevNode == NULL) {
        printf("The given previous node cannot be NULL");
        return;
    }
    struct node *newNode = (struct node *) malloc(sizeof(struct node));
    strcpy(newNode->name, name);
    newNode->next = prevNode->next;
    prevNode->next = newNode;
}

//Delete a node at a given position
void deleteNodeAtPosition(int position) {
    struct node *temp = first;
    if (position == 0) {
        first = temp->next;
        free(temp);
        return;
    }
    for (int i = 0; temp != NULL && i < position - 1; i++) {
        temp = temp->next;
    }
    if (temp == NULL || temp->next == NULL) {
        return; //If the position is greater than the number of nodes
    }
    struct node *next = temp->next->next;
    free(temp->next);
    temp->next = next;
}

/*
 * Delete a node after a given id
 * @param id The id of the node after which the node will be deleted
 * @return void
 * */
void deleteNodeAfterId(int id) {
    struct node *prevNode = findNodeById(id);
    if (prevNode == NULL) {
        printf("The given previous node cannot be NULL");
        return;
    }
    struct node *temp = prevNode->next;
    prevNode->next = temp->next;
    free(temp);
}

/*
 * Add a new node to the linked list
 * @return void
 * */
void addNode() {
    struct node *new;
    new = malloc(sizeof(struct node));
    printf("Write your id: ");
    scanf("%d", &new->id);
    fflush(stdin);
    printf("Write your name: ");
    fgets(new->name, sizeof(new->name), stdin);
    new->name[strcspn(new->name, "\n")] = '\0';
    if (first == NULL) {
        new->next = NULL;
        first = new;
    } else {
        struct node *temp = first;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = new;
        new->next = NULL;
    }
}

/*
 * Print the linked list
 * @return void
 * */
void print() {
    //printf("║     Id    ║    Name  ╚╝   ║\n");
    int i = 1;
    struct node *temp = first;
    printf("╔═══════════╦═══════════╦══════════════════════════════╗\n");
    printf("║ Node(pos) ║    Id     ║           Name               ║\n");
    printf("╠═══════════╬═══════════╬══════════════════════════════╣\n");

    while (temp != NULL) {
        printf("║    %d      ║    %d      ║%30s║\n", i, temp->id, temp->name);
        temp = temp->next;
        i++;
    }
    printf("╚═══════════╩═══════════╩══════════════════════════════╝\n");
}

/*
 * Clear the screen
 * @return void
 * */
void clearScreen() {
#ifdef WINDOWS
    system("cls");
#else
    system("clear");
#endif
}

/*
 * Delay the program
 * @return void
 * */
void delay() {
#ifdef WINDOWS
    system("timeout 3 > nul");
#else
    system("sleep 3");
#endif
}


int main() {
    addNode();
    addNode();
    addNode();
    addNode();
    addNode();

    //Menu for the user
    int option;
    do {
        printf("1. Print the linked list\n");
        printf("2. Add a new node to a position\n");
        printf("3. Add a new node after a given id\n");
        printf("4. Delete a node in a given position\n");
        printf("5. Delete a node after a given id\n");
        printf("6. Exit\n");
        printf("Choose an option: ");
        scanf("%d", &option);
        switch (option) {
            case 1:
                clearScreen();
                print();
                fgetc(stdin);
                printf("Press enter to continue...");
                fgetc(stdin);
                clearScreen();
                break;
            case 2:
                print();
                int position;

                printf("Choose a position to add the new node: ");
                scanf("%d", &position);
                struct node *prevNode = findNodeAtPosition(position - 1);
                printf("prevNode: %d\n", prevNode->id);
                printf("Prev Node name %s\n", prevNode->name);
                if (prevNode == NULL) {
                    printf("The given previous node cannot be NULL");
                    break;
                }
                int id;
                char name[30];
                printf("Write the id of the new node: ");
                scanf("%d", &id);
                getc(stdin);
                printf("Write the name of the new node: ");
                fgets(name, sizeof(name), stdin);
                name[strcspn(name, "\n")] = '\0';

                addNodeToPosition(prevNode, id, name);
                printf("Press enter to continue...");
                fgetc(stdin);
                clearScreen();
                break;
            case 3:
                print();
                int referenceId;
                printf("Choose the id of the node after which you want to add a new node: ");
                scanf("%d", &referenceId);
                int idToAdd;
                printf("Write the id of the new node: ");
                scanf("%d", &idToAdd);
                printf("Write the name of the new node: ");
                char nameToAdd[30];
                getc(stdin);
                fgets(nameToAdd, sizeof(nameToAdd), stdin);
                nameToAdd[strcspn(nameToAdd, "\n")] = '\0';
                insertAfterId(referenceId, nameToAdd);
                printf("Press enter to continue...");
                fgetc(stdin);
                clearScreen();
                break;
            case 4:
                print();
                int positionToDelete;
                printf("Choose a position to delete the node: ");
                scanf("%d", &positionToDelete);
                if (positionToDelete < 1) {
                    printf("Invalid position\n");
                    break;
                }
                deleteNodeAtPosition(positionToDelete - 1);
                printf("Press enter to continue...");
                fgetc(stdin);
                clearScreen();
                break;
            case 5:
                print();
                int idToDelete;
                printf("Choose the id of the node after which you want to delete a node: ");
                scanf("%d", &idToDelete);
                deleteNodeAfterId(idToDelete);
                printf("Press enter to continue...");
                fgetc(stdin);
                break;
            case 6:
                printf("Goodbye :3\n");
                delay();
                return 1;
            default:
                printf("Invalid option\n");
                delay();
                clearScreen();
                break;
        }
    } while (option != 3);
    return 0;
}
