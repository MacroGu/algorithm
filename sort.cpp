/*
 * all sort element is integer
 * create by: Macro Gu 
 * */

#include <vector>
#include <iostream>
#include <ctime>
#include <chrono>
#include <random>
#include <algorithm>
#include <string.h>


// bubble Sort
void bubbleSort(int* V, int size_)
{
	int temp = 0;
	for (int i = 0; i < size_; i++)
	{
		for(int j = 0; j < size_ - i - 1; j++)
		{
			if (V[j] > V[j + 1])
			{
				temp = V[j+1];
				V[j+1] = V[j];
				V[j] = temp;
			}
		}
	}
}

// insertion Sort
void insertionSort(int* V, int size_)
{
	int j = 0;
	int temp = 0;
	for(int i = 1; i < size_; i++)
	{
		j = i;
		temp = V[i];
		while(j > 0 && temp < V[j-1])
		{
			V[j] = V[j-1];
			j--;
		}
		V[j] = temp;
	}
}


// selection Sort
void selectionSort(int* V, int size_)
{
	for(int i = 0; i < size_; i++)
	{
		int m = V[i];
		int nextMinPos = i;
		for(int j = i + 1; j < size_; j++)
		{
			if (V[j] < m)
			{
				m = V[j];
				nextMinPos = j;
			}
		}

		// exchange current data with the next min one
		int temp = V[i];
		V[i] = V[nextMinPos];
		V[nextMinPos] = temp;
	}

}


// produce random element
int* initRandomNums(size_t arrSize)
{
	std::default_random_engine generator;
	std::uniform_int_distribution<int> distribution(-10000, 10000);
	int* randomArray = new int[arrSize];
	size_t arrayPos = 0;
	while(arrSize > arrayPos)
	{
		randomArray[arrayPos] = distribution(generator);
		++arrayPos;
	}

	return randomArray;
}
	
int main()
{
	size_t arraySize = 1000;
	int* sourceArray = initRandomNums(arraySize);
	std::cout << "source data.... "<< std::endl;
	for(size_t i = 0; i < arraySize; i++)
	{
		std::cout << sourceArray[i] << ", ";
	}

	// copy need sort data
	int* insertionSortData = new int[arraySize];
	memcpy(insertionSortData, sourceArray, arraySize * sizeof(int));
	int* bubbleSortData = new int[arraySize];
	memcpy(bubbleSortData, sourceArray, arraySize * sizeof(int));
	int* selectionSortData = new int[arraySize];
	memcpy(selectionSortData, sourceArray, arraySize * sizeof(int));

	std::chrono::time_point<std::chrono::system_clock> start, end;
	start = std::chrono::system_clock::now();
	insertionSort(insertionSortData, arraySize);
	end = std::chrono::system_clock::now();
	std::cout << std::endl << "insertion Sort cost time: " << 
		((std::chrono::duration<double, std::milli>)(end - start)).count() 
		<< " ms" << std::endl;;


	start = std::chrono::system_clock::now();
	bubbleSort(bubbleSortData, arraySize);
	end = std::chrono::system_clock::now();
	std::cout << std::endl << "bubble Sort cost time: " << 
		((std::chrono::duration<double, std::milli>)(end - start)).count() 
		<< " ms" << std::endl;;


	start = std::chrono::system_clock::now();
	selectionSort(bubbleSortData, arraySize);
	end = std::chrono::system_clock::now();
	std::cout << std::endl << "selection Sort cost time: " << 
		((std::chrono::duration<double, std::milli>)(end - start)).count() 
		<< " ms" << std::endl;;
	

	return 0;
}
