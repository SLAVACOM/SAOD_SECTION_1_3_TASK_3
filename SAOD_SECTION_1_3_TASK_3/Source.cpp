#include <iostream>
#include <regex>
#include <windows.h>

using namespace std;	

const int ARRAY_SIZE = 10 + 1;

int  arraySize = 0;


int validIntegerInput(string message) {
	string input;
	regex valid("[1-9][0-9]*");
	do {
		cout << message;
		cin >> input;
	} while (!regex_match(input, valid));
	return stoi(input);
}

struct LinkedList {
	string value;
	int next;
} list[ARRAY_SIZE];

void initList() {
	list[0].next = 0;
	list[0].value = "HEAD";

	for (int i = 1; i < ARRAY_SIZE; i++) list[i].next = -1;
	arraySize = 0;
}

bool isEmpty() {
	return arraySize == 0;
}
bool isFull() {
	return arraySize == ARRAY_SIZE - 1;
}

void print() {
	if (isEmpty()) {
		cout << "Список пуст" << endl;
		return;
	}
	cout << "Список заполнен ("<<arraySize<< '/' << (ARRAY_SIZE -1) << "):" << endl;
	int i = 1;
	int current = list[0].next;
	while (current != 0) {
		cout << i << ") " << list[current].value << endl;
		current = list[current].next;
		i++;
	}
}

void push(string value, string target = "", bool afrer = true) {
	if (isFull()) {
		cout << "Список заполнен" << endl;
		return;
	}

	int i =1;
	while (i < ARRAY_SIZE && list[i].next != -1) i++;

	if (isEmpty()) {
		list[i].value = value;
		list[i].next = 0;
		list[0].next = i;
	}
	else {
		int pos = list[0].next;
		int prev = 0;
		while (pos != 0 && list[pos].value != target) {
			prev = pos;
			pos = list[pos].next;
		}
		if (pos == 0) {
			cout << "Элемент не найден, поэтому элемент добавлен в конец" << endl;
			pos = prev;
		}
		if (afrer) {
			list[i].next = list[pos].next;
			list[pos].next = i;
		}
		else {
			list[i].next = pos;
			list[prev].next = i;;
		}
		list[i].value = value;
	}
	arraySize++;
	cout << "Элемент добавлен" << endl;
}

void pop(string value) {
	if (isEmpty()) {
		cout << "Список пуст" << endl;
		return;
	}
	int i = list[0].next;
	int prev = 0;
	while (i != 0 && list[i].value != value) {
		prev = i;
		i = list[i].next;
	}

	if (i == 0) {
		cout << "Элемент не найден" << endl;
		return;
	}

	list[prev].next = list[i].next;
	list[i].next = -1;
	arraySize--;
	cout << "Элемент '" << value << "' удален из списка." << endl;
}

void find(string value) {
	if (isEmpty()) {
		cout << "Список пуст" << endl;
		return;
	}
	int i = 1;
	while (list[i].next != -1) {
		if (list[i].value == value) {
			cout << "Элемент найден: " << list[i].value << endl;
			return;
		}
		i++;
	}
	cout << "Элемент не найден" << endl;
}


void menu(bool& exit) {
	cout << endl << "Меню:" << endl;
	cout << "1. Вывести список" << endl;
	cout << "2. Пустой ли список" << endl;
	cout << "3. Проверить полный ли список" << endl;
	cout << "4. Добавить элемнт" << endl;
	cout << "5. Удалить элемент" << endl;
	cout << "6. найти элемент" << endl;
	cout << "7. Очистить список" << endl;
	cout << "0. Выход" << endl;
	int choice = validIntegerInput("Выберите действие: ");
	string value, target;
	bool after;
	switch (choice) {
	case 1:
		print();
		break;
	case 2:
		cout << "Список " << (isEmpty() ? "пуст" : "не пуст") << endl;
		break;
	case 3:
		cout << "Список " << (isFull() ? "полон" : "не полон") << endl;
		break;

	case 4:
		cout << "Введите значение элемента: ";
		cin.ignore();
		getline(cin, value);
		cout << "Добавить после (1) или перед (0) элементом? ";
		cin >> after;
		if (!isEmpty()) {
			cout << "Введите целевой элемент: ";
			cin.ignore();
			getline(cin, target);
		}
		push(value, target, after);
		break;
	case 5:
		cout << "Введите значение элемента для удаления: ";
		cin.ignore();
		getline(cin, value);
		pop(value);		
		break;
	case 6:
		cout << "Введите значение элемента для поиска: ";
		cin.ignore();
		getline(cin, value);
		find(value);
		break;
	case 7:
		initList();
		break;
	case 0:
		exit = true;
		break;
	default:
		cout << "Неверный выбор" << endl;
		break;
	}
}


int main() {
	setlocale(LC_ALL, "RUS");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	initList();
	bool exit = false;
	while (!exit) {
		menu(exit);
	}
	return 0;
}