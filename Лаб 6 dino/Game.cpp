#include <iostream>
#include <random>
#include<stdio.h>
#include"Game.h"
#include<Windows.h>
#include <string>
using namespace std;

void Game::barrierGenerate(){//���������� ��������, �������������� ��������, ��� �� ��� ������������ ������� ������ � �����
	if ((rand() % 100) < 16) {
		if (matrix[3][13] != "|" && matrix[3][12] != "|" && matrix[3][11] != "|" && matrix[3][10] != "|")
		{
			matrix[3][14] = "|";
		}
	}
}
void Game::step(){
	if (matrix[3][0] == "$" && matrix[3][1] == "|") {//�������� �� �������� �� ����������
		stop = true;
	}
	for (int j = 1; j < 14; j++) {//����� ���� ����� (�������� �������� �����������)
		matrix[3][j] = matrix[3][j + 1];
		matrix[3][j + 1] = " ";
		matrix[4][j] = matrix[4][j + 1];
	}
	barrierGenerate();//��������� ��������
};
void Game::toDisplay() {//����� ��������� ����
	step();//����� ������ �����, ����� �� ������ ������ ��� ����� ����������
	for (int i = 0; i < 6; i++) {//������������ ����
		cout << endl;
		for (int j = 0; j < 15; j++) {
			cout << matrix[i][j];
		}
	}
};
void Game::jump(){//����� ������ ���������
	matrix[3][0] = " ";
	for (int i = 3; i > 1; i--) {//�������� ����������� �����
		matrix[i][0] = " ";
		matrix[i - 1][0] = "$";
		Sleep(300);//����������� ���������� ��������� �� 0.3 �������
		system("cls");//������� �������
		count++;
		matrix[5][1] =to_string(count);//����������� �����
		toDisplay();
	}
	for (int i = 1; i < 3; i++) {//�������� ����������� ����
		matrix[i][0] = " ";
		matrix[i + 1][0] = "$";
		Sleep(300);
		system("cls");
		count++;
		matrix[5][1] = to_string(count);
		toDisplay();
	}
}
void Game::refresh() {//�����, ������� ��������� ���� ��� ��������, ����� ���� �� ������������ � ���� �� �����
	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 15; j++) {
			matrix[i][j] = newmatrix[i][j];
		}
	}
}
void Game::start(){//����� ������ ����
	stop = false;
	bool space = false;
	count = 0;
	refresh();
	toDisplay();
	while (!stop){//���� ���������� �� ���������� � ������������
		space = false;
		if (GetKeyState(VK_SPACE) & 0x8000){//���� ������ ��� �����, �� �������
			space = true;
			jump();
		}
		if (!space) {//���� �� ��� ����� ������, ����� ������
			Sleep(300);
			system("cls");
			toDisplay();
			count++;
			matrix[5][1] = to_string(count);

		}
	}
	cout << "\n��������� ����? (1 - �� , 2 - ���)" << endl;
	int repeat;
	cin >> repeat;
	if (repeat == 1){
		system("cls");
		start();
	}
	else{
		cout << "\n������� �� ����!" << endl;
		exit(0);
	}

};