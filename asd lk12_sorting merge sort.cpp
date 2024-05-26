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

void merge(int *data, int left, int mid, int right)
{
	int i, j, k;
	int n1 = mid - left + 1;
	int n2 =  right - mid;

	int *L = new int[n1], *R = new int[n2];

	for (i = 0; i < n1; i++)
		L[i] = data[left + i];
	for (j = 0; j < n2; j++)
		R[j] = data[mid + 1+ j];

	i = 0;
	j = 0;
	k = left;
	while (i < n1 && j < n2)
	{
		if (L[i] <= R[j])
		{
			data[k] = L[i];
			i++;
		}
		else
		{
			data[k] = R[j];
			j++;
		}
		k++;
	}

	while (i < n1)
	{
		data[k] = L[i];
		i++;
		k++;
	}

	while (j < n2)
	{
		data[k] = R[j];
		j++;
		k++;
	}
	delete[] L;
	delete[] R;
}

void sort(int *data, int left, int right)
{
	if (left < right)
	{
		int mid = left+(right-left)/2;

		sort(data, left, mid);
		sort(data, mid+1, right);

		merge(data, left, mid, right);
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
