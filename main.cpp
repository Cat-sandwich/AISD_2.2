#include <iostream>
#include <vector>
#include <random>
#include <chrono>
#include <thread>
#include <fstream>
#include <conio.h>
#include <Windows.h>
#include <string>
using namespace std;

struct stats {
	size_t comparison_count = 0;
	size_t copy_count = 0;
};

int get_key()
{
	int key = _getch();
	if ((key == 0) || (key == 224)) key = _getch();
	return key;
}

template<typename T>
vector<T> create_sort_vector(int size)
{
	vector<T> arr(0);
	for (int i = 0; i < size; i++)
	{
		arr.push_back((T)((i + 1)/3));

	}
	return arr;
}
template<typename T>
vector<T> create_back_sort_vector(int size)
{
	vector<T> arr(0);
	T data = (T)1000;
	for (int i = 0; i < size; i++)
	{
		arr.push_back((T)(data - 7)/4);
		data = data - 7;
	}
	return arr;
}

template<typename T>
vector<T> create_anti_sort_vector(int size)
{
	srand(time(NULL));
	vector<T> arr(0);
		for (int i = 0; i < size; i++)
		{
			arr.push_back( (T)( - 50 + rand() % 150)/2);
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
void mean_time()
{
	int size = 8000;
	fstream file_buble, file_shell, file_comb;
	file_buble.open("mean_time_buble.txt", ios::app);
	file_shell.open("mean_time_shell.txt", ios::app);
	file_comb.open("mean_time_comb.txt", ios::app);

	while (size < 100001)
	{
		chrono::duration<float> result_buble(0), result_shell(0), result_comb(0);
		
		long long mean_copy_buble = 0, mean_copy_shell = 0, mean_copy_comb = 0;
		long long mean_comp_buble = 0, mean_comp_shell = 0, mean_comp_comb = 0;

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
			//res_shell = shell_sorting<T>(arr_2.begin(), arr_2.end(), arr_2.size());
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
		file_buble << "Среднее время : " << -result_buble.count() / 100 << endl;
		file_buble << endl;

		file_shell << "Число эл-тов : " << size << endl;
		file_shell << "Число сравнений : " << mean_comp_shell / 100 << endl;
		file_shell << "Число копирований : " << mean_copy_shell / 100 << endl;
		file_shell << "Среднее время : " << -result_shell.count() / 100 << endl;
		file_shell << endl;

		file_comb << "Число эл-тов : " << size << endl;
		file_comb << "Число сравнений : " << mean_comp_comb / 100 << endl;
		file_comb << "Число копирований : " << mean_copy_comb / 100 << endl;
		file_comb << "Среднее время : " << -result_comb.count() / 100 << endl;
		file_comb << endl;
		
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
	file_buble.close();
	file_comb.close();
	file_shell.close();
	cout << "mean_time end" << endl;
}

template<typename T>
void sorted_time()
{
	int size = 100000;
	fstream file_buble, file_shell, file_comb;
	file_buble.open("sorted_time_buble.txt", ios::app);
	file_shell.open("sorted_time_shell.txt", ios::app);
	file_comb.open("sorted_time_comb.txt", ios::app);

	while (size < 100001)
	{
		chrono::duration<float> result_buble(0), result_shell(0), result_comb(0);

		long long mean_copy_buble = 0, mean_copy_shell = 0, mean_copy_comb = 0;
		long long mean_comp_buble = 0, mean_comp_shell = 0, mean_comp_comb = 0;

		vector<T> arr_1 = create_sort_vector<T>(size);
		vector<T> arr_2 = create_sort_vector<T>(size);
		vector<T> arr_3 = create_sort_vector<T>(size);

		stats res_buble, res_shell, res_comb;

		auto start_buble = chrono::high_resolution_clock::now();
		res_buble = bubble_sorting<T>(arr_1.begin(), arr_1.end());
		auto end_buble = chrono::high_resolution_clock::now();

		result_buble = start_buble - end_buble;

		auto start_shell = chrono::high_resolution_clock::now();
		//res_shell = shell_sorting<T>(arr_2.begin(), arr_2.end(), arr_2.size());
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
		
		file_buble << "Число эл-тов : " << size << endl;
		file_buble << "Число сравнений : " << mean_comp_buble << endl;
		file_buble << "Число копирований : " << mean_copy_buble << endl;
		file_buble << "Среднее время : " << -result_buble.count()  << endl;
		file_buble << endl;

		file_shell << "Число эл-тов : " << size << endl;
		file_shell << "Число сравнений : " << mean_comp_shell << endl;
		file_shell << "Число копирований : " << mean_copy_shell  << endl;
		file_shell << "Среднее время : " << -result_shell.count()  << endl;
		file_shell << endl;

		file_comb << "Число эл-тов : " << size << endl;
		file_comb << "Число сравнений : " << mean_comp_comb  << endl;
		file_comb << "Число копирований : " << mean_copy_comb  << endl;
		file_comb << "Среднее время : " << -result_comb.count()  << endl;
		file_comb << endl;

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
	file_buble.close();
	file_comb.close();
	file_shell.close();
	cout << "sorted end" << endl;
}
template<typename T>
void back_sorted_time()
{
	int size = 50000;
	fstream file_buble, file_shell, file_comb;
	file_buble.open("back_sorted_buble.txt", ios::app);
	file_shell.open("back_sorted_shell.txt", ios::app);
	file_comb.open("back_sorted_comb.txt", ios::app);

	while (size < 100001)
	{
		chrono::duration<float> result_buble(0), result_shell(0), result_comb(0);

		long long mean_copy_buble = 0, mean_copy_shell = 0, mean_copy_comb = 0;
		long long mean_comp_buble = 0, mean_comp_shell = 0, mean_comp_comb = 0;

		vector<T> arr_1 = create_anti_sort_vector<T>(size);
		vector<T> arr_2 = create_anti_sort_vector<T>(size);
		vector<T> arr_3 = create_anti_sort_vector<T>(size);

		stats res_buble, res_shell, res_comb;

		auto start_buble = chrono::high_resolution_clock::now();
		res_buble = bubble_sorting<T>(arr_1.begin(), arr_1.end());
		auto end_buble = chrono::high_resolution_clock::now();

		result_buble = start_buble - end_buble;

		auto start_shell = chrono::high_resolution_clock::now();
		//res_shell = shell_sorting<T>(arr_2.begin(), arr_2.end(), arr_2.size());
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

		file_buble << "Число эл-тов : " << size << endl;
		file_buble << "Число сравнений : " << mean_comp_buble << endl;
		file_buble << "Число копирований : " << mean_copy_buble << endl;
		file_buble << "Среднее время : " << -result_buble.count() << endl;
		file_buble << endl;

		file_shell << "Число эл-тов : " << size << endl;
		file_shell << "Число сравнений : " << mean_comp_shell << endl;
		file_shell << "Число копирований : " << mean_copy_shell << endl;
		file_shell << "Среднее время : " << -result_shell.count() << endl;
		file_shell << endl;

		file_comb << "Число эл-тов : " << size << endl;
		file_comb << "Число сравнений : " << mean_comp_comb << endl;
		file_comb << "Число копирований : " << mean_copy_comb << endl;
		file_comb << "Среднее время : " << -result_comb.count() << endl;
		file_comb << endl;

		if (size < 10000)
			size += 1000;
		else
		{
			if (size == 10000 )
				size = 25000;
			else if( size == 25000)
				size = 50000;
			else if (size == 50000)
				size = 100000;
		}

	}
	file_buble.close();
	file_comb.close();
	file_shell.close();
	cout << "back end" << endl;
}

int check_int()
{
	int number = -1;

	while (number <= 0)
	{
		while (!(cin >> number) || (cin.peek() != '\n'))
		{
			cin.clear();
			while (cin.get() != '\n');
			cout << "Введите корректное значение...\n";
		}
		if(number <= 0)
		{
			cin.clear();
			while (cin.get() != '\n');
			cout << "Введите корректное значение...\n";
		}
	}

	return number;
}
template<typename T>
void menu_1()
{
	bool check = 1;
	int size = 0;
	vector<T> arr(0);

	while (check)
	{
		system("cls");
		cout << " 1 - провести все тесты" << endl;
		cout << " 2 - отсортировать массив на N элементов сортировкой пузырьком" << endl;
		cout << " 3 - отсортировать массив на N элементов сортировкой шелла" << endl;
		cout << " 4 - отсортировать массив на N элементов сортировкой расческа" << endl;
		cout << " 0 - завершение работы" << endl;
		int key = get_key();
		switch (key)
		{
		case 48:
			check = 0;
			break;
		case 49:
			mean_time<int>();
			sorted_time<int>();
			back_sorted_time<int>();
			break;
		case 50:
			cout << "Введите размерость массива: ";
			size = check_int();
			arr = create_anti_sort_vector<T>(size);
			print_array<T>(arr);
			bubble_sorting<T>(arr.begin(), arr.end());
			print_array<T>(arr);
			system("pause");
			break;
		case 51:
			cout << "Введите размерость массива: ";
			size = check_int();
			arr = create_anti_sort_vector<T>(size);
			print_array<T>(arr);
			shell_sorting<T>(arr.begin(), arr.end(), arr.size());
			print_array<T>(arr);
			system("pause");
			break;
		case 52:
			cout << "Введите размерость массива: ";
			size = check_int();
			arr = create_anti_sort_vector<T>(size);
			print_array<T>(arr);
			comb_sorting<T>(arr.begin(), arr.end(), arr.size());
			print_array<T>(arr);
			system("pause");
			break;
		default:
			break;
		}

	}

}
int main()
{
	setlocale(LC_ALL, "RUS");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	bool check = 1;
	int size = 0;

	while (check)
	{
		system("cls");
		cout << " Выберите тип:" << endl;
		cout << " 1 - int" << endl;
		cout << " 2 - float" << endl;
		cout << " 3 - double" << endl;
		cout << " 0 - завершить работу" << endl;
		int key = get_key();
		switch (key)
		{
		case 48:
			check = 0;
			break;
		case 49:
			menu_1<int>();
			break;
		case 50:
			menu_1<float>();
			break;
		case 51:
			menu_1<double>();
			break;
		default:
			break;
		}

	}
	
	system("pause");

	return 0;
}