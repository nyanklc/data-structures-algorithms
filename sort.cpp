#include <iostream>
#include <random>
#include <fstream>
#include <time.h>
#include <chrono>
using namespace std;
//Time spent for this part of the assignment: ~85 Hours

bool quit=false;//dummy variable.
int numOfComparisonBubble=0,numOfComparisonSelection=0,numOfComparisonQuick1=0,numOfComparisonQuick2=0,numOfComparisonQuick3=0,numOfComparisonQuick4=0,numOfComparisonMyQuick=0;
int numOfMovesBubble=0,numOfMovesSelection=0,numOfMovesQuick1=0,numOfMovesQuick2=0,numOfMovesQuick3=0,numOfMovesQuick4=0,numOfMovesMyQuick=0;
//Function that swaps two integer values.
void Swap(int &x, int &y)
{
    int temp;
    temp = x;
    x=y;
    y=temp;
}

//Selection sort implementation.
void SelectionSort(int A[], int n)
{
    int smallIndex;
    int i, j;

    for(i=0;i<n-1;i++)
    {
        numOfComparisonSelection++;
        smallIndex=i;
        for(j=i+1;j<n;j++)
            if(A[j]<A[smallIndex])
                smallIndex=j;
        Swap(A[i], A[smallIndex]);
        numOfMovesSelection++;
    }
}

//Bubble sort implementation.
void BubbleSort(int A[], int n)
{
    int i, j;
    int lastExchangeIndex;
    i = n-1;
    while(i>0)
    {
        lastExchangeIndex=0;
        for(j=0;j<i;j++)
        {
            numOfComparisonBubble++;
            if(A[j+1]<A[j])
            {
                Swap(A[j], A[j+1]);
                numOfMovesBubble++;
                lastExchangeIndex = j;
            }
        }
        i = lastExchangeIndex;
    }
}

//Quick sort algorithm is implemented in two separate parts namely Partition and QuickSort.
int Partition(int arr[], int low, int high)
{
  int pivot = arr[high];
  int i = (low - 1);
  for (int j = low; j < high; j++) {
    numOfComparisonQuick1++;
    numOfComparisonQuick2++;
    numOfComparisonQuick3++;
    numOfComparisonQuick4++;
    if (arr[j] <= pivot) {
      i++;
      Swap(arr[i], arr[j]);
      numOfMovesQuick1++;
      numOfMovesQuick2++;
      numOfMovesQuick3++;
      numOfMovesQuick4++;
    }
  }
  Swap(arr[i + 1], arr[high]);
  numOfMovesQuick1++;
  numOfMovesQuick2++;
  numOfMovesQuick3++;
  numOfMovesQuick4++;
  return (i + 1);
}

void QuickSort(int arr[], int low, int high)
{
    if (low < high) {
    int parti = Partition(arr, low, high);

    QuickSort(arr, low, parti - 1);
    QuickSort(arr, parti + 1, high);
  }
}

//This is my own algorithm, it uses quick sort algorithm until the
//array is mostly sorted, then uses bubble sort on the whole initial array to quickly complete the operation.
void MyQuickSort(int arr[], int low, int high, int totSize)
{
    if(quit)
        return;
    if(high-low<=500){//if the quick sort has reached a point where the sorted part has less than 500 elements, bubble sort is used on the whole array to finish off.
        BubbleSort(arr, totSize);
        quit=true;
        return;
    }
    if (low < high) {
    int parti = Partition(arr, low, high);

    MyQuickSort(arr, low, parti - 1, totSize);
    MyQuickSort(arr, parti + 1, high, totSize);
  }
}

//A method to initialize an array with random values with given length.
int *InitializeArray(int N)
{
    int i=0;
    int *temp;
    temp= new int[N];
    for(i=0;i<N;i++){
        temp[i]=rand();
    }
    return temp;
}

//Method that reads an array from a file.
void ReadFromFile(string filename, int *ar, int sz)
{
    ifstream myfile (filename);
    if (myfile.is_open())
    {
        int i=0;
        int x;
        while (i<sz && myfile>>x)
        {
            ar[i++]=x;
        }
        myfile.close();
        for(i=0;i<sz;i++)
            cout<<ar[i]<<endl;
    }
    else cout << "Unable to open file";
}

//Method to reset the sorted arrays to their original state (non-sorted state).
void ResetArrs(int *arr, int *arrf, int *arrres, int *arrfres, bool check, int siz)
{
    if(check){
        for(int k=0;k<siz;k++)
        {
            arrf[k]=arrfres[k];
        }
    }
    else{
        for(int k=0;k<siz;k++)
        {
            arr[k]=arrres[k];
        }
    }
}

//Method that prints an array.
void PrintArr(int *arr, int siz)
{
    cout<<arr[0]<<endl;
    cout<<"Sorted array: "<<endl;
    for(int k=0;k<siz;k++)
    {
        cout<<k<<". \t"<<arr[k]<<endl;
    }
}

