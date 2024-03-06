#include<stdio.h>
#include<stdlib.h>
#include <string.h>

struct node {
    int id;
    char name[30];
    struct node *next;
};

typedef struct {
    int id;
    char name[30];
} FileNode;

void addNodeToPosition(struct node **first, struct node *prevNode, int id, char name[30]);
struct node *findNodeAtPosition(struct node **first, int position);
struct node *findNodeById(struct node **first, int id);
void insertAfterId(struct node **first, int id, char name[30]);
void deleteNodeAfterId(struct node **first, int id);
void deleteNodeAtPosition(struct node **first, int position);
int checkIfIdExists(struct node **first, int id);
void saveToFile(struct node **first);
struct node *loadFromFile(struct node **first);
void deleteList(struct node **first);
void swapData(struct node *sourceNode, struct node *destinationNode);
void swapNode(struct node **first, struct node *sourceNode, struct node *destinationNode);
void print(struct node **first);
void clearScreen();
void delay();
int contadorN(struct node **first);

int main() {
    struct node *first = NULL;
    first = loadFromFile(&first);

    char *options[] = {
            "Print the whole list",
            "Add a new node to a position",
            "Add a new node after a given id",
            "Delete a node by position",
            "Delete a node after a given id",
            "Save list to file",
            "Swap data between two nodes",
            "Swap two nodes (adresses)",
            "Delete the whole list",
            "Invert list"
            "Exit"
        };
        int numOptions = sizeof(options) / sizeof(options[0]);

    //Menu for the user
    int option;
    do {
        clearScreen();
        printf("\tWelcome to the linked list program\n\n");
        for (int i = 0; i < numOptions; i++) {
            printf("%d. %s\n", i + 1, options[i]);
        }
        printf("\nChoose an option: ");
        scanf("%d", &option);
        switch (option) {
            case 1:
                clearScreen();
                if (NULL == first) {
                    printf("The list is empty\n");
                    delay();
                    break;
                }
                printf("\tHere's the whole list\n\n");
                print(&first);
                fgetc(stdin);
                printf("Press enter to continue...");
                fgetc(stdin);
                clearScreen();
                break;
            case 2:
                clearScreen();
                if (NULL != first) {
                    printf("\tYou're about to add a new node to a position\n");
                    print(&first);
                    int position;
                    printf("Choose a position to add the new node: ");
                    scanf("%d", &position);
                    struct node *prevNode = findNodeAtPosition(&first, position - 1);
                    if (NULL == prevNode) {
                        printf("The given previous node cannot be NULL");
                        break;
                    }
                    int id;
                    char name[30];
                    printf("Write the id of the new node: ");
                    scanf("%d", &id);
                    getc(stdin);
                    if (checkIfIdExists(&first, id)) {
                        printf("The given id already exists\n");
                        clearScreen();
                        break;
                    }
                    printf("Write the name of the new node: ");
                    fgets(name, sizeof(name), stdin);
                    name[strcspn(name, "\n")] = '\0';
                    fflush(stdin);

                    addNodeToPosition(&first, prevNode, id, name);
                    break;
                }
                printf("Write the id of the new node: ");
                int id;
                scanf("%d", &id);
                printf("Write the name of the new node: ");
                char name[30];
                getc(stdin);
                fgets(name, sizeof(name), stdin);
                name[strcspn(name, "\n")] = '\0';
                addNodeToPosition(&first, first, id, name);

                printf("Press enter to continue...");
                fgetc(stdin);
                clearScreen();
                break;
            case 3:
                clearScreen();
                printf("\tYou're about to add a new node after a given id\n");
                print(&first);
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
                insertAfterId(&first, referenceId, nameToAdd);
                printf("Press enter to continue...");
                fgetc(stdin);
                clearScreen();
                break;
            case 4:
                clearScreen();
                printf("\t\x1b[31mYou're about to delete a node in a given position\x1b[0m\n");
                print(&first);
                int positionToDelete;
                printf("Choose a position to delete the node: ");
                scanf("%d", &positionToDelete);
                if (positionToDelete < 1) {
                    printf("Invalid position\n");
                    break;
                }
                deleteNodeAtPosition(&first, positionToDelete - 1);
                printf("Press enter to continue...");
                fgetc(stdin);
                clearScreen();
                break;
            case 5:
                clearScreen();
                printf("\t\x1b[31mYou're about to delete a node after a given id\x1b[0m\n");
                print(&first);
                int idToDelete;
                printf("Choose the id of the node after which you want to delete a node: ");
                scanf("%d", &idToDelete);
                deleteNodeAfterId(&first, idToDelete);
                printf("Press enter to continue...");
                fgetc(stdin);
                break;
            case 6:
                clearScreen();
                saveToFile(&first);
                printf("The list has been saved to the file\n");
                delay();
                clearScreen();
                break;
            case 7:
                clearScreen();
                printf("\t\x1b[31mYou're about to swap data between two nodes\x1b[0m\n");
                print(&first);
                int sourceId;
                printf("Choose the id of the source node: ");
                scanf("%d", &sourceId);
                int destinationId;
                printf("Choose the id of the destination node: ");
                scanf("%d", &destinationId);
                struct node *sourceNode = findNodeById(&first, sourceId);
                struct node *destinationNode = findNodeById(&first, destinationId);
                if (sourceNode == NULL || destinationNode == NULL) {
                    printf("Invalid source or destination node\n");
                    break;
                }
                swapData(sourceNode, destinationNode);
                printf("Press enter to continue...");
                fgetc(stdin);
                clearScreen();
                break;
            case 8:
                clearScreen();
                printf("\t\x1b[31mYou're about to swap two nodes (adresses)\x1b[0m\n");
                print(&first);
                int sourceIdSwap;
                printf("Choose the id of the source node: ");
                scanf("%d", &sourceIdSwap);
                int destinationIdSwap;
                printf("Choose the id of the destination node: ");
                scanf("%d", &destinationIdSwap);
                struct node *sourceNodeSwap = findNodeById(&first, sourceIdSwap);
                struct node *destinationNodeSwap = findNodeById(&first, destinationIdSwap);
                if (sourceNodeSwap == NULL || destinationNodeSwap == NULL) {
                    printf("Invalid source or destination node\n");
                    break;
                }
                swapNode(&first, sourceNodeSwap, destinationNodeSwap);
                printf("Press enter to continue...");
                fgetc(stdin);
                clearScreen();
                break;
            case 9:
                clearScreen();
                deleteList(&first);
                printf("The list has been deleted\n");
                delay();
                clearScreen();
                break;
            case 10:
                // Invert list using swapNode function
                clearScreen();
                int size = contadorN(&first);
                printf("SIze: %d\n", size);
                struct node *origen;
                struct node *destino;
                //Exchanging the first with last node, and after the second with the penultimate node, and so on
                for (int i = 0; i < size/2; i++){
                    origen = findNodeAtPosition(&first, i);
                    destino = findNodeAtPosition(&first, size - i);
                    printf("Origen: %s\n", origen->name);
                    printf("Destino: %s\n", destino->name);
                    swapNode(&first, origen, destino);
                }
                print(&first);
                break;
            case 11:
                clearScreen();
                printf("Goodbye\n");
                delay();
                clearScreen();
                break;
            default:
                clearScreen();
                printf("Invalid option\n");
                delay();
                clearScreen();
                break;
        }
    } while (option != numOptions);
    return 0;
}

