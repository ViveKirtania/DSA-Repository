#include <stdio.h>
#include <stdlib.h>

// Define a structure for a node in the linked list representing a number
struct Node {
    int digit;
    struct Node* next;
};

struct Node* reverse(struct Node* head) {
    struct Node* prev = NULL;
    struct Node* current = head;
    struct Node* next_node;

    while (current != NULL) {
        next_node = current->next;
        current->next = prev;
        prev = current;
        current = next_node;
    }

    return prev;
}

// Function to create a new node
struct Node* createNode(int digit) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if (newNode == NULL) {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    newNode->digit = digit;
    newNode->next = NULL;
    return newNode;
}

// Function to add two linked list numbers and return the result as a linked list
struct Node* addLinkedLists(struct Node* num1, struct Node* num2) {
    struct Node* result = NULL; // Resultant linked list
    struct Node* current = NULL;
    int carry = 0;

    while (num1 != NULL || num2 != NULL) {
        int sum = carry;
        if (num1 != NULL) {
            sum += num1->digit;
            num1 = num1->next;
        }
        if (num2 != NULL) {
            sum += num2->digit;
            num2 = num2->next;
        }

        carry = sum / 10;
        int digit = sum % 10;

        struct Node* newNode = createNode(digit);

        if (result == NULL) {
            result = newNode;
            current = newNode;
        } else {
            current->next = newNode;
            current = newNode;
        }
    }

    if (carry > 0) {
        struct Node* newNode = createNode(carry);
        current->next = newNode;
    }

    return result;
}

// Function to display a linked list number
void displayLinkedList(struct Node* num) {
    if (num == NULL) {
        printf("0\n");
        return;
    }
    while (num != NULL) {
        printf("%d", num->digit);
        num = num->next;
    }
    printf("\n");
}

// Function to free memory used by a linked list
void freeLinkedList(struct Node* num) {
    while (num != NULL) {
        struct Node* temp = num;
        num = num->next;
        free(temp);
    }
}

int main() {
    struct Node* num1 = NULL;
    struct Node* num2 = NULL;

    char ch;
    int digit;

    printf("Enter the first long integer (without leading zeros), one digit at a time. Enter -1 to stop:\n");
    while (1) {
        scanf("%d", &digit);
        if (digit == -1) {
            break;
        }
        struct Node* newNode = createNode(digit);
        newNode->next = num1;
        num1 = newNode;
    }

    printf("Enter the second long integer (without leading zeros), one digit at a time. Enter -1 to stop:\n");
    while (1) {
        scanf("%d", &digit);
        if (digit == -1) {
            break;
        }
        struct Node* newNode = createNode(digit);
        newNode->next = num2;
        num2 = newNode;
    }

    // Add the numbers and display the result
    struct Node* result = addLinkedLists(num1, num2);

    // Display the input numbers and their sum in original order
    printf("Number 1: ");
    displayLinkedList(reverse(num1));
    printf("Number 2: ");
    displayLinkedList(reverse(num2));
    printf("Result: ");
    displayLinkedList(reverse(result));

    return 0;
}
