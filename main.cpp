#include <iostream>
#include <vector>
#include <random>
using namespace std;

struct stats {
	size_t comparison_count = 0;
	size_t copy_count = 0;
};

template<typename T>
vector<T> create_sort_vector(int size)
{
	vector<T> arr(size);
	for (int i = 0; i < size; i++)
	{
		arr[i] = i-3;

	}
	return arr;
}
template<typename T>
vector<T> create_back_sort_vector(int size)
{
	vector<T> arr(size);
	T data = (T) 1000
	for (int i = 0; i < size; i++)
	{
		arr[i] = data - 7;
		data = data - 7;
	}
	return arr;
}

template<typename T>
vector<T> create_anti_sort_vector(int size)
{
	srand(time(NULL));
	vector<T> arr(size);
		for (int i = 0; i < size; i++)
		{
			arr[i] = -50 + rand() % 100;
		}
	return arr;
}

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
stats comb_sorting(typename vector<T> ::iterator begin, typename vector<T> ::iterator end, int size)
{
	stats count;
	int step = size;
	bool is_swap = true;
	while (step > 1 || is_swap)
	{ 
		step = (int)(step / 1.247);
		is_swap = false;
		for (auto i = begin; i < (end - step); i++)
		{
			if (*i > *(i + step))
			{
				is_swap = true;
				swap(*i, *(i + step));
				count.copy_count++;
			}
			count.comparison_count++;
		}

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
	vector<int> arr = create_anti_sort_vector<int>(10);
	print_array(arr);
	typename vector<int>::iterator  pt = arr.end();
	//bubble_sorting<int>(arr.begin(), arr.end());
	//shell_sorting<int>(arr.begin(), arr.end(), arr.size());
	comb_sorting<int>(arr.begin(), arr.end(), arr.size());
	print_array(arr);
	system("pause");

	return 0;
}