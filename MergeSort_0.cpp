#include<iostream>
#include<cstdlib>
#include<time.h>
#include<conio.h>
#include<iomanip> //precision
using namespace std;


void PrintData(int data[], int length){
	cout<<endl;
	for(int i = 0; i < length; i++){
		if(i%10 == 0){
			cout<<endl;
		}
		else{ 
			cout<<"\t";
		}
		
		cout<<data[i];
	}
	cout<<endl<<endl<<endl;
}

void CopyArray(int array1[], int array2[],  int length){
	for(int i=0; i < length; i++){
		array2[i] = array1[i];
	}	
}

//ALMOST SORTED DATA: (NOT YET USED BUT TESTED WORKING)
void SwapArray(int array1[], int array2[], int length){
     CopyArray(array1, array2,length);
     array2[18] = array1[19];
     array2[19] = array1[18];
     }
     
void Merge(int theArray[], int length, int first, int mid, int last, int* compareCount, int* movesCount){
	int tempArray[length]; // temp array
	int first1 = first; // subarray begin
	int last1 = mid; // end of first subarray
	int first2 = mid + 1; // secnd subarry begin
	int last2 = last; // end of secnd subarry
	int index = first1;
	
	// next available location in tempArray
	for (; (first1 <= last1) && (first2 <= last2); ++index){
		*compareCount += 1;
		if (theArray[first1] < theArray[first2]){
			tempArray[index] = theArray[first1];
			++first1;
			*movesCount += 1;	
		}
		else {
			tempArray[index] = theArray[first2];
			++first2;
			*movesCount += 1;
		}
	}
	
	for (; first1 <= last1; ++first1, ++index){
		tempArray[index] = theArray[first1];
		*movesCount += 1;
	}
		
	for (; first2 <= last2; ++first2, ++index){
		tempArray[index] = theArray[first2];
		*movesCount += 1;
	}

	for (index = first; index <= last; ++index)
		theArray[index] = tempArray[index];
}

void MergeSort(int theArray[], int length, int first, int last, int* divideCount, int* compareCount, int* movesCount){
	
	if (first < last)
	{ // sort each half
		*divideCount += 1;
		int mid = (first + last)/2; // index of midpoint
		// sort left half theArray[first..mid]
		MergeSort(theArray, length, first, mid, divideCount, compareCount, movesCount);
		// sort right half theArray[mid+1..last]
		MergeSort(theArray, length, mid+1, last, divideCount, compareCount, movesCount);
		// merge the two halves
		Merge(theArray, length, first, mid, last, compareCount, movesCount);
	} // end if
}

int Partition(int T[], int first, int last, int* compareCount, int* movesCount)
{
     int pivot, temp;
     int loop, cutPoint, bottom, top;
     pivot = T[first];
     bottom = first;
     top = last;
     loop = 1;
     while (loop){
		while (T[top]>pivot)
		{
            *compareCount+=1;
		   	top--;
		}
         //  cout<<"top"<<T[top]<<endl;
        while (T[bottom]<pivot)
        { 
			*compareCount+=1;
		   	bottom++;
		}
        //   cout<<"bottom"<<T[bottom]<<endl;
	    if (bottom < top)
		 {	
            if(T[top] == pivot && T[bottom]== pivot){
				*compareCount+=1;
				top--;
				continue;
			}
	           temp = T[bottom];
	           T[bottom]=T[top];
	           T[top]=temp;
	           *movesCount+=1;
	    }
	     else {
	          loop=0;
	          cutPoint=top;
	    }
     }
     //cout<<"cutpoint"<<cutPoint<<endl;
     return cutPoint;
} //end partition()

void QuickSort (int T[], int first, int last, int* compareCount, int* movesCount)
{
     int cut;
     if (first < last){
          cut = Partition(T,first,last, compareCount, movesCount);
          QuickSort(T, first, cut, compareCount, movesCount);
          QuickSort(T, cut+1, last, compareCount, movesCount);
     }
}



void GenerateRandomNumbers(int numbers[], int length){
    	srand(time(NULL));
	for(int i = 0; i< length; i++){
		numbers[i] = (rand() % 1000) + 1;
	}
}

void SortData(int counts[], int data[], int length)
{
	int tempdata[length], S_data[length], S_tempdata[length], tempdata500[length], tempdata100[length];
	CopyArray(data, tempdata, length);
	MergeSort(data, length, 0, length - 1, &counts[0], &counts[1],&counts[2]);
    if (length == 100){
         cout<<"Sorting...Merge"<<endl;
         PrintData(data, length);
    }
    QuickSort(tempdata, 0, length - 1, &counts[3], &counts[4]);
    if (length == 100){
         cout<<"Sorting...Quick"<<endl;
         PrintData(tempdata, length);
    }
    SwapArray(data, S_data, length);
    CopyArray(S_data, S_tempdata, length);
    cout<<"Swapped_data"<<endl;
    PrintData(S_data, length);
    MergeSort(S_data, length, 0, length - 1, &counts[5], &counts[6],&counts[7]);
    QuickSort(S_tempdata, 0, length - 1, &counts[8], &counts[9]);
}

void PrintCounts(int counts[], int length, int x, int y)
{
    double MergeCom = counts[x];
	double QuickCom = counts[y];
	double ComRatio = MergeCom/QuickCom;
    cout<<length<<"\t\t"<<counts[x]<<"\t\t"<<counts[y]<<"\t\t"<<ComRatio<<endl;
    x=0;
    y=0;
}
int main()
{
    int data[1000], tempdata500[500], tempdata100[100]; 
    int Data100[]={0,0,0,0,0,0,0,0,0,0};
	int Data500[]={0,0,0,0,0,0,0,0,0,0};
	int Data1000[]={0,0,0,0,0,0,0,0,0,0};
	GenerateRandomNumbers(data, 1000);
	CopyArray(data, tempdata500, 500);
	CopyArray(data, tempdata100, 100);
	cout<<"Generated random numbers"<<endl;
    	PrintData(tempdata100, 100);
	SortData(Data1000, data, 1000);
    	SortData(Data500, tempdata500, 500);
    	SortData(Data100, tempdata100, 100);
    	cout<<setprecision(1)<<fixed;
	cout<<"NUMBER\t\tMERGE SORT\tQUICK SORT\tRATIO"<<endl;
	cout<<endl<<endl<<"-----------compare counts using random data-----------"<<endl;
    	PrintCounts(Data100, 100, 1, 3);
	PrintCounts(Data500, 500, 1, 3);
	PrintCounts(Data1000, 1000, 1, 3);
	cout<<endl<<endl<<"-------------move counts using random data------------"<<endl;
    	PrintCounts(Data100, 100, 2, 4);
	PrintCounts(Data500, 500, 2, 4);
	PrintCounts(Data1000, 1000, 2, 4);
	cout<<endl<<endl<<"-----------compare counts using sorted data-----------"<<endl;
    	PrintCounts(Data100, 100, 6, 8);
	PrintCounts(Data500, 500, 6, 8);
	PrintCounts(Data1000, 1000, 6, 8);
	cout<<endl<<endl<<"-------------move counts using sorted data------------"<<endl;
    	PrintCounts(Data100, 100, 7, 9);
	PrintCounts(Data500, 500, 7, 9);
	PrintCounts(Data1000, 1000, 7, 9);
	getch();
    return 0;
}
