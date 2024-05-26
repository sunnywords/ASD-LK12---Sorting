#include <iostream>
#include <cstdlib>
#include <ctime>
#include <exception>
#include <stack>

using namespace std;

int *generate_random_int(int n)
{
	int *data = new int[n];
	for (int i = 0; i < n; i++)
	{
		data[i] = rand();
	}
	return data;
}

bool is_sorted(int *data, int n)
{
	for (int i = 1; i < n; i++)
	{
		if (data[i - 1] > data[i])
		{
			return false;
		}
	}
	return true;
}

void swap(int* a, int* b) 
{ 
	int t = *a; 
	*a = *b; 
	*b = t; 
} 

int partition(int arr[], int low, int high) 
{ 
	int pivot = arr[high]; 
	int i = (low - 1); 

	for (int j = low; j <= high - 1; j++) 
	{ 
		if (arr[j] < pivot) 
		{ 
			i++; 
			swap(&arr[i], &arr[j]); 
		} 
	} 
	swap(&arr[i + 1], &arr[high]); 
	return (i + 1); 
} 

void sort(int arr[], int n) 
{ 
	stack<int> stack; 

	stack.push(0); 
	stack.push(n - 1); 

	while (!stack.empty()) 
	{ 
		int h = stack.top(); 
		stack.pop(); 
		int l = stack.top(); 
		stack.pop(); 

		int p = partition(arr, l, h); 

		if (p - 1 > l) 
		{ 
			stack.push(l); 
			stack.push(p - 1); 
		} 

		if (p + 1 < h) 
		{ 
			stack.push(p + 1); 
			stack.push(h); 
		} 
	} 
} 

int main()
{
	int num_of_experiments = 100;
	int *data;
	int n;

	// DEBUG
	// The program will stop if the sorting is incorrect
	n = 100;
	data = generate_random_int(n);
	sort(data, n);
	if (!is_sorted(data, n))
	{
		cerr << "Sorting function ERROR." << endl;
		throw exception();
	}
	
	// EXPERIMENTS
	cout << "data, time (ms)\n";
	cout << ".............. \n";
	for (int i = 1; i <= num_of_experiments; i++)
	{
		n = i * 1000;
		data = generate_random_int(n);

		clock_t start = clock();
		sort(data, n);
		clock_t stop = clock();
		double duration = 1000.0 * (stop - start) / CLOCKS_PER_SEC;
		cout << n << ", " << duration << "\n";
		delete data;
	}
	return 0;
}
