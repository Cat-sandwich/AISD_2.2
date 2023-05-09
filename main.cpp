#include <iostream>
#include <vector>
#include <random>
using namespace std;

struct stats {
	size_t comparison_count = 0;
	size_t copy_count = 0;
};

template<typename T>
stats bubble_sorting(typename vector<T> :: iterator begin, typename vector<T> ::iterator end)
{
	stats count;
	for (auto i = begin; i != (end - (T)1); i++)
	{
		for (auto j = begin; j != (end - (T)1); j++)
		{
			if (*j > *(j + 1))
			{
				swap(*j, *(j + 1));
				count.copy_count++;

			}
			count.comparison_count++;
		}
	}
	return count;
}

template<typename T>
stats shell_sorting(typename vector<T> ::iterator begin, typename vector<T> ::iterator end, int size)
{
	stats count;
	int d = size/2;
	while (d > 0)
	{
		for (auto i = begin  ; i != end - (T)d; i++)
		{
			auto j = i;
			do
			{
				if (*j > *(j + d))
				{
					swap(*j, *(j + d));
					count.copy_count++;
				}
				if (j != begin)
					j -= 1;
				count.comparison_count++;
			} while (j != begin);
			
		}
		d = d / 2;
	}
	return count;
}

template<typename T>
void print_array(const vector<T>& arr)
{
	for (int i = 0; i <arr.size(); i++)
	{
		cout << arr[i]<< " , ";

	}
	cout << endl;
}
int main()
{
	srand(time(NULL));
	int N = 10;
	vector<int> arr(N);
	for (int i = 0; i < N; i++) 
	{
		arr[i] = rand() % 100;
		
	}
	print_array(arr);
	typename vector<int>::iterator  pt = arr.end();
	//bubble_sorting<int>(arr.begin(), arr.end());
	shell_sorting<int>(arr.begin(), arr.end(), arr.size());
	print_array(arr);
	system("pause");

	return 0;
}