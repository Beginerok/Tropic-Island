#pragma once
#include "WindowsSDLApi.h"
#include <vector>
#include <algorithm>
#include <iterator>
struct chessai//структура хранящая флаги завершения ходов игры пешек и их значения
{
	bool ai;
	int value;
};
class Game
{
public:
	SDL_Window *window;
	SDL_Event event_;
	WindowsSDLApi *WindowsSDLApi_;
	Game();
	void draw_screen();//Рендер
	void setup_opengl(int width, int height);//Установка опенгл
	int Execute();//Основной поток игры 
	void BeganActive();//Ходы игрока тут
	void SetCoordinats();
	void Move_Up();//Ход игрока вверх
	void Move_Down();//Ход игрока вниз
	void Move_Right();//Ход игрока вправо
	void Move_Left();//Ход игрока влево
	void CheckFinishGame();//считаем кол-во пешек на финишных позициях для игрока и искуственного интеллекта
	void AI();//Метод искусственного интеллекта
	void ReccurentWalk();//Реккурентный ход ИИ
	bool Move_UpAI(int i, int j);//Ход вверх искуственного интеллекта вверх(флаг возвращения определяет успешность хода)
	bool Move_DownAI(int i, int j);//Ход искуственного интеллекта вверх(флаг возвращения определяет успешность хода)
	bool Move_RightAI(int i, int j);//Ход вправо искуственного интеллекта вверх(флаг возвращения определяет успешность хода)
	bool Move_LeftAI(int i, int j);//Ход влево искуственного интеллекта вверх(флаг возвращения определяет успешность хода)
	bool Check_MoveLeft(int value);//Проверка ИИ может ли походить влево
	bool Check_MoveUp(int value);//Проверка ИИ может ли походить вверх
	POINT FindMatrix(int value);//Поиск в матрице пешки(у каждой свое значение) и вовзрат ее индексов
	bool Check_MoveDown(int value);//Проверка ИИ может ли походить вниз
	bool Check_MoveRight(int value);//Проверка ИИ может ли походить вправо
	bool run;//флаг выхода
	void Exit();//Выход
	int** Matrix;//Поле игры
	int** QuadCoorXleft, **QuadCoorXright, **QuadCoorYup, **QuadCoorYdown;//координаты квадратов поля для мыши
	int  ActiveX,ActiveY,Active,oldx,oldy;//выделенные координаты и пешки для игрока
	double* ChessX,*ChessY;//координаты пешек для отрисовки
	bool firstplayer, secondplayer,*ai;//флаги возможности хода игроков и всех пешек для завершения игры
	int current, currentI, currentJ;//выдделенная пешка и её индексы
	std::vector<chessai> Ai;//Вектор с флагами финиша каждой пешки для искуственного интеллекта
	int aicountfirstrow, aicountsecondrow, aicountthirdrow; //счетчик кол-ва пешек ИИ на строчках
	~Game();//Очистка памяти
};

