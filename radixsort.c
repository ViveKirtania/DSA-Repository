#include <stdio.h>

void print(int arr[], int n){
    int i;
    for (i=0;i<n;i++){
        printf("%d ",arr[i]);
    }
}

int getmax(int arr[], int n) {           //function to get max digits in the array
    int i, max = arr[0], count = 0;
    
    for (i = 0; i < n; i++) {
        if (arr[i] > max) {
            max = arr[i];
        }
    }
    
    while (max != 0) {
        max /= 10;
        count++;
    }
    return count;
}

int power(int a, int b){              //function to get power of 2 numbers (i need function for integer, the pow() function in <math.h> is for double)
    int i,c;
    c=a;
    if(b==0){
        return 1;
    }
    else{
    for (i=1;i<b;i++){
        a=a*c;
    }}
return a;
}

void countSort(int arr[], int length, int exp) {
    int output[length]; // Create a temporary output array
    int count[10] = {0};

    // Count the occurrences of each digit at the given exponent
    for (int i = 0; i < length; i++) {
        int digit = (arr[i] / exp) % 10;
        count[digit]++;
    }

    // Calculate the cumulative count
    for (int i = 1; i < 10; i++) {
        count[i] += count[i - 1];
    }

    // Build the output array
    for (int i = length - 1; i >= 0; i--) {
        int digit = (arr[i] / exp) % 10;
        output[count[digit] - 1] = arr[i];
        count[digit]--;
    }

    // Copy the sorted elements back to the original array
    for (int i = 0; i < length; i++) {
        arr[i] = output[i];
    }
}

void radixsort(int arr[], int n) {
    printf("\n");
    int max_digits = getmax(arr, n);
    int i=0;
    for (int exp = 1; exp < power(10, max_digits); exp *= 10) {
        i++;
        countSort(arr, n, exp);

        printf("\nStep %d: ", i);
        print(arr, n);
    }
}

int main(){
    int arr[100];
    int n,i=0;
    printf("enter number of terms: ");
    scanf("%d",&n);

    printf("enter the numbers to be sorted: ");
    for(i=0;i<n;i++){
        scanf("%d",&arr[i]);
    }
    printf("\nunsorted array: ");print(arr,n);
    radixsort(arr, n);
    printf("\n\nsorted array: ");print(arr, n);

}
