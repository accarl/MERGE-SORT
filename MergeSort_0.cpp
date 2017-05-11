#include<iostream>
#include<cstdlib>
#include<time.h>
#include<conio.h>
#include<iomanip>
using namespace std;


void PrintData(int data[], int length){
	cout<<endl<<endl;
	for(int i = 0; i < length; i++){
		if(i%10 == 0){
			cout<<endl;
		}
		else{ 
			cout<<"\t";
		}
		
		cout<<data[i];
	}
	cout<<endl<<endl;
}

void CopyArray(int array1[], int array2[],  int length){
	for(int i=0; i < length; i++){
		array2[i] = array1[i];
	}	
}

//ALMOST SORTED DATA: (NOT YET USED BUT TESTED WORKING)
void SwapArray(int array1[], int array2[], int length){
     CopyArray(array1, array2,length);
     array2[8] = array1[9];
     array2[9] = array1[8];
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
    	if (length == 10){
        	cout<<"Sorting...Merge"<<endl;
        	PrintData(data, length);
    	}
    	QuickSort(tempdata, 0, length - 1, &counts[3], &counts[4]);
    	if (length == 10){
         	cout<<"Sorting...Quick"<<endl;
         	PrintData(tempdata, length);
    	}
    	SwapArray(data, S_data, length);
    	CopyArray(S_data, S_tempdata, length);
    	cout<<"Swapped_data"<<endl;
    	PrintData(S_data, length);
    	MergeSort(S_data, length, 0, length - 1, &counts[5], &counts[6],&counts[7]);
    	QuickSort(S_tempdata, 0, length - 1, &counts[8], &counts[9]);
    	cout<<"M_Com: "<<counts[1]<<"\tM_Mov: "<<counts[2]<<"\tSM_Com: "<<counts[6]<<"\tSM_Mov: "<<counts[7]<<endl;
    	cout<<"Q_Com: "<<counts[3]<<"\tQ_Mov: "<<counts[4]<<"\tSQ_Com: "<<counts[8]<<"\tSQ_Mov: "<<counts[9]<<endl;
    	//int finalcounts[10];
    	//finalcounts[0,1,2,3,4,5,6,7,8,9]= counts[0,1,2,3,4,5,6,7,8,9];
}
int main()
{
    int data[100], tempdata500[50], tempdata100[10]; 
    int Data100[]={0,0,0,0,0,0,0,0,0,0};
	int Data500[]={0,0,0,0,0,0,0,0,0,0};
	int Data1000[]={0,0,0,0,0,0,0,0,0,0};
	GenerateRandomNumbers(data, 100);
	CopyArray(data, tempdata500, 50);
	CopyArray(data, tempdata100, 10);
	cout<<"Generated random numbers"<<endl;
    	PrintData(tempdata100, 10);
	cout<<"1000"<<endl;
	SortData(Data1000, data, 100);
	cout<<"500"<<endl;
    	SortData(Data500, tempdata500, 50);
	cout<<"100"<<endl;
    	SortData(Data100, tempdata100, 10);
	
    	
    	double MergeCompare100 = Data100[1];
	double QuickCompare100 = Data100[3];
		
    	double MergeMove100 = Data100[2];
	double QuickMove100 = Data100[4];
	
	double CompareRatio100 = MergeCompare100/QuickCompare100;
	double MovesRatio100 = MergeMove100/QuickMove100;
	
    	cout<<setprecision(1)<<fixed;
	cout<<endl<<endl;
	cout<<"NUMBER\t\tMERGE SORT\tQUICK SORT\tRATIO"<<endl<<endl;
	cout<<"COMPARE\t\t"<<endl;
	cout<<"100\t\t"<<Data100[1]<<"\t\t"<<Data100[3]<<"\t\t"<<CompareRatio100<<endl;
	cout<<endl<<"MOVES\t\t"<<endl;
    	cout<<"100\t\t"<<Data100[2]<<"\t\t"<<Data100[4]<<"\t\t"<<MovesRatio100<<endl;

	getch();
    return 0;
}

