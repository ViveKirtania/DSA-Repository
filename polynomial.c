#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct Term {
    float coefficient;
    int exponent;
};

struct Node {
    struct Term term;
    struct Node* next;
};

struct Node* createNode(float coefficient, int exponent) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->term.coefficient = coefficient;
    newNode->term.exponent = exponent;
    newNode->next = NULL;
    return newNode;
}

// Function to reduce terms with the same exponent in a polynomial
void reduceTerms(struct Node* polynomial) {
    struct Node* current = polynomial->next;
    while (current != polynomial) {
        struct Node* runner = current->next;
        while (runner != polynomial) {
            if (runner->term.exponent == current->term.exponent) {
                current->term.coefficient += runner->term.coefficient;
                struct Node* temp = runner;
                runner = runner->next;
                // Remove runner node
                current->next = runner;
                free(temp);
            } else {
                runner = runner->next;
            }
        }
        current = current->next;
    }
}

struct Node* Pread() {
    struct Node* head = createNode(0.0, 0); // Header node
    struct Node* current = head;

    int numTerms;
    printf("Enter the number of terms in the polynomial: ");
    scanf("%d", &numTerms);

    for (int i = 0; i < numTerms; i++) {
        float coefficient;
        int exponent;
        printf("Enter coefficient and exponent for term %d: ", i + 1);
        scanf("%f %d", &coefficient, &exponent);
        current->next = createNode(coefficient, exponent);
        current = current->next;
    }
    
    current->next = head; 
    return head;
}

void Pwrite(struct Node* head) {
    struct Node* current = head->next;

    if (current == NULL) {
        printf("Polynomial is empty.\n");
        return;
    }

    printf("%.2fx^%d", current->term.coefficient, current->term.exponent);
    current = current->next;

    while (current != head) {
        if (current->term.coefficient > 0) {
            printf(" + %.2fx^%d", current->term.coefficient, current->term.exponent);
        } else {
            printf(" %.2fx^%d", current->term.coefficient, current->term.exponent);
        }
        current = current->next;
    }
    printf("\n");
}

struct Node* Padd(struct Node* polynomialA, struct Node* polynomialB) {
    struct Node* result = createNode(0.0, 0); 
    struct Node* currentA = polynomialA->next;
    struct Node* currentB = polynomialB->next;
    struct Node* currentResult = result;

    while (currentA != polynomialA && currentB != polynomialB) {
        if (currentA->term.exponent == currentB->term.exponent) {
            float sum = currentA->term.coefficient + currentB->term.coefficient;
            if (sum != 0) {
                currentResult->next = createNode(sum, currentA->term.exponent);
                currentResult = currentResult->next;
            }
            currentA = currentA->next;
            currentB = currentB->next;
        } else if (currentA->term.exponent > currentB->term.exponent) {
            currentResult->next = createNode(currentA->term.coefficient, currentA->term.exponent);
            currentResult = currentResult->next;
            currentA = currentA->next;
        } else {
            currentResult->next = createNode(currentB->term.coefficient, currentB->term.exponent);
            currentResult = currentResult->next;
            currentB = currentB->next;
        }
    }

    while (currentA != polynomialA) {
        currentResult->next = createNode(currentA->term.coefficient, currentA->term.exponent);
        currentResult = currentResult->next;
        currentA = currentA->next;
    }

    while (currentB != polynomialB) {
        currentResult->next = createNode(currentB->term.coefficient, currentB->term.exponent);
        currentResult = currentResult->next;
        currentB = currentB->next;
    }

    currentResult->next = result; 
    return result;
}

struct Node* Psub(struct Node* polynomialA, struct Node* polynomialB) {
    struct Node* result = createNode(0.0, 0); // Header node
    struct Node* currentA = polynomialA->next;
    struct Node* currentB = polynomialB->next;
    struct Node* currentResult = result;

    while (currentA != polynomialA && currentB != polynomialB) {
        if (currentA->term.exponent == currentB->term.exponent) {
            float diff = currentA->term.coefficient - currentB->term.coefficient;
            if (diff != 0) {
                currentResult->next = createNode(diff, currentA->term.exponent);
                currentResult = currentResult->next;
            }
            currentA = currentA->next;
            currentB = currentB->next;
        } else if (currentA->term.exponent > currentB->term.exponent) {
            currentResult->next = createNode(currentA->term.coefficient, currentA->term.exponent);
            currentResult = currentResult->next;
            currentA = currentA->next;
        } else {
            currentResult->next = createNode(-currentB->term.coefficient, currentB->term.exponent);
            currentResult = currentResult->next;
            currentB = currentB->next;
        }
    }

    while (currentA != polynomialA) {
        currentResult->next = createNode(currentA->term.coefficient, currentA->term.exponent);
        currentResult = currentResult->next;
        currentA = currentA->next;
    }

    while (currentB != polynomialB) {
        currentResult->next = createNode(-currentB->term.coefficient, currentB->term.exponent);
        currentResult = currentResult->next;
        currentB = currentB->next;
    }

    currentResult->next = result; 
    return result;
}

/// Function to multiply two polynomials
struct Node* Pmult(struct Node* polynomialA, struct Node* polynomialB) {
    struct Node* result = createNode(0.0, 0); // Header node
    struct Node* currentA = polynomialA->next;
    struct Node* currentB = polynomialB->next;
    struct Node* currentResult = result;

    while (currentA != polynomialA) {
    currentB=polynomialB->next;
        while(currentB !=polynomialB){
        
            float prod = currentA->term.coefficient * currentB->term.coefficient;
            int prodpow = currentA->term.exponent + currentB->term.exponent;
            
                currentResult->next = createNode(prod, prodpow);
                currentResult = currentResult->next;
            
            currentB = currentB->next;
        }
        currentA = currentA->next;
    }

    

    currentResult->next = result;

    reduceTerms(result); 
    return result;
}

float Peval(struct Node* polynomial, float x) {
    float result = 0.0;
    struct Node* current = polynomial->next;

    while (current != polynomial) {
        result += current->term.coefficient * pow(x, current->term.exponent);
        current = current->next;
    }

    return result;
}

void Perase(struct Node* polynomial, int exponent) {
    struct Node* current = polynomial->next;
    struct Node* prev = polynomial;

    while (current != polynomial) {
        if (current->term.exponent == exponent) {
            prev->next = current->next;
            free(current);
            return; 
        }
        prev = current;
        current = current->next;
    }
}

int main() {
    struct Node* polynomialA = Pread();
    struct Node* polynomialB = Pread();
    
    printf("Polynomial A: ");
    Pwrite(polynomialA);
    
    printf("Polynomial B: ");
    Pwrite(polynomialB);
    
    printf("addition A+B: ");
    Pwrite(Padd(polynomialA,polynomialB));

    printf("subtraction A-B: ");
    Pwrite(Psub(polynomialA,polynomialB));

    printf("product: ");
    Pwrite(Pmult(polynomialA,polynomialB));

    printf("evalutation of polynomialA at x=1: ");
    printf("%.0f\n",Peval(polynomialA,1));

    printf("erasing the ^2 power from exponent B: ");
    Perase(polynomialB, 2);
    Pwrite(polynomialB);

    
    return 0;
}
