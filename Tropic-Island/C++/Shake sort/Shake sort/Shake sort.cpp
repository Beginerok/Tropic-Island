// Shake sort.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <vector>
#include <ctime>

void filling(std::vector<int> *arr) {
	for (int i = 0; i < (*arr).size(); i++) {
		(*arr)[i] = (int)(rand() % 100);
		std::cout<<(*arr)[i]<< " ";
	}
	std::cout << std::endl;
}
void shakerSort(std::vector<int>*arr) {
	int buff;
	int left = 0;
	int right = (*arr).size() - 1;
	do {
		for (int i = left; i < right; i++) {
			if ((*arr)[i] > (*arr)[i + 1]) {
				buff = (*arr)[i];
				(*arr)[i] = (*arr)[i + 1];
				(*arr)[i + 1] = buff;
			}
		}
		right--;
		for (int i = right; i > left; i--) {
			if ((*arr)[i] < (*arr)[i - 1]) {
				buff = (*arr)[i];
				(*arr)[i] = (*arr)[i - 1];
				(*arr)[i - 1] = buff;
			}
		}
		left++;
	} while (left < right);
}

int main()
{
	const int N = 20;
	std::vector<int> arr;
	for (int i = 0; i < N; i++)
		arr.push_back(0);
	srand(time(0));
	filling(&arr);
	shakerSort(&arr); 
	for (int i = 0; i < arr.size(); i++) {
		std::cout << arr[i] << " ";
	}
	arr.clear();
	std::cin.ignore();
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
