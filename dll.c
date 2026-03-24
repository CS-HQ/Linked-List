#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node *next;
    struct node *prev;
};

// 1. Initialize the list
void create_list(struct node **head_ref) {
    *head_ref = NULL;
    printf("List created/initialized.\n");
}

// Helper: Create a single node
struct node* create_node(int data) {
    struct node *newNode = (struct node *)malloc(sizeof(struct node));
    if (newNode == NULL) {
        printf("Memory error!\n");
        exit(1);
    }
    newNode->data = data;
    newNode->next = NULL;
    newNode->prev = NULL;
    return newNode;
}

// 2. Add at Front
void add_at_front(struct node **head_ref, int data) {
    struct node *newNode = create_node(data);
    newNode->next = *head_ref;
    if (*head_ref != NULL) {
        (*head_ref)->prev = newNode;
    }
    *head_ref = newNode;
}

// 3. Add at Last
void add_at_last(struct node **head_ref, int data) {
    struct node *newNode = create_node(data);
    if (*head_ref == NULL) {
        *head_ref = newNode;
        return;
    }
    struct node *temp = *head_ref;
    while (temp->next != NULL) temp = temp->next;
    temp->next = newNode;
    newNode->prev = temp;
}

// 4. Add at Position (add_at_pos)
void add_at_pos(struct node **head_ref, int data, int position) {
    if (position < 1) return;
    if (position == 1) {
        add_at_front(head_ref, data);
        return;
    }
    struct node *temp = *head_ref;
    for (int i = 1; temp != NULL && i < position - 1; i++) {
        temp = temp->next;
    }
    if (temp == NULL) return;

    struct node *newNode = create_node(data);
    newNode->next = temp->next;
    newNode->prev = temp;
    if (temp->next != NULL) {
        temp->next->prev = newNode;
    }
    temp->next = newNode;
}

// 5. Display
void display(struct node *head) {
    struct node *temp = head;
    if (temp == NULL) {
        printf("List is empty.\n");
        return;
    }
    while (temp != NULL) {
        printf("%d <-> ", temp->data);
        temp = temp->next;
    }
    printf("NULL\n");
}

// 6. Delete Front
void delete_front(struct node **head_ref) {
    if (*head_ref == NULL) return;
    struct node *temp = *head_ref;
    *head_ref = (*head_ref)->next;
    if (*head_ref != NULL) {
        (*head_ref)->prev = NULL;
    }
    free(temp);
}

// 7. Delete Last
void delete_last(struct node **head_ref) {
    if (*head_ref == NULL) return;
    struct node *temp = *head_ref;
    if (temp->next == NULL) {
        *head_ref = NULL;
    } else {
        while (temp->next != NULL) temp = temp->next;
        temp->prev->next = NULL;
    }
    free(temp);
}

// 9. Delete at a Particular Position
void delete_at_pos(struct node **head_ref, int position) {
    if (*head_ref == NULL || position < 1) {
        printf("Invalid position or empty list.\n");
        return;
    }

    struct node *temp = *head_ref;

    // Case 1: Deleting the first node
    if (position == 1) {
        delete_front(head_ref);
        return;
    }

    // Traverse to the node at the specific position
    for (int i = 1; temp != NULL && i < position; i++) {
        temp = temp->next;
    }

    // Case 2: Position is beyond the list length
    if (temp == NULL) {
        printf("Position %d is out of range.\n", position);
        return;
    }

    // Case 3: Deleting the last node
    if (temp->next == NULL) {
        delete_last(head_ref);
        return;
    }

    // Case 4: Deleting a middle node
    // Link the previous node to the next node
    temp->prev->next = temp->next;
    // Link the next node back to the previous node
    temp->next->prev = temp->prev;

    printf("Deleted %d from position %d.\n", temp->data, position);
    free(temp);
}

// 8. Free List (Cleans up all nodes)
void free_list(struct node **head_ref) {
    struct node *current = *head_ref;
    struct node *nextNode;
    while (current != NULL) {
        nextNode = current->next;
        free(current);
        current = nextNode;
    }
    *head_ref = NULL;
    printf("Memory freed. List is empty.\n");
}

int main() {
    struct node *head;

    create_list(&head);
    add_at_front(&head, 10);
    add_at_last(&head, 30);
    add_at_pos(&head, 20, 2); // List: 10 <-> 20 <-> 30
    
    printf("Initial List: ");
    display(head);
    
    // Testing the specific position deletion
    delete_at_pos(&head, 2); // Should delete 20
    
    printf("After deleting position 2: ");
    display(head);
    
    free_list(&head);
    return 0;
}