#include <cstdlib> 
#include <ctime> 
#include <iostream>
#include <chrono>
using namespace std;
typedef std::chrono::high_resolution_clock::time_point TimeVar;

#define duration(a) std::chrono::duration_cast<std::chrono::duration<double>>(a).count()
#define timeNow() std::chrono::high_resolution_clock::now()


void bubbleSort(int *arr,int n);
void insertionSort(int *arr,int length);
void selectionSort(int *arr,int n);
void quickSort(int *arr,int left,int right);
void merge(int *arr,int l,int m,int r);
void mergeSort(int *arr, int l, int r);
void printArray(int *arr, int size);
void max_heapify(int *a, int i, int n);
void heapsort(int *a, int n);
void build_maxheap(int *a, int n);
int getMax(int *arr, int n);
void countSort(int *arr, int n, int exp);
void radixsort(int *arr, int n);
int* generateArray(int size);


template<typename F, typename... Args>
double funcTime(F func, Args&&... args){
    TimeVar t1=timeNow();
    func(std::forward<Args>(args)...);
    return duration(timeNow()-t1);
}

int main(){
      
      int input[] = {10, 100, 1000, 10000, 100000, 1000000};
     
      for (int j = 0 ; j < 10 ; j++){
            cout << "------------------------------------" << endl;
            for (int i = 0 ; i < 6 ; i++){
                int* array = generateArray(input[i]);
                cout << "Initial Array" << endl;
               // printArray(array,input[i]);
                cout << endl;
                cout << "Input: " << input[i] << endl;
                //cout <<"BubbleSort: "<< funcTime(bubbleSort,array,input[i]) << endl;
                cout <<"Quick Sort: "<< funcTime(quickSort,array,0,input[i] - 1) << endl;
                //cout <<"Insertion Sort: "<< funcTime(insertionSort,array,input[i]) << endl;
                //cout <<"Selection Sort: "<< funcTime(selectionSort,array,input[i]) << endl;
                //cout <<"Merge Sort: "<< funcTime(mergeSort,array,0,input[i] - 1) << endl;
                //cout <<"HeapSort: "<< funcTime(heapsort,array,input[i]) << endl;
                //cout <<"Radix Sort: "<< funcTime(radixsort,array,input[i]) << endl;
                cout << endl;
                cout << "Sorted Array" << endl;
                //printArray(array,input[i]);
                delete array;
                cout << "_____________________" << endl;
            }
      }
      return 0;
}

int* generateArray(int size){
      int* array = new int[size];
      srand((unsigned)time(0)); 
      for(int i=0; i<size; i++){ 
            array[i] = (rand()%100)+1;
      }
      return array;
};

void bubbleSort(int *arr, int n) {
      bool swapped = true;
      int j = 0;
      int tmp;
      while (swapped) {
            swapped = false;
            j++;
            for (int i = 0; i < n - j; i++) {
                  if (arr[i] > arr[i + 1]) {
                        tmp = arr[i];
                        arr[i] = arr[i + 1];
                        arr[i + 1] = tmp;
                        swapped = true;
                  }
            }
      }
}

void insertionSort(int *arr, int length) {
      int i, j, tmp;
      for (i = 1; i < length; i++) {
            j = i;
            while (j > 0 && arr[j - 1] > arr[j]) {
                  tmp = arr[j];
                  arr[j] = arr[j - 1];
                  arr[j - 1] = tmp;
                  j--;
            }
      }
}

void selectionSort(int *arr, int n) {
      int i, j, minIndex, tmp;    
      for (i = 0; i < n - 1; i++) {
            minIndex = i;
            for (j = i + 1; j < n; j++)
                  if (arr[j] < arr[minIndex])
                        minIndex = j;
            if (minIndex != i) {
                  tmp = arr[i];
                  arr[i] = arr[minIndex];
                  arr[minIndex] = tmp;
            }
      }
}

void quickSort(int *arr, int left, int right) {
      int i = left, j = right;
      int tmp;
      int pivot = arr[(left + right) / 2];
      /* partition */
      while (i <= j) {
            while (arr[i] < pivot)
                  i++;
            while (arr[j] > pivot)
                  j--;
            if (i <= j) {
                  tmp = arr[i];
                  arr[i] = arr[j];
                  arr[j] = tmp;
                  i++;
                  j--;
            }
      };
      /* recursion */
      if (left < j)
            quickSort(arr, left, j);
      if (i < right)
            quickSort(arr, i, right);
}

