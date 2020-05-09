// HeapSort.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <list>

int main()
{
	// quick sort
	std::list<int> list;
	const int N = 20;
	for (int i = 0; i < N; i++)
	{
		if (i % 2 == 0)
			list.push_back(N - i);
		else
			list.push_front(N - i);
	}
	for (std::list<int>::iterator it = list.begin(); it != list.end(); it++) {
		std::cout << (*it) << " ";
	}
	std::cout << std::endl;
	list.sort();
	for (std::list<int>::iterator it = list.begin(); it != list.end(); it++) {
		std::cout << (*it) << " ";
	}
	//quick sort end
	std::cout << std::endl;
	//sort greater
	list.sort(std::greater<int>());
	for (std::list<int>::iterator it = list.begin(); it != list.end(); it++) {
		std::cout << (*it) << " ";
	}
	std::cout << std::endl;
	//sort greater end

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