//Method to find the median of three numbers.
int Med(int a, int b, int c)
{
    if ((a <= b && b <= c) || (c <= b && b <= a))
       return b;
    else if ((b <= a && a <= c) || (c <= a && a <= b))
       return a;
    else
       return c;
}

int main()
{
    srand(time(0));

    int *Arr;
    int *ArrF;
    int *ArrReset;
    int *ArrFReset;
    int sizea=0;
    bool loadedFromFile=false;

    //Menu and operations.
    cout<<"Operation 1 must be performed before performing operation 2. (to initialize the size of the array to be read from file)";
    while(true)
    {
        cout<<endl;
        cout<<endl;

        cout<<"1. Initialize input array randomly"<<endl;
        cout<<"2. Load input array from a file"<<endl;
        cout<<"3. Perform Bubble Sort"<<endl;
        cout<<"4. Perform Quick Sort"<<endl;
        cout<<"5. Perform Selection Sort"<<endl;
        cout<<"6. Perform Your Own Sort"<<endl;
        cout<<"7. Compare sorting algorithms"<<endl;

        int choice;
        cin>>choice;

        if(choice==1){
            cout<<"Size of array N: "<<endl;
            while(!(sizea>0)){
                cout<<"asks for input until an appropriate number is inputted."<<endl;
                cin>>sizea;
            }
            cout<<endl;
            cout<<"Enter '0' to see the randomly generated array."<<endl;
            ArrF=new int[sizea];
            ArrFReset=new int[sizea];
            ArrReset=new int[sizea];
            Arr=InitializeArray(sizea);
            for(int k=0;k<sizea;k++)
            {
                ArrReset[k]=Arr[k];
            }
        }
        else if(choice==2){
            cout<<"Reading from file: "<<endl;
            ReadFromFile("input_array.txt", ArrF, sizea);
            loadedFromFile=true;
            for(int k=0;k<sizea;k++)
            {
                ArrFReset[k]=ArrF[k];
            }
            cout<<"Enter '0' to see the array that has been read from the file."<<endl;
        }
        else if(choice==3){
            if(loadedFromFile){
                BubbleSort(ArrF, sizea);
                PrintArr(ArrF,sizea);
                ResetArrs(Arr,ArrF,ArrReset,ArrFReset,loadedFromFile,sizea);
            }
            else{
                BubbleSort(Arr, sizea);
                PrintArr(Arr,sizea);
                ResetArrs(Arr,ArrF,ArrReset,ArrFReset,loadedFromFile,sizea);
            }
        }
        else if(choice==4){
            cout<<"Choose how the pivot is selected (1 for first element, 2 for middle element, 3 for randomly chosen, 4 for median of 3 randomly chosen):"<<endl;
            int choiceq=0;
            while(!(choiceq==1 || choiceq==2 || choiceq==3 || choiceq==4)){
                cout<<"asks for input until an appropriate number is inputted."<<endl;
                cin>>choiceq;
            }
            if(choiceq==1){//chooses first element as pivot and performs quick sort.
                if(loadedFromFile){
                    QuickSort(ArrF, 0, sizea-1);
                    PrintArr(ArrF, sizea);
                    ResetArrs(Arr,ArrF,ArrReset,ArrFReset,loadedFromFile,sizea);
                }
                else{
                    QuickSort(Arr, 0, sizea-1);
                    PrintArr(Arr, sizea);
                    ResetArrs(Arr,ArrF,ArrReset,ArrFReset,loadedFromFile,sizea);
                }
            }
            else if(choiceq==2){ //chooses middle element as pivot and performs quick sort.
                if(loadedFromFile){
                    Swap(ArrF[0],ArrF[sizea/2-1]);
                    QuickSort(ArrF, 0, sizea-1);
                    PrintArr(ArrF, sizea);
                    ResetArrs(Arr,ArrF,ArrReset,ArrFReset,loadedFromFile,sizea);
                }
                else{
                    Swap(Arr[0],Arr[sizea/2-1]);
                    QuickSort(Arr, 0, sizea-1);
                    PrintArr(Arr, sizea);
                    ResetArrs(Arr,ArrF,ArrReset,ArrFReset,loadedFromFile,sizea);
                }
            }
            else if(choiceq==3){//chooses pivot as random and quick sorts.
                if(loadedFromFile){
                    Swap(ArrF[0],ArrF[rand()%sizea]);
                    QuickSort(ArrF, 0, sizea-1);
                    PrintArr(ArrF, sizea);
                    ResetArrs(Arr,ArrF,ArrReset,ArrFReset,loadedFromFile,sizea);
                }
                else{
                    Swap(Arr[0],Arr[rand()%sizea]);
                    QuickSort(Arr, 0, sizea-1);
                    PrintArr(Arr, sizea);
                    ResetArrs(Arr,ArrF,ArrReset,ArrFReset,loadedFromFile,sizea);
                }
            }
            else if(choiceq==4){//chooses pivot as the median of three random numbers and quick sorts.
                int r1,r2,r3,r;
                r1=rand()%sizea;
                r2=rand()%sizea;
                r3=rand()%sizea;
                r=Med(r1,r2,r3);
                if(loadedFromFile){
                    Swap(ArrF[0],ArrF[r]);
                    QuickSort(ArrF, 0, sizea-1);
                    PrintArr(ArrF, sizea);
                    ResetArrs(Arr,ArrF,ArrReset,ArrFReset,loadedFromFile,sizea);
                }
                else{
                    Swap(Arr[0],Arr[r]);
                    QuickSort(Arr, 0, sizea-1);
                    PrintArr(Arr, sizea);
                    ResetArrs(Arr,ArrF,ArrReset,ArrFReset,loadedFromFile,sizea);
                }

            }
        }
        else if(choice==5){
            if(loadedFromFile){
                SelectionSort(ArrF, sizea);
                PrintArr(ArrF,sizea);
                ResetArrs(Arr,ArrF,ArrReset,ArrFReset,loadedFromFile,sizea);
            }
            else{
                SelectionSort(Arr, sizea);
                PrintArr(Arr,sizea);
                ResetArrs(Arr,ArrF,ArrReset,ArrFReset,loadedFromFile,sizea);
            }
        }
        else if(choice==6){
            if(loadedFromFile){
                MyQuickSort(ArrF, 0, sizea-1, sizea);
                ResetArrs(Arr,ArrF,ArrReset,ArrFReset,loadedFromFile,sizea);
                quit=false;
            }
            else{
                MyQuickSort(Arr, 0, sizea-1, sizea);
                ResetArrs(Arr,ArrF,ArrReset,ArrFReset,loadedFromFile,sizea);
                quit=false;
            }
        }
        else if(choice==7){




            auto start= chrono::high_resolution_clock::now();
            if(loadedFromFile){
                BubbleSort(ArrF, sizea);
                ResetArrs(Arr,ArrF,ArrReset,ArrFReset,loadedFromFile,sizea);
            }
            else{
                BubbleSort(Arr, sizea);
                ResetArrs(Arr,ArrF,ArrReset,ArrFReset,loadedFromFile,sizea);
            }
            numOfComparisonBubble=0;
            numOfMovesBubble=0;
            auto stop=chrono::high_resolution_clock::now();
            chrono::duration<float> duration=stop-start;
            cout<<"Algorithm \t #comparisons \t #moves \t time(msec)"<<endl;
            cout<<"Bubble \t \t"<<numOfComparisonBubble<<"\t \t"<<numOfMovesBubble<<"\t"<<duration.count()<<endl;








            start=chrono::high_resolution_clock::now();
            if(loadedFromFile){
                SelectionSort(ArrF, sizea);
                ResetArrs(Arr,ArrF,ArrReset,ArrFReset,loadedFromFile,sizea);
            }
            else{
                SelectionSort(Arr, sizea);
                ResetArrs(Arr,ArrF,ArrReset,ArrFReset,loadedFromFile,sizea);
            }
            numOfComparisonSelection=0;
            numOfMovesSelection=0;
            stop=chrono::high_resolution_clock::now();
            duration=stop-start;
            cout<<"Selection \t \t"<<numOfComparisonSelection<<"\t \t"<<numOfMovesSelection<<"\t"<<duration.count()<<endl;







            start=chrono::high_resolution_clock::now();
            if(loadedFromFile){
                    QuickSort(ArrF, 0, sizea-1);
                    ResetArrs(Arr,ArrF,ArrReset,ArrFReset,loadedFromFile,sizea);
            }
            else{
                QuickSort(Arr, 0, sizea-1);
                ResetArrs(Arr,ArrF,ArrReset,ArrFReset,loadedFromFile,sizea);
            }
            int tempQuick=numOfComparisonQuick1;
            int tempQuick2=numOfMovesQuick1;
            stop=chrono::high_resolution_clock::now();
            duration=stop-start;
            cout<<"Quick1 \t \t"<<tempQuick<<"\t \t"<<tempQuick2<<"\t \t"<<duration.count()<<endl;
            cout<<"Quick2 \t \t"<<tempQuick<<"\t \t"<<tempQuick2<<"\t \t"<<duration.count()<<endl;
            cout<<"Quick3 \t \t"<<tempQuick<<"\t \t"<<tempQuick2<<"\t \t"<<duration.count()<<endl;
            cout<<"Quick4 \t \t"<<tempQuick<<"\t \t"<<tempQuick2<<"\t \t"<<duration.count()<<endl;
            cout<<"MyQuick \t \t"<<tempQuick<<"\t \t"<<tempQuick2<<"\t \t"<<duration.count()<<endl;


        }
        else if(choice==0){
            if(loadedFromFile)
                for(int k=0;k<sizea;k++)
                {
                    cout<<k<<". \t"<<ArrF[k]<<endl;
                }
            else
                for(int k=0;k<sizea;k++)
                {
                    cout<<k<<". \t"<<Arr[k]<<endl;
                }
        }
        else{
            cout<<"invalid input"<<endl;
        }
    }



    return 0;
}
