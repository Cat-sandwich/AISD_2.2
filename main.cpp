#include <iostream>
#include <vector>
#include <random>
#include <chrono>
#include <thread>
#include <fstream>
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
		arr.push_back(i - 3);

	}
	return arr;
}
template<typename T>
vector<T> create_back_sort_vector(int size)
{
	vector<T> arr(size);
	T data = (T)1000;
	for (int i = 0; i < size; i++)
	{
		arr.push_bsck(data - 7);
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
			arr.push_back( - 50 + rand() % 100);
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

template<typename T>
void mean_time(int ident)
{
	int size = 1000;

	while (size < 1000)
	{
		chrono::duration<float> result_buble(0), result_shell(0), result_comb(0);
		fstream file_buble, file_shell, file_comb;
		file_buble.open("mean_time_buble.txt", ios::app);
		file_shell.open("mean_time_shell.txt", ios::app);
		file_comb.open("mean_time_comb.txt", ios::app);
		long int mean_copy_buble = 0, mean_copy_shell = 0, mean_copy_comb = 0;
		long int mean_comp_buble = 0, mean_comp_shell = 0, mean_comp_comb = 0;

		for (int i = 0; i < 100; i++)
		{
			vector<T> arr_1 = create_anti_sort_vector<T>(size);
			vector<T> arr_2 = create_anti_sort_vector<T>(size);
			vector<T> arr_3 = create_anti_sort_vector<T>(size);
			stats res_buble, res_shell, res_comb;

			auto start_buble = chrono::high_resolution_clock::now();
			res_buble = bubble_sorting<T>(arr_1.begin(), arr_1.end());
			auto end_buble = chrono::high_resolution_clock::now();

			result_buble = start_buble - end_buble;

			auto start_shell = chrono::high_resolution_clock::now();
			res_shell = shell_sorting<T>(arr_2.begin(), arr_2.end(), arr_2.size());
			auto end_shell = chrono::high_resolution_clock::now();

			result_shell = start_shell - end_shell;

			auto start_comb = chrono::high_resolution_clock::now();
			res_comb = comb_sorting<T>(arr_3.begin(), arr_3.end(), arr_3.size());
			auto end_comb = chrono::high_resolution_clock::now();

			result_comb = start_comb - end_comb;

			mean_comp_shell += res_shell.comparison_count;
			mean_copy_shell += res_shell.copy_count;

			mean_comp_buble += res_buble.comparison_count;
			mean_copy_buble += res_buble.copy_count;

			mean_comp_comb += res_comb.comparison_count;
			mean_copy_comb += res_comb.copy_count;
		}
		file_buble << "Число эл-тов : " << size << endl;
		file_buble << "Число сравнений : " << mean_comp_buble / 100 << endl;
		file_buble << "Число копирований : " << mean_copy_buble / 100 << endl;
		file_buble << "Среднее время : " << result_buble.count() / 100 << endl;

		file_shell << "Число эл-тов : " << size << endl;
		file_shell << "Число сравнений : " << mean_comp_shell / 100 << endl;
		file_shell << "Число копирований : " << mean_copy_shell / 100 << endl;
		file_shell << "Среднее время : " << result_shell.count() / 100 << endl;

		file_comb << "Число эл-тов : " << size << endl;
		file_comb << "Число сравнений : " << mean_comp_comb / 100 << endl;
		file_comb << "Число копирований : " << mean_copy_comb / 100 << endl;
		file_comb << "Среднее время : " << result_comb.count() / 100 << endl;
		
		if (size < 10000)
			size += 1000;
		else
		{
			if (size == 10000)
				size = 25000;
			else
				size += 25000;
		}
	}
	system("pause");
}
int main()
{
	vector<int> arr = create_anti_sort_vector<int>(10);
	print_array(arr);
	typename vector<int>::iterator  pt = arr.end();
	//bubble_sorting<int>(arr.begin(), arr.end());
	//shell_sorting<int>(arr.begin(), arr.end(), arr.size());
	comb_sorting<int>(arr.begin(), arr.end(), arr.size());
	mean_time<int>(1);
	print_array(arr);
	system("pause");

	return 0;
}