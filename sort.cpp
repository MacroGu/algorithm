/*
 * all sort element is integer
 * create by: Macro Gu 
 * */

#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <ctime>
#include <chrono>
#include <random>
#include <algorithm>
#include <string.h>
#include <stdint.h>

// there are some sort algoritm left, but I do not want do that
// for example: HeapSort, RadixSort...

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


// merge Sort
void Merge(int* a, int low, int high, int mid)
{
	// now we have low to mid and mid + 1 to high sorted array
	// merge them to one array
	int i = low;
	int j = mid + 1;
	int k = 0;
	int* temp = new int[high - low + 1];

	while(i <= mid && j <= high)
	{
		if (a[i] < a[j])
		{
			temp[k] = a[i];
			i++;
		}
		else
		{
			temp[k] = a[j];
			j++;
		}

		k++;
	}	


	while(i <= mid)
	{
		temp[k] = a[i];
		k++;
		i++;
	}

	while(j <= high)
	{
		temp[k] = a[j];
		j++;
		k++;
	}


	// copy
	for(k = low; k <= high; k++)
	{
		a[k] = temp[k - low];
	}
}

void mergeSort(int* a, int lower, int upper)
{
	if (lower >= upper) return;

	int mid = (lower + upper) / 2;
	mergeSort(a, lower, mid);
	mergeSort(a, mid + 1, upper);
	Merge(a, lower, upper, mid);
}


// quickSort
void quickSort(int* a, int left, int right)
{
	int i = left, j = right;
	int tmp;
	int pivot = a[(left + right) / 2];
	while (i <= j)
	{
		while(a[i] < pivot)
		{
			i++;
		}
		while(a[j] > pivot)
		{
			j--;
		}

		if (i <= j)
		{
			tmp = a[i];
			a[i] = a[j];
			a[j] = tmp;
			i++;
			j--;
		}
	}

	if (j > left)
	{
		quickSort(a, left, j);
	}
	if (i < right)
	{
		quickSort(a, i , right);
	}
}

// produce random element
int* initRandomNums(size_t arrSize, size_t range)
{
	std::default_random_engine generator;
	std::uniform_int_distribution<int> distribution(-range, range);
	int* randomArray = new int[arrSize];
	size_t arrayPos = 0;
	while(arrSize > arrayPos)
	{
		randomArray[arrayPos] = distribution(generator);
		++arrayPos;
	}

	return randomArray;
}


bool compareTwoSameLengthArray(int* a, int* b, size_t length)
{
	for (int i = 0; i < length; i++)
	{
		if (a[i] != b[i])
			return false;
	}

	return true;
}

int main()
{
	size_t arraySize = 0;
	size_t range = 0;
	std::vector<std::string> showSort;
	// get config data
	std::string line;	
	std::ifstream myfile("config.conf");
	if (myfile.is_open())
	{
		uint8_t pos = 0;
		while(getline(myfile,line))
		{
			if (1 == pos)
			{
				arraySize = stoi(line);
			}
			else if (pos > 4)
			{
				showSort.push_back(line);
			}

			pos++;
			std::cout << line << std::endl;
		}

		myfile.close();
	}
	else
	{
		std::cout << "unable to open file" << std::endl;
		return 0;
	}

	int* sourceArray = initRandomNums(arraySize, range);
	std::cout << std::endl;
	std::chrono::time_point<std::chrono::system_clock> start, end;
	for_each(showSort.cbegin(), showSort.cend(), [&](const std::string & s){
			if (s.compare("merge") == 0)
			{
				int* mergeSortData = new int[arraySize];
				memcpy(mergeSortData, sourceArray, arraySize * sizeof(int));
				start = std::chrono::system_clock::now();
				mergeSort(mergeSortData, 0, arraySize - 1);
				end = std::chrono::system_clock::now();
				std::cout << std::endl << "merge Sort cost time: " << 
				((std::chrono::duration<double, std::milli>)(end - start)).count() 
				<< " ms" << std::endl;;
				std::cout << std::endl;
			}
			else if (s.compare("quick") == 0)
			{
				int* quickSortData = new int[arraySize];
				memcpy(quickSortData, sourceArray, arraySize * sizeof(int));
				start = std::chrono::system_clock::now();
				quickSort(quickSortData, 0, arraySize - 1);
				end = std::chrono::system_clock::now();
				std::cout << std::endl << "quick Sort cost time: " << 
				((std::chrono::duration<double, std::milli>)(end - start)).count() 
				<< " ms" << std::endl;;
				std::cout << std::endl;
			}
			else if (s.compare("bubble") == 0)
			{
				int* bubbleSortData = new int[arraySize];
				memcpy(bubbleSortData, sourceArray, arraySize * sizeof(int));
				start = std::chrono::system_clock::now();
				bubbleSort(bubbleSortData, arraySize);
				end = std::chrono::system_clock::now();
				std::cout << std::endl << "bubble Sort cost time: " << 
				((std::chrono::duration<double, std::milli>)(end - start)).count() 
				<< " ms" << std::endl;
				std::cout << std::endl;
			}
			else if (s.compare("selection") == 0)
			{

				int* selectionSortData = new int[arraySize];
				memcpy(selectionSortData, sourceArray, arraySize * sizeof(int));
				start = std::chrono::system_clock::now();
				selectionSort(selectionSortData, arraySize);
				end = std::chrono::system_clock::now();
				std::cout << std::endl << "selection Sort cost time: " << 
					((std::chrono::duration<double, std::milli>)(end - start)).count() 
					<< " ms" << std::endl;;
				std::cout << std::endl;

			}
			else if (s.compare("insertion") == 0)
			{

				int* insertionSortData = new int[arraySize];
				memcpy(insertionSortData, sourceArray, arraySize * sizeof(int));
				start = std::chrono::system_clock::now();
				insertionSort(insertionSortData, arraySize);
				end = std::chrono::system_clock::now();
				std::cout << std::endl << "insertion Sort cost time: " << 
					((std::chrono::duration<double, std::milli>)(end - start)).count() 
					<< " ms" << std::endl;;
				std::cout << std::endl;
			}
			else 
			{
				std::cout << "conf errro " << s ;
			}
	});


	return 0;
}
