﻿// HeapSortReally.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <vector>
#include <ctime>
void swap(std::vector<int> *v, int n, int m)
{
	int tmp = (*v)[n];
	(*v)[n] = (*v)[m];
	(*v)[m] = tmp;
	/*
	for (int i = 0; i < (*v).size(); i++)
	{
		std::cout << (*v)[i] << " ";
	}
	std::cout << std::endl;
	*/
}
int main()
{
	std::vector<int> arr;
	const int N = 20;
	srand(time(0));
	for (int i = 0; i < N; i++)
	{
		arr.push_back((int)rand() % 100);
		std::cout << arr[i] << " ";
	}
	std::cout << std::endl;
	for (int j = 0; j < N; j++)
	{
		for (int i = N / 2 - j/2; i > -1; i--)
		{
			if (2 * i + 2 <= N - 1-j)
			{
				if (arr[2 * i + 1] > arr[2 * i + 2])
				{
					if (arr[i] < arr[2 * i + 1])
					{
						swap(&arr, i, 2 * i + 1);
						//std::cout <<j<<" "<< i << " " << 2 * i + 1 << std::endl;
					}
				}
				else
					if (arr[i] < arr[2 * i + 2])
					{
						swap(&arr, i, 2 * i + 2);
						//std::cout <<j<<" "<< i << " " << 2 * i + 2 << std::endl;
					}
			}
			else
				if (2 * i + 1 <= N - 1-j)
					if (arr[i] < arr[2 * i + 1])
						swap(&arr, i, 2 * i + 1);
		}
		swap(&arr,0, N - 1 - j);
		//std::cout << j << " " << 0 << " " << N-1-j << std::endl;
	}
	for (int i = 0; i < N; i++)
	{
		std::cout << arr[i] << " ";
	}
	std::cout << std::endl;
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