/*
 * Delete the linked list
 * @return void
 * */
void deleteList(struct node **first) {
    struct node *current = *first;
    struct node *next;
    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }
    *first = NULL;
    free(*first);
}

/*
 * Print the linked list
 * @return void
 * */
void print(struct node **first) {
    //printf("║     Id    ║    Name  ╚╝   ║\n");
    int i = 1;
    struct node *temp = *first;
    printf("╔═══════════╦═══════════╦═══════════════════════════════╗\n");
    printf("║ Node(pos) ║    Id     ║           Name                ║\n");
    printf("╠═══════════╬═══════════╬═══════════════════════════════╣\n");

    while (temp != NULL) {
        printf("║    %d      ║     %d  \t║%26s\t║\n", i, temp->id, temp->name);
        temp = temp->next;
        i++;
    }
    printf("╚═══════════╩═══════════╩═══════════════════════════════╝\n");
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
    system("timeout 2 > nul");
#else
    system("sleep 2");
#endif
}

/*
 * Save the linked list to a file
 * @return void
 * */
void saveToFile(struct node **first) {
    int choice = 0;
    printf("¿Deseas sobreescribir el archivo?(y 1/n 0): ");
    struct node *temp = *first;
    scanf("%d", &choice);
    if (!choice) {
        FILE *file = fopen("linkedlist.dat", "rb+");
        fseek(file, 0, SEEK_END);
        while (temp != NULL) {
            FileNode *fileNode = malloc(sizeof(FileNode));
            fileNode->id = temp->id;
            strcpy(fileNode->name, temp->name);
            fwrite(fileNode, sizeof(FileNode), 1, file);
            temp = temp->next;
        }
        fclose(file);
        return;
    }
    FILE *file = fopen("linkedlist.dat", "wb");
    if (*first == NULL) {
        fclose(file);
        return;
    }
    while (temp != NULL) {
        FileNode *fileNode = malloc(sizeof(FileNode));
        fileNode->id = temp->id;
        strcpy(fileNode->name, temp->name);
        fwrite(fileNode, sizeof(FileNode), 1, file);
        temp = temp->next;
    }
    fclose(file);
}

