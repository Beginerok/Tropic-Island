#include "Game.h"
#include <iostream>
Game::Game()
{
	run = true;//флаг признак нажатия кнопки выхода F5
	Matrix = new int* [8];//Поле 64 ячейки - значения 0 - для пустой ячейки, для игрока каждая пешка-шашка от 1 до 9, для компьютера значения в матрице от 10 до 18
	for (int i = 0; i < 8; i++)
		Matrix[i] = new int[8];
	//Квадраты координат нужны чтобы программа знала какие ячейки над указателем мыши, 64 квадрата
	QuadCoorXleft = new int* [8];//каждой ячейки матрицы Matrix соответстует квадрат координат для мыши xleft означает левую координату x
	QuadCoorXright = new int* [8];//xright - правая x
	QuadCoorYdown = new int* [8];//верхняя y координата
	QuadCoorYup = new int* [8];//нижняя y координата
	for (int i = 0; i < 8; i++)
	{
		QuadCoorXleft[i] = new int[8];
		QuadCoorXright[i] = new int[8];
		QuadCoorYdown[i] = new int[8];
		QuadCoorYup[i] = new int[8];
	}
	//Координаты пешек для отрисовки
	ChessX = new double[18];//X
	ChessY = new double[18];//Y
	//Выделяемая пешка ее координаты и значения
	ActiveX = -1;//X
	ActiveY = -1;//Y
	Active = -1;//Value
	firstplayer = true;//флаг того что можете игрок 1й ходить
	secondplayer = false;//флаг того что можете игрок 2й ходить
	ai = new bool[18];//ячейки флаги того что пешка на финишной позиции
	chessai tmp;
	for (int i = 0; i < 18; i++)
	{
		ai[i] = false;
		if (i > 8)
		{
			tmp.ai = ai[i];
			tmp.value = i+1;
			Ai.push_back(tmp);//Вектор с флагами финиша каждой пешки для искуственного интеллекта
		}
	}
	aicountfirstrow = 0;//счетчик кол-ва пешек ИИ(искуственного интеллекта) на верхней строчке(0-я)
	aicountsecondrow = 0;//счетчик кол-ва пешек ИИ на предверхней строчке(1-я)
	aicountthirdrow = 0;//счетчик кол-ва пешек ИИ на предпредверхней строчке(2-я)
}
void Game::setup_opengl(int width, int height)
{
	//Установка опенгл
	glClearColor(0, 0, 0, 0);
	glViewport(0, 0, width, height);
	glShadeModel(GL_SMOOTH);
	glCullFace(GL_BACK);
	glFrontFace(GL_CCW);
	glMatrixMode(GL_MODELVIEW);
	gluLookAt(0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);
	gluPerspective(189, 0.5, 0.6, 0.6);
}
void Draw_Table()
{
	//Отрисовка поля линиями
	//table
	glVertex2f(-0.8, 0.8);
	glVertex2f(-0.8, -0.8);

	glVertex2f(-0.6, 0.8);
	glVertex2f(-0.6, -0.8);

	glVertex2f(-0.4, 0.8);
	glVertex2f(-0.4, -0.8);

	glVertex2f(-0.2, 0.8);
	glVertex2f(-0.2, -0.8);

	glVertex2f(0.0, 0.8);
	glVertex2f(0.0, -0.8);

	glVertex2f(0.2, 0.8);
	glVertex2f(0.2, -0.8);

	glVertex2f(0.4, 0.8);
	glVertex2f(0.4, -0.8);

	glVertex2f(0.6, 0.8);
	glVertex2f(0.6, -0.8);

	glVertex2f(0.8, 0.8);
	glVertex2f(0.8, -0.8);

	glVertex2f(-0.8, 0.8);
	glVertex2f(0.8, 0.8);

	glVertex2f(-0.8, 0.6);
	glVertex2f(0.8, 0.6);

	glVertex2f(-0.8, 0.4);
	glVertex2f(0.8, 0.4);

	glVertex2f(-0.8, 0.2);
	glVertex2f(0.8, 0.2);

	glVertex2f(-0.8, 0.0);
	glVertex2f(0.8, 0.0);

	glVertex2f(-0.8, -0.2);
	glVertex2f(0.8, -0.2);

	glVertex2f(-0.8, -0.4);
	glVertex2f(0.8, -0.4);

	glVertex2f(-0.8, -0.6);
	glVertex2f(0.8, -0.6);

	glVertex2f(-0.8, -0.8);
	glVertex2f(0.8, -0.8);
	//table end

}
void Draw_Circle()
{
	//Отрисовка круга(пешек-шахмат) черного
	for (int i = 0; i <= 50; i++) {
		float a = (float)i / 50.0f * 3.1415f * 2.0f;
		glVertex2f(cos(a), sin(a));
	}
}
void Draw_Circle_Fill()
{
	//Отрисовка круга(пешек-шахмат) белого
	for (int i = 0; i <= 50; i++) {
		float a = (float)i / 50.0f * 3.1415f * 2.0f;
		glVertex2f(0.0, 0.0);
		glVertex2f(cos(a), sin(a));
	}
}
void Game::Move_Up()
{
	//Ход игрока вверх
	if (Active > 0 && ActiveX != 0 && Matrix[ActiveX-1][ActiveY] == 0)//Если выделенная пешка и не самая верхняя строчка и ячейка выше пустая
	{
		Matrix[ActiveX-1][ActiveY] = Matrix[ActiveX][ActiveY] ;//присваиваем ячейке выше текущюю(выделенную пешку)
		Matrix[ActiveX][ActiveY] = 0;//затираем старую ячейку на пустую 
		ChessY[Active-1] += 0.2;//перемещаем координату У пешки вверх для отрисовки
		ActiveX = -1;//стираем координаты выделенной пешки
		ActiveY = -1;//стираем координаты выделенной пешки
		Active = -1;//делаем неактивной текущую выделенную фигуру
		std::cout << " Player MoveUp " << Active << std::endl;
		firstplayer = false;
		secondplayer = true;//меняем флаги хода от игрока к ИИ
	}
}
void Game::Move_Down()
{
	//Ход игрока вниз
	if (Active > 0 && ActiveX != 7 && Matrix[ActiveX+1][ActiveY] == 0)//Если выделенная пешка и не самая нижняя строчка и ячейка ниже пустая
	{
		Matrix[ActiveX+1][ActiveY] = Matrix[ActiveX][ActiveY] ;//присваиваем ячейке ниже текущюю(выделенную пешку)
		Matrix[ActiveX][ActiveY] = 0;//затираем старую ячейку на пустую 
		ChessY[Active-1] -= 0.2;//перемещаем координату У пешки вниз для отрисовки
		ActiveX = -1;//стираем координаты выделенной пешки
		ActiveY = -1;//стираем координаты выделенной пешки
		Active = -1;//делаем неактивной текущую выделенную фигуру
		std::cout << "Player MoveDown " << Active << std::endl;
		firstplayer = false;
		secondplayer = true;//меняем флаги хода от игрока к ИИ
	}
}
void Game::Move_Right()
{
	//Ход игрока вправо
	if (Active > 0 && ActiveY != 7 && Matrix[ActiveX][ActiveY+1] == 0)//Если выделенная пешка и не самая правая строчка и ячейка справа пустая
	{
		Matrix[ActiveX][ActiveY+1] = Matrix[ActiveX][ActiveY] ;//присваиваем ячейке справа текущюю(выделенную пешку)
		Matrix[ActiveX][ActiveY] = 0;//затираем старую ячейку на пустую 
		ChessX[Active-1] += 0.2;//перемещаем координату Х пешки вправо для отрисовки
		ActiveX = -1;//стираем координаты выделенной пешки
		ActiveY = -1;//стираем координаты выделенной пешки
		Active = -1;//делаем неактивной текущую выделенную фигуру
		std::cout << "MoveRight " << Active << std::endl;
		firstplayer = false;
		secondplayer = true;//меняем флаги хода от игрока к ИИ
	}
}
void Game::Move_Left()
{
	//Ход игрока влево 
	if (Active > 0 && ActiveY != 0 && Matrix[ActiveX][ActiveY-1] == 0)//Если выделенная пешка и не самая левая строчка и ячейка слева пустая
	{
		Matrix[ActiveX][ActiveY-1] = Matrix[ActiveX][ActiveY] ;//присваиваем ячейке слева текущюю(выделенную пешку)
		Matrix[ActiveX][ActiveY] = 0;//затираем старую ячейку на пустую 
		ChessX[Active-1] -= 0.2;//перемещаем координату Х пешки влево для отрисовки
		ActiveX = -1;//стираем координаты выделенной пешки
		ActiveY = -1;//стираем координаты выделенной пешки
		Active = -1;//делаем неактивной текущую выделенную фигуру
		std::cout << "MoveLeft " << Active << std::endl;
		firstplayer = false;
		secondplayer = true;//меняем флаги хода от игрока к ИИ
	}
}
void Game::CheckFinishGame()
{
	//считаем кол-во пешек на финишных позициях для игрока и искуственного интеллекта
	int countfirstplayer=0, countsecondplayer=0;
	for (int i = 5; i < 8; i++)
		for (int j = 5; j < 8; j++)
			if (Matrix[i][j] > 0 && Matrix[i][j] < 10)
				countfirstplayer++;
	if (countfirstplayer == 9)
		std::cout << "first player win" << std::endl;
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			if (Matrix[i][j] > 9)
				countsecondplayer++;
	if (countsecondplayer == 9)
		std::cout << "second player AI win" << std::endl;
}
bool Game::Move_UpAI(int i,int j)
{
	//Ход вверх искуственного интеллекта вверх(флаг возвращения определяет успешность хода)
	if (i != 0 && Matrix[i - 1][j] == 0)//по аналогии с игроком если строчка не самая верхняя и ячейка сверху пустая
	{
		if (i - 1 == 0 && aicountfirstrow > 2)//если счетчик кол-ва пешек на самой верхней строчке от 3х
			return false;
		if (i - 1 == 1 && aicountsecondrow > 2)//если счетчик кол-ва пешек на предверхней строчке от 3х
			return false;
		if (i - 1 == 2 && aicountthirdrow > 2)//если счетчик кол-ва пешек на предпредверхней строчке от 3х
			return false;
		Matrix[i - 1][j] = Matrix[i][j];//ячейке сверху присваеваем пешку текущей ячейки
		ChessY[Matrix[i][j] - 1] += 0.2;//смещаем координату Y пешки для отрисовки
		Matrix[i][j] = 0;//стираем старую ячейку на пустую
		std::cout << "MoveUp AI" << std::endl;
		switch (i - 1)//смотрим кол-во пешек на трех верхних строчках
		{
		case 0:
			aicountfirstrow++;
			aicountsecondrow--;//переместилась со 2 на 1
			break;
		case 1:
			aicountsecondrow++;
			aicountthirdrow--;//переместилась с 3 на 2
			break;
		case 2:
			aicountthirdrow++;//переместилась на 3
			break;
		}
		return true;
	}
	else
		return false;
}
bool Game::Move_DownAI(int i, int j)
{
	//Ход искуственного интеллекта вверх(флаг возвращения определяет успешность хода)
	if (i != 7 && Matrix[i + 1][j] == 0)//по аналогии с игроком если строчка не самая нижняя и ячейка снизу пустая
	{
		Matrix[i + 1][j] = Matrix[i][j];//ячейке снизу присваеваем пешку текущей ячейки
		ChessY[Matrix[i][j] - 1] -= 0.2;//смещаем координату Y пешки для отрисовки
		Matrix[i][j] = 0;//стираем старую ячейку на пустую
		std::cout << "MoveDown AI"<< std::endl;
		switch (i)//смотрим кол-во пешек на трех верхних строчках
		{
		case 0:
			aicountfirstrow--;
			aicountsecondrow++;//переместилась с 1 на 2
			break;
		case 1:
			aicountsecondrow--;
			aicountthirdrow++;//переместилась с 2 на 3
			break;
		case 2:
			aicountthirdrow--;//переместилась с 3
			break;
		}
		return true;
	}
	else
		return false;
}
bool Game::Move_RightAI(int i, int j)
{
	//Ход вправо искуственного интеллекта вверх(флаг возвращения определяет успешность хода)
	if (j != 7 && Matrix[i][j + 1] == 0)//по аналогии с игроком если строчка не самая правая и ячейка справа пустая
	{
		Matrix[i][j + 1] = Matrix[i][j];//ячейке справа присваеваем пешку текущей ячейки
		ChessX[Matrix[i][j] - 1] += 0.2;//смещаем координату X пешки для отрисовки
		Matrix[i][j] = 0;//стираем старую ячейку на пустую
		std::cout << "MoveRight AI" << std::endl;
		return true;
	}
	else
		return false;
}
bool Game::Move_LeftAI(int i, int j)
{
	//Ход влево искуственного интеллекта вверх(флаг возвращения определяет успешность хода)
	if (j != 0 && Matrix[i][j - 1] == 0)//по аналогии с игроком если строчка не левая и ячейка слева пустая
	{
		Matrix[i][j - 1] = Matrix[i][j];//ячейке слева присваеваем пешку текущей ячейки
		ChessX[Matrix[i][j] - 1] -= 0.2;//смещаем координату X пешки для отрисовки
		Matrix[i][j] = 0;//стираем старую ячейку на пустую
		std::cout << "MoveLeft AI" <<std::endl;
		return true;
	}
	else
		return false;
}
POINT Game::FindMatrix(int value)
{
	//Поиск в матрице пешки(у каждой свое значение) и вовзрат ее индексов
	POINT tmp;
	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++)
			if (Matrix[i][j] == value)
			{
				tmp.x = i;
				tmp.y = j;
				return tmp;
			}
}
bool Game::Check_MoveUp(int value)
{
	//Проверка ИИ может ли походить вверх
	POINT p = FindMatrix(value);
	if (p.x - 1 == 0 && aicountfirstrow > 2)//кол-во пешек в самой верхней строчке
		return false;
	if (p.x - 1 == 1 && aicountsecondrow > 2)//кол-во пешек в предверхней строчке
		return false;
	if (p.x - 1 == 2 && aicountthirdrow > 2)//кол-во пешек в преддпредверхней строчке
		return false;
	if (p.x != 0 && Matrix[p.x-1][p.y] == 0)
		return true;
	else
		return false;
}
bool Game::Check_MoveLeft(int value)
{
	//Проверка ИИ может ли походить влево
	POINT p = FindMatrix(value);
	if (p.y != 0 && Matrix[p.x][p.y-1] == 0)
		return true;
	else
		return false;
}
bool Game::Check_MoveDown(int value)
{
	//Проверка ИИ может ли походить вниз
	POINT p = FindMatrix(value);
	if (p.x != 7 && Matrix[p.x + 1][p.y] == 0)
		return true;
	else
		return false;
}
bool Game::Check_MoveRight(int value)
{
	//Проверка ИИ может ли походить вправо
	POINT p = FindMatrix(value);
	if (p.y != 7 && Matrix[p.x][p.y + 1] == 0)
		return true;
	else
		return false;
}
struct find_s
{
	//поиск значения пешки в структуре chessai
	int value;
	find_s(int value) : value(value) {}
	bool operator () (const chessai& m) const
	{
		return m.value == value;
	}
};
void Game::ReccurentWalk()
{
	//Реккурентный ход ИИ
	current = -1, currentI = -1, currentJ = -1;//изначально выделенная пешка не определена
	for (int i = 0; i < Ai.size(); i++)//поиск по массиву
		if (!Ai[i].ai)//если не завершены ходы для конкретных пешек
		{
			if (Check_MoveUp(Ai[i].value) || Check_MoveLeft(Ai[i].value))//Можно ли походить вверх или влево?
			{
				current = Ai[i].value;//запоминаем текущую пешку
				break;
			}
			else
			{
				//Если походить нельзя стираем из массива ходов пешку
				std::vector<chessai>::iterator position = std::find_if(Ai.begin(), Ai.end(), find_s(Ai[i].value));
				if (position != Ai.end()) // == myVector.end() means the element was not found
					Ai.erase(position);
			}
		}
	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++)
			if (Matrix[i][j] == current)//ищем в матрице пешку и запоминаем индексы
			{
				currentI = i;
				currentJ = j;
				break;
			}
	if (currentI != -1 && currentJ != -1)//если какая либо найдена ходим либо вверх либо влево
	{
		if (!Move_UpAI(currentI, currentJ))
			if (!Move_LeftAI(currentI, currentJ))
			{
				ReccurentWalk();
			}
	}
	else
	{
		//если не найдена заполняем массив ходов снова пешками
		chessai tmp;
		for (int i = 0; i < 18; i++)
		{
			ai[i] = false;
			if (i > 8)
			{
				tmp.ai = ai[i];
				tmp.value = i + 1;
				Ai.push_back(tmp);
			}
		}
		//ищем ту которая может походить вправо или вниз
		for (int i = 0; i < Ai.size(); i++)
			if (!Ai[i].ai)
			{
				if (Check_MoveRight(Ai[i].value) || Check_MoveDown(Ai[i].value))
				{
					current = Ai[i].value;
					break;
				}
				else
				{
					//если не может то стираем из массива
					std::vector<chessai>::iterator position = std::find_if(Ai.begin(), Ai.end(), find_s(Ai[i].value));
					if (position != Ai.end()) // == Vector.end() means the element was not found
						Ai.erase(position);
				}
			}
		//ищем ее индексы в матрице
		for (int i = 0; i < 8; i++)
			for (int j = 0; j < 8; j++)
				if (Matrix[i][j] == current)
				{
					currentI = i;
					currentJ = j;
					break;
				}
		//ходим вправо или вниз
		if(!Move_RightAI(currentI, currentJ))
			if (!Move_DownAI(currentI, currentJ))
			{
				std::cout <<"Artificial Intellegence asked: WTF?" << std::endl;
			}
	}
	chessai tmp;
	if(Ai.empty())//если список ходов пуст заполняем снова всеми
		for (int i = 0; i < 18; i++)
		{
			ai[i] = false;
			if (i > 8)
			{
				tmp.ai = ai[i];
				tmp.value = i + 1;
				Ai.push_back(tmp);
			}
		}
}
void Game::AI()
{
	//Метод искусственного интеллекта
	if(secondplayer)
	{
		secondplayer = false;
		firstplayer = true;//меняем флаги хода игрока и ИИ
		ReccurentWalk();//Ход ИИ
		if (currentI == 0 && currentJ == 0)//проверка 9 позиций для завершения игры
		{
			ai[9] = true;
			//ReccurentWalk();
		}
		if (currentI == 0 && currentJ == 1)
		{
			ai[10] = true;
			//ReccurentWalk();
		}
		if (currentI == 0 && currentJ == 2)
		{
			ai[11] = true;
			//ReccurentWalk();
		}
		if (currentI == 1 && currentJ == 0)
		{
			ai[12] = true;
			//ReccurentWalk();
		}
		if (currentI == 1 && currentJ == 1)
		{
			ai[13] = true;
			//ReccurentWalk();
		}
		if (currentI == 1 && currentJ == 2)
		{
			ai[14] = true;
			//ReccurentWalk();
		}
		if (currentI == 2 && currentJ == 0)
		{
			ai[15] = true;
			//ReccurentWalk();
		}
		if (currentI == 2 && currentJ == 1)
		{
			ai[16] = true;
			//ReccurentWalk();
		}
		if (currentI == 2 && currentJ == 2)
		{
			ai[17] = true;
			//ReccurentWalk();
		}
	}
}
void Game::SetCoordinats()
{
	//Заполняем матрицу пустыми ячейками
	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++)
		{
			Matrix[i][j] = 0;
		}
	//Пешки для игрока
	Matrix[0][0] = 1;
	Matrix[0][1] = 2;
	Matrix[0][2] = 3;
	Matrix[1][0] = 4;
	Matrix[1][1] = 5;
	Matrix[1][2] = 6;
	Matrix[2][0] = 7;
	Matrix[2][1] = 8;
	Matrix[2][2] = 9;
	//Пешки для ИИ
	Matrix[5][5] = 10;
	Matrix[5][6] = 11;
	Matrix[5][7] = 12;
	Matrix[6][5] = 13;
	Matrix[6][6] = 14;
	Matrix[6][7] = 15;
	Matrix[7][5] = 16;
	Matrix[7][6] = 17;
	Matrix[7][7] = 18;

	//Координаты пешек Х и У
	ChessX[0] = -0.7;
	ChessY[0] = 0.7;

	ChessX[1] = -0.5;
	ChessY[1] = 0.7;

	ChessX[2] = -0.3;
	ChessY[2] = 0.7;

	ChessX[3] = -0.7;
	ChessY[3] = 0.5;

	ChessX[4] = -0.5;
	ChessY[4] = 0.5;

	ChessX[5] = -0.3;
	ChessY[5] = 0.5;

	ChessX[6] = -0.7;
	ChessY[6] = 0.3;

	ChessX[7] = -0.5;
	ChessY[7] = 0.3;

	ChessX[8] = -0.3;
	ChessY[8] = 0.3;

	ChessX[9] = 0.3;
	ChessY[9] = -0.3;

	ChessX[10] = 0.5;
	ChessY[10] = -0.3;

	ChessX[11] = 0.7;
	ChessY[11] = -0.3;

	ChessX[12] = 0.3;
	ChessY[12] = -0.5;

	ChessX[13] = 0.5;
	ChessY[13] = -0.5;

	ChessX[14] = 0.7;
	ChessY[14] = -0.5;

	ChessX[15] = 0.3;
	ChessY[15] = -0.7;

	ChessX[16] = 0.5;
	ChessY[16] = -0.7;

	ChessX[17] = 0.7;
	ChessY[17] = -0.7;

	//Координаты квадратов для мыши
	QuadCoorXleft[0][0] = 73;
	QuadCoorXright[0][0] = 135;
	QuadCoorYup[0][0] = 52;
	QuadCoorYdown[0][0] = 95;

	QuadCoorXleft[0][1] = 143;
	QuadCoorXright[0][1] = 205;
	QuadCoorYup[0][1] = 52;
	QuadCoorYdown[0][1] = 95;

	QuadCoorXleft[0][2] = 214;
	QuadCoorXright[0][2] = 271;
	QuadCoorYup[0][2] = 52;
	QuadCoorYdown[0][2] = 95;

	QuadCoorXleft[0][3] = 284;
	QuadCoorXright[0][3] = 342;
	QuadCoorYup[0][3] = 52;
	QuadCoorYdown[0][3] = 95;

	QuadCoorXleft[0][4] = 353;
	QuadCoorXright[0][4] = 411;
	QuadCoorYup[0][4] = 52;
	QuadCoorYdown[0][4] = 95;

	QuadCoorXleft[0][5] = 425;
	QuadCoorXright[0][5] = 481;
	QuadCoorYup[0][5] = 52;
	QuadCoorYdown[0][5] = 95;

	QuadCoorXleft[0][6] = 494;
	QuadCoorXright[0][6] = 553;
	QuadCoorYup[0][6] = 52;
	QuadCoorYdown[0][6] = 95;

	QuadCoorXleft[0][7] = 565;
	QuadCoorXright[0][7] = 624;
	QuadCoorYup[0][7] = 52;
	QuadCoorYdown[0][7] = 95;
	//
	QuadCoorXleft[1][0] = 73;
	QuadCoorXright[1][0] = 135;
	QuadCoorYup[1][0] = 103;
	QuadCoorYdown[1][0] = 143;

	QuadCoorXleft[1][1] = 143;
	QuadCoorXright[1][1] = 205;
	QuadCoorYup[1][1] = 103;
	QuadCoorYdown[1][1] = 143;

	QuadCoorXleft[1][2] = 214;
	QuadCoorXright[1][2] = 271;
	QuadCoorYup[1][2] = 103;
	QuadCoorYdown[1][2] = 143;

	QuadCoorXleft[1][3] = 284;
	QuadCoorXright[1][3] = 342;
	QuadCoorYup[1][3] = 103;
	QuadCoorYdown[1][3] = 143;

	QuadCoorXleft[1][4] = 353;
	QuadCoorXright[1][4] = 411;
	QuadCoorYup[1][4] = 103;
	QuadCoorYdown[1][4] = 143;

	QuadCoorXleft[1][5] = 425;
	QuadCoorXright[1][5] = 481;
	QuadCoorYup[1][5] = 103;
	QuadCoorYdown[1][5] = 143;

	QuadCoorXleft[1][6] = 494;
	QuadCoorXright[1][6] = 553;
	QuadCoorYup[1][6] = 103;
	QuadCoorYdown[1][6] = 143;

	QuadCoorXleft[1][7] = 565;
	QuadCoorXright[1][7] = 624;
	QuadCoorYup[1][7] = 103;
	QuadCoorYdown[1][7] = 143;
	//
	QuadCoorXleft[2][0] = 73;
	QuadCoorXright[2][0] = 135;
	QuadCoorYup[2][0] = 152;
	QuadCoorYdown[2][0] = 193;

	QuadCoorXleft[2][1] = 143;
	QuadCoorXright[2][1] = 205;
	QuadCoorYup[2][1] = 152;
	QuadCoorYdown[2][1] = 193;

	QuadCoorXleft[2][2] = 214;
	QuadCoorXright[2][2] = 271;
	QuadCoorYup[2][2] = 152;
	QuadCoorYdown[2][2] = 193;

	QuadCoorXleft[2][3] = 284;
	QuadCoorXright[2][3] = 342;
	QuadCoorYup[2][3] = 152;
	QuadCoorYdown[2][3] = 193;

	QuadCoorXleft[2][4] = 353;
	QuadCoorXright[2][4] = 411;
	QuadCoorYup[2][4] = 152;
	QuadCoorYdown[2][4] = 193;

	QuadCoorXleft[2][5] = 425;
	QuadCoorXright[2][5] = 481;
	QuadCoorYup[2][5] = 152;
	QuadCoorYdown[2][5] = 193;

	QuadCoorXleft[2][6] = 494;
	QuadCoorXright[2][6] = 553;
	QuadCoorYup[2][6] = 152;
	QuadCoorYdown[2][6] = 193;

	QuadCoorXleft[2][7] = 565;
	QuadCoorXright[2][7] = 624;
	QuadCoorYup[2][7] = 152;
	QuadCoorYdown[2][7] = 193;
	//
	QuadCoorXleft[3][0] = 73;
	QuadCoorXright[3][0] = 135;
	QuadCoorYup[3][0] = 203;
	QuadCoorYdown[3][0] = 244;

	QuadCoorXleft[3][1] = 143;
	QuadCoorXright[3][1] = 205;
	QuadCoorYup[3][1] = 203;
	QuadCoorYdown[3][1] = 244;

	QuadCoorXleft[3][2] = 214;
	QuadCoorXright[3][2] = 271;
	QuadCoorYup[3][2] = 203;
	QuadCoorYdown[3][2] = 244;

	QuadCoorXleft[3][3] = 284;
	QuadCoorXright[3][3] = 342;
	QuadCoorYup[3][3] = 203;
	QuadCoorYdown[3][3] = 244;

	QuadCoorXleft[3][4] = 353;
	QuadCoorXright[3][4] = 411;
	QuadCoorYup[3][4] = 203;
	QuadCoorYdown[3][4] = 244;

	QuadCoorXleft[3][5] = 425;
	QuadCoorXright[3][5] = 481;
	QuadCoorYup[3][5] = 203;
	QuadCoorYdown[3][5] = 244;

	QuadCoorXleft[3][6] = 494;
	QuadCoorXright[3][6] = 553;
	QuadCoorYup[3][6] = 203;
	QuadCoorYdown[3][6] = 244;

	QuadCoorXleft[3][7] = 565;
	QuadCoorXright[3][7] = 624;
	QuadCoorYup[3][7] = 203;
	QuadCoorYdown[3][7] = 244;
	//
	QuadCoorXleft[4][0] = 73;
	QuadCoorXright[4][0] = 135;
	QuadCoorYup[4][0] = 253;
	QuadCoorYdown[4][0] = 291;

	QuadCoorXleft[4][1] = 143;
	QuadCoorXright[4][1] = 205;
	QuadCoorYup[4][1] = 253;
	QuadCoorYdown[4][1] = 291;

	QuadCoorXleft[4][2] = 214;
	QuadCoorXright[4][2] = 271;
	QuadCoorYup[4][2] = 253;
	QuadCoorYdown[4][2] = 291;

	QuadCoorXleft[4][3] = 284;
	QuadCoorXright[4][3] = 342;
	QuadCoorYup[4][3] = 253;
	QuadCoorYdown[4][3] = 291;

	QuadCoorXleft[4][4] = 353;
	QuadCoorXright[4][4] = 411;
	QuadCoorYup[4][4] = 253;
	QuadCoorYdown[4][4] = 291;

	QuadCoorXleft[4][5] = 425;
	QuadCoorXright[4][5] = 481;
	QuadCoorYup[4][5] = 253;
	QuadCoorYdown[4][5] = 291;

	QuadCoorXleft[4][6] = 494;
	QuadCoorXright[4][6] = 553;
	QuadCoorYup[4][6] = 253;
	QuadCoorYdown[4][6] = 291;

	QuadCoorXleft[4][7] = 565;
	QuadCoorXright[4][7] = 624;
	QuadCoorYup[4][7] = 253;
	QuadCoorYdown[4][7] = 291;
	//
	QuadCoorXleft[5][0] = 73;
	QuadCoorXright[5][0] = 135;
	QuadCoorYup[5][0] = 303;
	QuadCoorYdown[5][0] = 342;

	QuadCoorXleft[5][1] = 143;
	QuadCoorXright[5][1] = 205;
	QuadCoorYup[5][1] = 303;
	QuadCoorYdown[5][1] = 342;

	QuadCoorXleft[5][2] = 214;
	QuadCoorXright[5][2] = 271;
	QuadCoorYup[5][2] = 303;
	QuadCoorYdown[5][2] = 342;

	QuadCoorXleft[5][3] = 284;
	QuadCoorXright[5][3] = 342;
	QuadCoorYup[5][3] = 303;
	QuadCoorYdown[5][3] = 342;

	QuadCoorXleft[5][4] = 353;
	QuadCoorXright[5][4] = 411;
	QuadCoorYup[5][4] = 303;
	QuadCoorYdown[5][4] = 342;

	QuadCoorXleft[5][5] = 425;
	QuadCoorXright[5][5] = 481;
	QuadCoorYup[5][5] = 303;
	QuadCoorYdown[5][5] = 342;

	QuadCoorXleft[5][6] = 494;
	QuadCoorXright[5][6] = 553;
	QuadCoorYup[5][6] = 303;
	QuadCoorYdown[5][6] = 342;

	QuadCoorXleft[5][7] = 565;
	QuadCoorXright[5][7] = 624;
	QuadCoorYup[5][7] = 303;
	QuadCoorYdown[5][7] = 342;
	//
	QuadCoorXleft[6][0] = 73;
	QuadCoorXright[6][0] = 135;
	QuadCoorYup[6][0] = 354;
	QuadCoorYdown[6][0] = 399;

	QuadCoorXleft[6][1] = 143;
	QuadCoorXright[6][1] = 205;
	QuadCoorYup[6][1] = 354;
	QuadCoorYdown[6][1] = 399;

	QuadCoorXleft[6][2] = 214;
	QuadCoorXright[6][2] = 271;
	QuadCoorYup[6][2] = 354;
	QuadCoorYdown[6][2] = 399;

	QuadCoorXleft[6][3] = 284;
	QuadCoorXright[6][3] = 342;
	QuadCoorYup[6][3] = 354;
	QuadCoorYdown[6][3] = 399;

	QuadCoorXleft[6][4] = 353;
	QuadCoorXright[6][4] = 411;
	QuadCoorYup[6][4] = 354;
	QuadCoorYdown[6][4] = 399;

	QuadCoorXleft[6][5] = 425;
	QuadCoorXright[6][5] = 481;
	QuadCoorYup[6][5] = 354;
	QuadCoorYdown[6][5] = 399;

	QuadCoorXleft[6][6] = 494;
	QuadCoorXright[6][6] = 553;
	QuadCoorYup[6][6] = 354;
	QuadCoorYdown[6][6] = 399;

	QuadCoorXleft[6][7] = 565;
	QuadCoorXright[6][7] = 624;
	QuadCoorYup[6][7] = 354;
	QuadCoorYdown[6][7] = 399;
	//
	QuadCoorXleft[7][0] = 73;
	QuadCoorXright[7][0] = 135;
	QuadCoorYup[7][0] = 404;
	QuadCoorYdown[7][0] = 445;

	QuadCoorXleft[7][1] = 143;
	QuadCoorXright[7][1] = 205;
	QuadCoorYup[7][1] = 404;
	QuadCoorYdown[7][1] = 445;

	QuadCoorXleft[7][2] = 214;
	QuadCoorXright[7][2] = 271;
	QuadCoorYup[7][2] = 404;
	QuadCoorYdown[7][2] = 445;

	QuadCoorXleft[7][3] = 284;
	QuadCoorXright[7][3] = 342;
	QuadCoorYup[7][3] = 404;
	QuadCoorYdown[7][3] = 445;

	QuadCoorXleft[7][4] = 353;
	QuadCoorXright[7][4] = 411;
	QuadCoorYup[7][4] = 404;
	QuadCoorYdown[7][4] = 445;

	QuadCoorXleft[7][5] = 425;
	QuadCoorXright[7][5] = 481;
	QuadCoorYup[7][5] = 404;
	QuadCoorYdown[7][5] = 445;

	QuadCoorXleft[7][6] = 494;
	QuadCoorXright[7][6] = 553;
	QuadCoorYup[7][6] = 404;
	QuadCoorYdown[7][6] = 445;

	QuadCoorXleft[7][7] = 565;
	QuadCoorXright[7][7] = 624;
	QuadCoorYup[7][7] = 404;
	QuadCoorYdown[7][7] = 445;
}
void Game::BeganActive()
{
	//Ходы игрока тут
	for(int i=0;i<8;i++)
		for (int j = 0; j < 8; j++)
		{
			if (Active != -1)//если выделенная пешка не пустота(точнее уже выделили пешку)
			{
				if (oldx - WindowsSDLApi_->point.x > 0 && oldx - WindowsSDLApi_->point.x > 20)//сравниваем старые и новые кординаты нажатия мыши и ходим
					Move_Left();
				if (oldx - WindowsSDLApi_->point.x < 0 && oldx - WindowsSDLApi_->point.x <-20)
					Move_Right();
				if (oldy - WindowsSDLApi_->point.y > 0 && oldy - WindowsSDLApi_->point.y > 20)
					Move_Up();
				if (oldy - WindowsSDLApi_->point.y < 0 && oldy - WindowsSDLApi_->point.y < -20)
					Move_Down();
				oldx = WindowsSDLApi_->point.x;//меняем старые координаты мыши на текущие
				oldy = WindowsSDLApi_->point.y;
				return;
			}
			if (WindowsSDLApi_->point.x > QuadCoorXleft[i][j] && WindowsSDLApi_->point.x < QuadCoorXright[i][j] &&
				WindowsSDLApi_->point.y > QuadCoorYup[i][j] && WindowsSDLApi_->point.y < QuadCoorYdown[i][j] && Matrix[i][j] != 0
				&& oldx!=WindowsSDLApi_->point.x && oldy!=WindowsSDLApi_->point.y)//смотрим в какой квадрат попали координаты клика мыши
			{
				if ((Matrix[i][j] > 0 && Matrix[i][j] < 10 && firstplayer) || (Matrix[i][j]>9 && secondplayer))
				{
					if (Matrix[i][j] > 0 && Matrix[i][j] < 10 && firstplayer)
					{
						std::cout << "first player walk " << firstplayer << " " << secondplayer << std::endl;
					}
					if (Matrix[i][j] > 9 && secondplayer)
					{
						secondplayer = false;
						firstplayer = true;
						std::cout << "second player walk " << firstplayer << " " << secondplayer << std::endl;
					}
					Active = Matrix[i][j];//выделяем пешку из матрицы
					ActiveX = i;//запоминаем индексы её
					ActiveY = j;
					oldx = WindowsSDLApi_->point.x, oldy = WindowsSDLApi_->point.y;
					std::cout << ActiveX << " " << ActiveY << std::endl;
					std::cout << oldx << " " << oldy << std::endl;
					std::cout << Active << std::endl;
					return;
				}
			}
		}
}
void Game::draw_screen()
{
	//Рендер
	while (run)
	{
		glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
		glDepthMask(GL_TRUE);
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClearDepth(1.0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT /*| GL_COLOR_MATERIAL*/);
		//Рисуем поле
		glBegin(GL_LINES);
		Draw_Table();
		glEnd();
		//Рисуем черные пешки игрока
		for (int i = 0; i < 9; i++)
		{
			glPushMatrix();
			glTranslatef(ChessX[i], ChessY[i], 0);
			glScalef(0.05, 0.05, 1);
			glBegin(GL_LINE_LOOP);
			Draw_Circle();
			glEnd();
			glPopMatrix();
		}
		//Рисуем белые пешки ИИ
		for (int i = 9; i < 18; i++)
		{
			glPushMatrix();
			glTranslatef(ChessX[i], ChessY[i], 0);
			glScalef(0.05, 0.05, 1);
			glBegin(GL_LINES);
			Draw_Circle_Fill();
			glEnd();
			glPopMatrix();
		}

		SDL_GL_SwapWindow(window);
		SDL_PollEvent(&event_);
		SDL_PumpEvents();
		WindowsSDLApi_->Update(event_);
		CheckFinishGame();//проверка окончания игры
		BeganActive();//Обработчик мыши для игрока
		AI();//Модуль ИИ
		run = !WindowsSDLApi_->getdone();//Проверка нажатия кнопки закрытия приложения
	}
	Exit();
}
int Game::Execute()
{
	//Основной поток игры
	SDL_GLContext context;
	SDL_Init(SDL_INIT_VIDEO);
	window = SDL_CreateWindow("Chess", 10, 10,700 ,500, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
	context = SDL_GL_CreateContext(window);
	SDL_GL_SetSwapInterval(1);
	setup_opengl(700, 500);
	WindowsSDLApi_ = new WindowsSDLApi();
	SetCoordinats();
	draw_screen();
	SDL_GL_DeleteContext(context);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}
void Game::Exit()
{
	run = false;
}
Game::~Game()
{
	//Очистка памяти
	for (int i = 0; i < 8; i++)
	{
		delete[] Matrix[i];
		delete[] QuadCoorXleft[i];
		delete[] QuadCoorXright[i];
		delete[] QuadCoorYdown[i];
		delete[] QuadCoorYup[i];
	}
	delete[] Matrix;
	delete[] QuadCoorXleft;
	delete[] QuadCoorXright;;
	delete[] QuadCoorYdown;
	delete[] QuadCoorYup;
	delete[] ChessX;
	delete[] ChessY;
	delete[] ai;
	Ai.clear();
	delete WindowsSDLApi_;
}
