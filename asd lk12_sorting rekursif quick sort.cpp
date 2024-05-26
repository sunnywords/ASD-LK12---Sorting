#include <iostream>
#include <cstdlib>
#include <ctime>
#include <exception>

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

int partition (int *data, int low, int high)
{
	int pivot = data[high]; 
	int i = (low - 1); 

	for (int j = low; j <= high - 1; j++)
	{
		if (data[j] < pivot)
		{
			i++; 
			swap(data[i], data[j]);
		}
	}
	swap(data[i + 1], data[high]);
	return (i + 1);
}

void sort(int *data, int low, int high)
{
	if (low < high)
	{
		int pi = partition(data, low, high);

		sort(data, low, pi - 1);
		sort(data, pi + 1, high);
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
	sort(data, 0, n-1);
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
		sort(data, 0, n-1);
		clock_t stop = clock();
		double duration = 1000.0 * (stop - start) / CLOCKS_PER_SEC;
		cout << n << ", " << duration << "\n";
		delete data;
	}
	return 0;
}
