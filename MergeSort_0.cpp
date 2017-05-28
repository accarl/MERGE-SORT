#include<iostream>
#include<cstdlib>
#include<time.h>
#include<conio.h>
#include<iomanip> //precision
#include<chrono>// for elapsed time
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

//cout<<"Testing"<<endl;


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

void SortData(int counts[], int data[], double time[], int length)
{
	int tempdata[length], S_data[length], S_tempdata[length], tempdata500[length], tempdata100[length];
	CopyArray(data, tempdata, length);
	
    cout<<"Sorting...Merge"<<endl;
	auto t1 = chrono::steady_clock::now();//clock t1 starts now
	
	MergeSort(data, length, 0, length - 1, &counts[0], &counts[1],&counts[2]);
	 auto t2 = chrono::steady_clock::now();//clock t1 ends
    time[0] = chrono::duration <double, micro> (t2 - t1).count();// difference of mergesort_random
    //auto diff = t2 -t1;
    //cout<<"Merge Sort Elapsed Time: " <<chrono::duration <double, nano> (diff).count() << " ns" << endl;
	cout<<"Random - Merge Sort Time: "<< time[0]<<endl;
    
    if (length == 100){
         PrintData(data, length);
    }
    auto t3 = chrono::steady_clock::now();//clock t3 starts now
    
    QuickSort(tempdata, 0, length - 1, &counts[3], &counts[4]);
    auto t4 = chrono::steady_clock::now();//clock stops
    cout<<"Sorting...Quick"<<endl;
         
    time[1] = chrono::duration <double, micro> (t4 - t3).count();// difference of quicksort_random
    cout<<"Random - Quick Sort Time: "<<time[1]<<endl;
    //auto diff1 = t2 - t1;
    //cout<<"Quick Sort Elapsed Time: " <<chrono::duration <double, milli> (diff1).count() << " ms" << endl;
	//cout<<"Elapsed Time: " <<chrono::duration <double, milli> (x).count() << " ms" << endl;
    if (length == 100){
         PrintData(tempdata, length);
    }
    SwapArray(data, S_data, length);
    CopyArray(S_data, S_tempdata, length);
    //cout<<"Swapped_data"<<endl;
    //PrintData(S_data, length);
    auto t5 = chrono::steady_clock::now();
    MergeSort(S_data, length, 0, length - 1, &counts[5], &counts[6],&counts[7]);
    auto t6 = chrono::steady_clock::now();
    time[2] = chrono::duration <double, micro> (t6 - t5).count(); //difference of mergesort_sorted
    cout<<"Semi Sorted - Merge Sort Time: "<<time[2]<<endl;
    auto t7 = chrono::steady_clock::now();
    QuickSort(S_tempdata, 0, length - 1, &counts[8], &counts[9]);
    auto t8 = chrono::steady_clock::now();
    time[3]= chrono::duration <double, micro> (t8 - t7).count(); //difference of quicksort_sorted
    cout<<"Semi Sorted - Quick Sort Time: "<<time[3]<<endl;
}

void PrintCounts(int counts[], int length, int x, int y, bool IsDuration)
{
    double MergeCom = counts[x];
	double QuickCom = counts[y];
	double ComRatio = MergeCom/QuickCom;
	if(IsDuration){
    	cout<<length<<"\t\t"<<counts[x]<<"\t\t"<<counts[y]<<"\t\t"<<ComRatio<<endl;
	}
	else{
			cout<<length<<"\t\t"<<counts[x]<<"\t\t"<<counts[y]<<endl;
	}
    x=0;
    y=0;
}

void PrintResult(int Data100[], int Data500[], int Data1000[], int x, int y, bool IsDuration)
{
    PrintCounts(Data100, 100, x, y,IsDuration);
	PrintCounts(Data500, 500, x, y,IsDuration);
	PrintCounts(Data1000, 1000, x, y,IsDuration);
	
}

	
void PrintCounts2(double counts[], double length, int x, int y)
{
    double MergeCom = counts[x];
	double QuickCom = counts[y];
	double ComRatio = MergeCom/QuickCom;
	
	
			cout<<length<<"\t\t"<<counts[x]<<"\t\t"<<counts[y]<<endl;
	
    x=0;
    y=0;
}

void PrintResult2(double time100[], double time500[], double time1000[], double x, double y)
{
    PrintCounts2(time100, 100, x, y);
	PrintCounts2(time500, 500, x, y);
	PrintCounts2(time1000, 1000, x, y);
	
}

int main()
{
    int data[1000], tempdata500[500], tempdata100[100]; 
    int Data100[]={0,0,0,0,0,0,0,0,0,0};
    //Data100[0] - DivideCount(MergeSort_RandomData)
    //Data100[1] - CompareCount(MergeSort_RandomData)
    //Data100[2] - MoveCount(MergeSort_RandomData)
    //Data100[3] - CompareCount(QuickSort_RandomData)
    //Data100[4] - MoveCount(QuickSort_RandomData)
    //Data100[5] - DivideCount(MergeSort_SortedData)
    //Data100[6] - CampareCount(MergeSort_SortedData)
    //Data100[7] - MoveCount(MergeSort_SortedData)
    //Data100[8] - CompareCount(QuickSort_SortedData)
    //Data100[9] - MoveCount(QuickSort_SortedData)
    
	int Data500[]={0,0,0,0,0,0,0,0,0,0};
	
	int Data1000[]={0,0,0,0,0,0,0,0,0,0};
	
	double time100[]={0,0,0,0};
	double time500[]={0,0,0,0};
	double time1000[]={0,0,0,0};
	
	
	GenerateRandomNumbers(data, 1000);
	CopyArray(data, tempdata500, 500);
	CopyArray(data, tempdata100, 100);
	cout<<"Generated random numbers"<<endl;
    PrintData(tempdata100, 100);
    
	SortData(Data1000, data, time1000, 1000);
	//cout<<"Test1"<<endl;
    SortData(Data500, tempdata500,time500, 500);
    //cout<<"Test2"<<endl;
    SortData(Data100, tempdata100,time100, 100);
    //cout<<"Test3"<<endl;
    cout<<setprecision(1)<<fixed;
	cout<<"NUMBER\t\tMERGE SORT\tQUICK SORT\tRATIO"<<endl;
	cout<<endl<<"-----------compare counts using random data-----------"<<endl;
    PrintResult(Data100, Data500, Data1000, 1,3,true);
	cout<<endl<<"-------------move counts using random data------------"<<endl;
    PrintResult(Data100, Data500, Data1000, 2,4,true);
	cout<<endl<<"-----------compare counts using sorted data-----------"<<endl;
    PrintResult(Data100, Data500, Data1000, 6,8,true);
	cout<<endl<<"-------------move counts using sorted data------------"<<endl;
    PrintResult(Data100, Data500, Data1000, 7,9,true);
    cout<<endl;
    
    cout<<endl<<"-----------------Elapsed Time Comparison-----------------"<<endl<<endl;
    cout<<"Number\t\tRandom\t\tSemi-Sorted"<<endl;
    cout<<endl<<"-------------Merge Sort------------"<<endl;
    PrintResult2(time100, time500, time1000,0,2);
    cout<<endl<<"-------------Quick Sort------------"<<endl;
    PrintResult2(time100, time500, time1000,1,3);
    
    
	getch();
    return 0;
}
