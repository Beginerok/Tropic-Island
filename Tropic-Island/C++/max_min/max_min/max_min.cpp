// max_min.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <vector>
#include <ctime>
int main()
{
	std::vector<float> arr;
	const int N = 100000;
	srand(time(0));
	for (int i = 0; i < N; i++) 
	{
		arr.push_back((float)(rand() % 101)/100.0);
		//std::cout << arr[i] << " ";
	}
	std::cout << std::endl;
	float min = arr[0], max = arr[0], mean = arr[0], meanquad = arr[0] * arr[0], disp = 0.0;
	for (int i = 1; i < N; i++)
	{
		if (min > arr[i])
			min = arr[i];
		if (max < arr[i])
			max = arr[i];
		mean += arr[i];
		meanquad += arr[i] * arr[i];
	}
	disp = meanquad / N - mean / N * mean / N;
	std::cout << "min=" << min << std::endl;
	std::cout << "max=" << max << std::endl;
	std::cout << "mean=" << (float)mean / N << std::endl;
	std::cout << "dispersion=" << disp << std::endl;
	std::cout << "sqrt(dispersion)=" << sqrt(disp) << std::endl;
	arr.clear();
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