void merge(int *arr, int l, int m, int r) {
      //http://quiz.geeksforgeeks.org/merge-sort/
    int i, j, k;
    int n1 = m - l + 1;
    int n2 =  r - m;
 
    /* create temp arrays */
    int L[n1], R[n2];
 
    /* Copy data to temp arrays L[] and R[] */
    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1+ j];
 
    /* Merge the temp arrays back into arr[l..r]*/
    i = 0; // Initial index of first subarray
    j = 0; // Initial index of second subarray
    k = l; // Initial index of merged subarray
    while (i < n1 && j < n2){
        if (L[i] <= R[j]){
            arr[k] = L[i];
            i++;
        }else{
            arr[k] = R[j];
            j++;
        }
        k++;
    }
 
    /* Copy the remaining elements of L[], if there
       are any */
    while (i < n1){
        arr[k] = L[i];
        i++;
        k++;
    }
 
    /* Copy the remaining elements of R[], if there
       are any */
    while (j < n2){
        arr[k] = R[j];
        j++;
        k++;
    }
}
 
/* l is for left index and r is right index of the
   sub-array of arr to be sorted */
void mergeSort(int *arr, int l, int r){
    if (l < r){
        // Same as (l+r)/2, but avoids overflow for
        // large l and h
        int m = l+(r-l)/2;
 
        // Sort first and second halves
        mergeSort(arr, l, m);
        mergeSort(arr, m+1, r);
 
        merge(arr, l, m, r);
    }
}
 
/* Function to print an array */
void printArray(int *arr, int size){
    int i;
    for (i=0; i < size; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

//http://proprogramming.org/heap-sort-in-c/
void max_heapify(int *a, int i, int n){
    int j, temp;
    temp = a[i];
    j = 2*i;
    while (j <= n){
        if (j < n && a[j+1] > a[j])
            j = j+1;
        if (temp > a[j])
            break;
        else if (temp <= a[j]){
            a[j/2] = a[j];
            j = 2*j;
        }
    }
    a[j/2] = temp;
    return;
}

void heapsort(int *a, int n){
    build_maxheap(a,n);
    int i, temp;
    for (i = n; i >= 2; i--){
        temp = a[i];
        a[i] = a[1];
        a[1] = temp;
        max_heapify(a, 1, i - 1);
    }
}

void build_maxheap(int *a, int n){
    int i;
    for(i = n/2; i >= 1; i--){
        max_heapify(a, i, n);
    }
}


//http://www.geeksforgeeks.org/radix-sort/
int getMax(int *arr, int n){
    int mx = arr[0];
    for (int i = 1; i < n; i++)
        if (arr[i] > mx)
            mx = arr[i];
    return mx;
}
 
// A function to do counting sort of *arr according to
// the digit represented by exp.
void countSort(int *arr, int n, int exp){
    int output[n]; // output array
    int i, count[10] = {0};
 
    // Store count of occurrences in count[]
    for (i = 0; i < n; i++)
        count[ (arr[i]/exp)%10 ]++;
 
    // Change count[i] so that count[i] now contains actual
    //  position of this digit in output[]
    for (i = 1; i < 10; i++)
        count[i] += count[i - 1];
 
    // Build the output array
    for (i = n - 1; i >= 0; i--){
        output[count[ (arr[i]/exp)%10 ] - 1] = arr[i];
        count[ (arr[i]/exp)%10 ]--;
    }
 
    // Copy the output array to *arr, so that *arr now
    // contains sorted numbers according to current digit
    for (i = 0; i < n; i++)
        arr[i] = output[i];
}
 
// The main function to that sorts *arr of size n using 
// Radix Sort
void radixsort(int *arr, int n){
    // Find the maximum number to know number of digits
    int m = getMax(arr, n);
 
    // Do counting sort for every digit. Note that instead
    // of passing digit number, exp is passed. exp is 10^i
    // where i is current digit number
    for (int exp = 1; m/exp > 0; exp *= 10)
        countSort(arr, n, exp);
}
 