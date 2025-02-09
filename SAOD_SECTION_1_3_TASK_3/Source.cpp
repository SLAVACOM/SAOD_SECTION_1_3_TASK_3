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
		cout << "������ ����" << endl;
		return;
	}
	cout << "������ �������� ("<<arraySize<< '/' << (ARRAY_SIZE -1) << "):" << endl;
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
		cout << "������ ��������" << endl;
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
			cout << "������� �� ������, ������� ������� �������� � �����" << endl;
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
	cout << "������� ��������" << endl;
}

void pop(string value) {
	if (isEmpty()) {
		cout << "������ ����" << endl;
		return;
	}
	int i = list[0].next;
	int prev = 0;
	while (i != 0 && list[i].value != value) {
		prev = i;
		i = list[i].next;
	}

	if (i == 0) {
		cout << "������� �� ������" << endl;
		return;
	}

	list[prev].next = list[i].next;
	list[i].next = -1;
	arraySize--;
	cout << "������� '" << value << "' ������ �� ������." << endl;
}

void find(string value) {
	if (isEmpty()) {
		cout << "������ ����" << endl;
		return;
	}
	int i = 1;
	while (list[i].next != -1) {
		if (list[i].value == value) {
			cout << "������� ������: " << list[i].value << endl;
			return;
		}
		i++;
	}
	cout << "������� �� ������" << endl;
}


void menu(bool& exit) {
	cout << endl << "����:" << endl;
	cout << "1. ������� ������" << endl;
	cout << "2. ������ �� ������" << endl;
	cout << "3. ��������� ������ �� ������" << endl;
	cout << "4. �������� ������" << endl;
	cout << "5. ������� �������" << endl;
	cout << "6. ����� �������" << endl;
	cout << "7. �������� ������" << endl;
	cout << "0. �����" << endl;
	int choice = validIntegerInput("�������� ��������: ");
	string value, target;
	bool after;
	switch (choice) {
	case 1:
		print();
		break;
	case 2:
		cout << "������ " << (isEmpty() ? "����" : "�� ����") << endl;
		break;
	case 3:
		cout << "������ " << (isFull() ? "�����" : "�� �����") << endl;
		break;

	case 4:
		cout << "������� �������� ��������: ";
		cin.ignore();
		getline(cin, value);
		cout << "�������� ����� (1) ��� ����� (0) ���������? ";
		cin >> after;
		if (!isEmpty()) {
			cout << "������� ������� �������: ";
			cin.ignore();
			getline(cin, target);
		}
		push(value, target, after);
		break;
	case 5:
		cout << "������� �������� �������� ��� ��������: ";
		cin.ignore();
		getline(cin, value);
		pop(value);		
		break;
	case 6:
		cout << "������� �������� �������� ��� ������: ";
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
		cout << "�������� �����" << endl;
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