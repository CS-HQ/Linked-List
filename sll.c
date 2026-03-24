#include <stdio.h> // provide defn for func printf, scanf
#include <stdlib.h> // provide defn for func malloc, free, exit

// Define the Node structure - Declaration
struct node {
    int data;  // part storing the data
    struct node *next; // part storing the address of next node // *next -> because next is a pointe of struct node type
};

// HELPER FUNCTION: Centralized node creation and error checking
struct node* create_node(int data) {
    struct node *newNode = (struct node *)malloc(sizeof(struct node));
    if (newNode == NULL) {
        printf("Error: Out of memory!\n");
        exit(1); 
    }
    newNode->data = data;
    newNode->next = NULL; // Initialization
    return newNode;
}

// Creation logic using the helper
void create_list(struct node **head_ref) {
    struct node *newNode, *temp; // Definition
    int choice = 1, data;

    while (choice) {
        printf("Enter data: ");
        scanf("%d", &data);
        
        newNode = create_node(data); // Using helper

        if (*head_ref == NULL) {
            *head_ref = temp = newNode;
        } else {
            temp->next = newNode;
            temp = newNode;
        }

        printf("Do you want to continue (0, 1)? ");
        scanf("%d", &choice);
    }
}

// 1. Add at Front
void add_at_front(struct node **head_ref, int data) {
    struct node *newNode = create_node(data); // Using helper
    newNode->next = *head_ref;
    *head_ref = newNode;
}

// 2. Add at Last
void add_at_last(struct node **head_ref, int data) {
    struct node *newNode = create_node(data); // Using helper

    if (*head_ref == NULL) {
        *head_ref = newNode;
        return;
    }

    struct node *temp = *head_ref;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = newNode;
}

// 3. Add at Position
void add_at_pos(struct node **head_ref, int data, int pos) {
    if (pos == 1) {
        add_at_front(head_ref, data);
        return;
    }

    struct node *temp = *head_ref;
    for (int i = 1; i < pos - 1 && temp != NULL; i++) {
        temp = temp->next;
    }

    if (temp == NULL) {
        printf("Position %d is out of bounds!\n", pos);
    } else {
        struct node *newNode = create_node(data); // Using helper
        newNode->next = temp->next;
        temp->next = newNode;
    }
}

// 4. Display Function
void display(struct node *head) {
    struct node *temp = head;
    if (head == NULL) {
        printf("List is empty.\n");
        return;
    }
    while (temp != NULL) {
        printf("[%d] -> ", temp->data);
        temp = temp->next;
    }
    printf("NULL\n");
}

// Deletion functions remain the same as they use free(), not malloc()
void delete_front(struct node **head_ref) {
    if (*head_ref == NULL) {
        printf("List is already empty.\n");
        return;
    }
    struct node *temp = *head_ref;
    *head_ref = (*head_ref)->next;
    free(temp);
    printf("Front node deleted.\n");
}

void delete_last(struct node **head_ref) {
    if (*head_ref == NULL) return;
    struct node *temp = *head_ref;
    if (temp->next == NULL) {
        free(temp);
        *head_ref = NULL;
        return;
    }
    while (temp->next->next != NULL) temp = temp->next;
    free(temp->next);
    temp->next = NULL;
    printf("Last node deleted.\n");
}

void delete_at_pos(struct node **head_ref, int pos) {
    if (*head_ref == NULL) return;
    if (pos == 1) {
        delete_front(head_ref);
        return;
    }
    struct node *temp = *head_ref;
    for (int i = 1; i < pos - 1 && temp != NULL; i++) temp = temp->next;
    if (temp == NULL || temp->next == NULL) {
        printf("Position %d out of bounds.\n", pos);
        return;
    }
    struct node *nodeToDelete = temp->next;
    temp->next = temp->next->next;
    free(nodeToDelete);
    printf("Node at position %d deleted.\n", pos);
}

// Cleanup Function
void free_list(struct node **head_ref) {
    struct node *current = *head_ref;
    struct node *next;
    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }
    *head_ref = NULL;
    printf("All memory cleared.\n");
}

int main() {
    struct node *head = NULL; 
    
    create_list(&head);
    add_at_front(&head, 10);
    add_at_last(&head, 30);
    add_at_pos(&head, 20, 2);
    
    display(head);
    
    delete_front(&head);
    delete_last(&head);
    
    display(head);
    
    free_list(&head);
    return 0;
}