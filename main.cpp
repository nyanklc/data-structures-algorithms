#include <iostream>
#include <bits/stdc++.h>

using namespace std;

int numOfSwaps=0;
void printArray(int a[], int n)
{
    for (int i = 0; i < n; i++)
        printf("%d ", a[i]);
    printf("\n");
}

int shellSort(int arr[], int n)
{
    // Start with a big gap, then reduce the gap
    for (int gap = n/2; gap > 0; gap /= 2)
    {
        // Do a gapped insertion sort for this gap size.
        // The first gap elements a[0..gap-1] are already in gapped order
        // keep adding one more element until the entire array is
        // gap sorted
        for (int i = gap; i < n; i += 1)
        {
            // add a[i] to the elements that have been gap sorted
            // save a[i] in temp and make a hole at position i
            int temp = arr[i];

            // shift earlier gap-sorted elements up until the correct
            // location for a[i] is found
            int j;
            for (j = i; j >= gap && arr[j - gap] > temp; j -= gap){
                arr[j] = arr[j - gap];

            }
            //  put temp (the original a[i]) in its correct location
            arr[j] = temp;
            printArray(arr,n);
        }
    }
    return 0;
}
// Driver program
int main()
{
    int a[] = {1,3,2,1,1,2,2};
    int n = 7;
    printArray(a,n);
    shellSort(a, n);

    return 0;
}
