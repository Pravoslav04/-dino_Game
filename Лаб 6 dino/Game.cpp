#include <iostream>
#include <random>
#include<stdio.h>
#include"Game.h"
#include<Windows.h>
#include <string>
using namespace std;

void Game::barrierGenerate(){//генерирует преграду, предварительно проверив, нет ли уже существующих преград справа и слева
	if ((rand() % 100) < 16) {
		if (matrix[3][13] != "|" && matrix[3][12] != "|" && matrix[3][11] != "|" && matrix[3][10] != "|")
		{
			matrix[3][14] = "|";
		}
	}
}
void Game::step(){
	if (matrix[3][0] == "$" && matrix[3][1] == "|") {//проверка не врезался ли динозаврик
		stop = true;
	}
	for (int j = 1; j < 14; j++) {//сдвиг поля влево (имитация движения динозаврика)
		matrix[3][j] = matrix[3][j + 1];
		matrix[3][j + 1] = " ";
		matrix[4][j] = matrix[4][j + 1];
	}
	barrierGenerate();//генерация преграды
};
void Game::toDisplay() {//метод отрисовки поля
	step();//сразу делаем сдвиг, чтобы не писать каждый раз перед отрисовкой
	for (int i = 0; i < 6; i++) {//отрисовывает поле
		cout << endl;
		for (int j = 0; j < 15; j++) {
			cout << matrix[i][j];
		}
	}
};
void Game::jump(){//метод прыжка динозавра
	matrix[3][0] = " ";
	for (int i = 3; i > 1; i--) {//движение динозаврика вверх
		matrix[i][0] = " ";
		matrix[i - 1][0] = "$";
		Sleep(300);//задерживает выполнение программы на 0.3 секунды
		system("cls");//очищает консоль
		count++;
		matrix[5][1] =to_string(count);//отображение счёта
		toDisplay();
	}
	for (int i = 1; i < 3; i++) {//движение динозаврика вниз
		matrix[i][0] = " ";
		matrix[i + 1][0] = "$";
		Sleep(300);
		system("cls");
		count++;
		matrix[5][1] = to_string(count);
		toDisplay();
	}
}
void Game::refresh() {//метод, который обновляет поле при рестарте, чтобы игра не продолжалась с того же места
	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 15; j++) {
			matrix[i][j] = newmatrix[i][j];
		}
	}
}
void Game::start(){//метод начала игры
	stop = false;
	bool space = false;
	count = 0;
	refresh();
	toDisplay();
	while (!stop){//пока динозаврик не столкнулся с препятствием
		space = false;
		if (GetKeyState(VK_SPACE) & 0x8000){//если пробел был нажат, то прыгаем
			space = true;
			jump();
		}
		if (!space) {//если не был нажат пробел, бежим дальше
			Sleep(300);
			system("cls");
			toDisplay();
			count++;
			matrix[5][1] = to_string(count);

		}
	}
	cout << "\nПовторить игру? (1 - да , 2 - нет)" << endl;
	int repeat;
	cin >> repeat;
	if (repeat == 1){
		system("cls");
		start();
	}
	else{
		cout << "\nСпасибо за игру!" << endl;
		exit(0);
	}

};