/*
 * Load the linked list from a file
 * @return struct node* The first node of the linked list
 * */
struct node *loadFromFile(struct node **first) {
    FILE *file = fopen("linkedlist.dat", "rb");
    if (file == NULL) {
        return NULL;
    }
    fseek(file, 0, SEEK_END);
    long size = ftell(file);
    if (size == 0) {
        fclose(file);
        return NULL;
    }
    fseek(file, 0, SEEK_SET);
    FileNode fileNode;
    fread(&fileNode, sizeof(FileNode), 1, file);
    *first = malloc(sizeof(struct node));
    (*first)->id = fileNode.id;
    strcpy((*first)->name, fileNode.name);
    struct node *temp = *first;
    while (fread(&fileNode, sizeof(FileNode), 1, file)) {
        temp->next = malloc(sizeof(struct node));
        temp = temp->next;
        temp->id = fileNode.id;
        strcpy(temp->name, fileNode.name);
    }
    fclose(file);
    return *first;
}


/*
 * Add a new node at a given position in the linked list
 * @param prevNode The previous (to given position) node in the linked list
 * @param id The id of the new node
 * @param name The name of the new node
 * @return void
 * */
void addNodeToPosition(struct node **first, struct node *prevNode, int id, char name[30]) {
    if (prevNode == *first) {
        struct node *newNode = (struct node *) malloc(sizeof(struct node));
        newNode->id = id;
        strcpy(newNode->name, name);
        newNode->next = *first;
        *first = newNode; // Update the head of the linked list
        return;
    }
    //Check if the previous node is NULL and if the next node is NULL
    if (prevNode->next == NULL) {
        printf("The given previous node cannot be NULL");
        return;
    }
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
struct node *findNodeAtPosition(struct node **first, int position) {
    if (position < 0) {
        printf("Invalid position\n");
        return NULL;
    }
    struct node *temp = *first;
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
struct node *findNodeById(struct node **first, int id) {
    struct node *temp = *first;
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
void insertAfterId(struct node **first, int id, char name[30]) {
    struct node *prevNode = findNodeById(first, id);
    if (prevNode == NULL) {
        printf("The given previous node cannot be NULL");
        return;
    }
    struct node *newNode = (struct node *) malloc(sizeof(struct node));
    newNode->id = id;
    strcpy(newNode->name, name);
    newNode->next = prevNode->next;
    prevNode->next = newNode;
}

//Delete a node at a given position
void deleteNodeAtPosition(struct node **first, int position) {
    struct node *temp = *first;
    if (position == 0) {
        first = &temp->next;
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
int contadorN(struct node **first){
    int contador = 0;
    struct node *temp = *first;
    while (temp != NULL)
    {
        contador++;
        temp = temp->next;
    }
    return contador;
}

void deleteNodeAfterId(struct node **first, int id) {
    struct node *prevNode = findNodeById(first, id);
    if (prevNode == NULL) {
        printf("The given previous node cannot be NULL");
        return;
    }
    struct node *temp = prevNode->next;
    prevNode->next = temp->next;
    free(temp);
}

/*
 * Check if a given id exists in the linked list
 * @param id The id to check
 * @return int 1 if the id exists, 0 otherwise
 * */
int checkIfIdExists(struct node **first, int id) {
    struct node *temp = *first;
    while (temp != NULL) {
        if (temp->id == id) {
            return 1;
        }
        temp = temp->next;
    }
    return 0;
}

/*
 * Add a new node to the linked list
 * @return void
 * */
void addNode(struct node **first) {
    if (*first == NULL) {
        struct node *newNode = malloc(sizeof(struct node));
        printf("Write your id: ");
        scanf("%d", &newNode->id);
        fflush(stdin);
        printf("Write your name: ");
        fgets(newNode->name, sizeof(newNode->name), stdin);
        newNode->name[strcspn(newNode->name, "\n")] = '\0';
        newNode->next = NULL;
        *first = newNode;
        return;
    }
    struct node *new;
    new = malloc(sizeof(struct node));
    printf("Write your id: ");
    scanf("%d", &new->id);
    fflush(stdin);
    printf("Write your name: ");
    fgets(new->name, sizeof(new->name), stdin);
    new->name[strcspn(new->name, "\n")] = '\0';
    if (*first == NULL) {
        new->next = NULL;
        *first = new;
    } else {
        struct node *temp = *first;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = new;
        new->next = NULL;
    }
}


/**
 * Swaps the data (id and name) between two nodes in a linked list.
 *
 * @param sourceNode The source node from which the data will be swapped.
 * @param destinationNode The destination node to which the data will be swapped.
 */
void swapData(struct node *sourceNode, struct node *destinationNode) {
    int tempId = sourceNode->id;
    sourceNode->id = destinationNode->id;
    destinationNode->id = tempId;
    char tempName[30];
    strcpy(tempName, sourceNode->name);
    strcpy(sourceNode->name, destinationNode->name);
    strcpy(destinationNode->name, tempName);
}

/**
 * Swaps two nodes in a linked list.
 *
 * @param first The pointer to the pointer of the first node in the linked list.
 * @param sourceNode The node to be swapped with the destination node.
 * @param destinationNode The node to be swapped with the source node.
 */
void swapNode(struct node **first, struct node *sourceNode, struct node *destinationNode) {
    if (sourceNode == destinationNode) {
        return;
    }
    struct node *temp = *first;
    struct node *prevSourceNode = NULL;
    struct node *prevDestinationNode = NULL;
    while (temp != NULL) {
        if (temp->next == sourceNode) {
            prevSourceNode = temp;
        }
        if (temp->next == destinationNode) {
            prevDestinationNode = temp;
        }
        temp = temp->next;
    }
    if (prevSourceNode != NULL) {
        prevSourceNode->next = destinationNode;
    } else {
        *first = destinationNode;
    }
    if (prevDestinationNode != NULL) {
        prevDestinationNode->next = sourceNode;
    } else {
        *first = sourceNode;
    }
    struct node *tempNext = sourceNode->next;
    sourceNode->next = destinationNode->next;
    destinationNode->next = tempNext;
}