#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include "Windows.h"

using namespace std;

void entryMenu(); // функция для вывода главного меню
void registerMenu(); //функция для проведения регистрации пользователя и записи данных в файл
void signInMenu(); //функция для вывода меню входа
int getMenuChoice(); //функция для получения выбора пользователя из главного меню программы
bool isCorrectSign(string username, string password); //функция для проверки введенных имени и пароля на правильность

int main()
{
	setlocale(LC_ALL, "rus"); //устанавливаем русскую локализацию

	entryMenu(); //выводим главное меню на экран
	getMenuChoice(); //ждем ввода пользователя, и в зависимости от выбора исполняем другие функции

	return 0;
}

void entryMenu()
{
	system("cls");
	cout << "ГЛАВНОЕ МЕНЮ" << endl;
	cout << "1. Регистрация" << endl;
	cout << "2. Вход" << endl;
	cout << "3. Выход из программы" << endl;
	cout << "Выберите пункт: " << endl;
}

void registerMenu()
{
	system("cls");

	string username, password; //переменные для данных регистрации

	cout << "1. РЕГИСТРАЦИЯ" << endl;
	cout << "Введите имя пользователя: ";
	cin.get();
	getline(cin, username);

	cout << "Введите пароль: ";
	getline(cin, password);

	ofstream fout("data.txt"); //поток для записи данных в файл

	if (fout.is_open()) //если он открылся - записываем построчно в файл
	{
		fout << username << "\n";
		fout << password << endl;
		fout.close(); //закрываем поток
		cout << "Регистрация прошла успешно!" << endl; //выводим сообщение об успешной регистрации
	}
	else {
		cout << "Ошибка при записи в файл!" << endl;
	}
}

void signInMenu()
{
	system("cls");
	cout << "2. ВХОД" << endl;

	string input_username, input_password;

	cin.get();
	cout << "Введите имя пользователя:";
	getline(cin, input_username);

	cout << "Введите пароль для пользователя " <<input_password <<": ";
	getline(cin, input_password);

	if (isCorrectSign(input_username, input_password))
	{
		cout << "Вход выполнен успешно!" << endl;
	}
	else
	{
		cout << "Неверные имя пользователя или пароль!" << endl;
	}
}

int getMenuChoice()
{
	int choice; //переменная для выбора пользователя
	while (1) {
		cin >> choice; //считываем ее с клавиатуры

		switch (choice)
		{
		case 1: //меню регистрации
			registerMenu();
			cin.get(); //после успешной или неуспешной регистрации ждем нажатия кнопки и выводим главное меню
			entryMenu();
			break;
		case 2:
			signInMenu(); 
			cin.get();
			entryMenu();
			break;
		case 3:
			cout << "Нажмите любую клавишу для выхода ...";
			cin.get();
			exit(0);
		default:
			cout << "Неверный выбор!" << endl;
			cin.get();
			entryMenu();
		}
	} 
}

bool isCorrectSign(string username, string password)
{
	//создаем переменные для считывания введенных пользователем данных
	string valid_username,
		   valid_password;

	ifstream fin("data.txt"); //открываем файловый поток для считывания верных данных из файла

	if (fin.is_open()) //если поток открылся успешно
	{
		getline(fin, valid_username); //считываем из файла первую строку как имя пользователя
		getline(fin, valid_password); //вторую как пароль

		fin.close();

		if (username == valid_username && password == valid_password) return true; //сравниваем и если совпадают возвращаем значение "Правда" - данные совпадают

		//иначе вовзращается false в выходе из функции
	}
	else //если поток не открылся успешно - выводим ошибку
	{
		cout << "Ошибка чтения файла с данными!" << endl;
		cin.get();
	}

	return false;
}
