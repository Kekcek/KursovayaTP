#include "Ippo.h"
#include "Observer.h"

#define FILE_DATA "File.txt"

void output_to_console(vector<Ippo> &myIppo) { // Вывод данных о лошади в консоль
	for (size_t i = 0; i < myIppo.size(); i++)
	{
		cout << "[" << i << "]" << myIppo[i].myprint() << endl;
	}
}

void add_new_horse(vector<Ippo>& myIppo)  //Добавление новой лощади
{
	try
	{
		int year;
		string poroda, imya;
		cout << "Введите имя лошади: ";
		cin >> imya;
		if (imya.empty())
			throw (string)"Поле не может быть пустым";
		cout << "Введите породу лошади: ";
		cin >> poroda;
		if(poroda.empty())
			throw (string)"Поле не может быть пустым";
		cout << "Введите год лошади: ";
		while (!(cin >> year) || (cin.peek() != '\n'))
		{
			cin.clear();
			while (cin.get() != '\n');
			throw (string)"Вводить нужно число.";
		}
		Ippo horse(poroda, imya, year);
		myIppo.push_back(horse);
	}
	catch (string err)
	{
		cout << err << endl;
		system("pause");
	}
}

void get_win(vector<Ippo>& myIppo, int input) // Выбор победителя
{
	int max = 0;
	for (int i = 1; i < myIppo.size(); i++)
	{
		if (myIppo[i].getwin() > myIppo[max].getwin())
		{
			max = i;
		}
	}
	if (input == max)
	{
		myIppo[input].setwinner(true);
	}
	else
		myIppo[input].setwinner(false);
}

void load_data(vector<Ippo>& myIppo) //Загрузка данных о лошадях из файла
{
	ifstream in; // Дескриптор файла
	in.open(FILE_DATA);
	if (!in)
		throw (string)"Ошибка открытия файла, файл с данными пуст";
	int god, col;
	string line, poroda, imya;
	getline(in, line);// Получаем первую строку в файле
	col = stoi(line);
	for (int i = 0; i < col; i++)
	{
		getline(in, poroda);
		getline(in, imya);
		getline(in, line);
		god = atoi(line.c_str());
		Ippo tmpHorse(poroda, imya, god);
		myIppo.push_back(tmpHorse);
	}
	in.close();
}

void save_data(vector<Ippo>& myIppo) // Сохранить данные о лошадях
{
	ofstream out(FILE_DATA);
	out << myIppo.size();
	out << '\0' << endl;
	for (size_t i = 0; i < myIppo.size(); i++)
	{
		out << myIppo[i].getData(1) << endl
			<< myIppo[i].getData(2) << endl
			<< myIppo[i].getData(3) << endl;
	}
	out.close();
}

int main()
{
	vector<Ippo> myIppo; // Массив лошадей

	ofstream out; // Дескриптор файла

	string tmp;

	Observer* obs1;
	setlocale(LC_ALL, "Rus"); // Ввывод русских символов
	try
	{
		load_data(myIppo);
	}
	catch (string err)
	{
		cout << err << endl;
		system("pause");
	}
	int input;
	int numst = 0;
	bool contin = true;
	while (true)
	{
		bool flag = false;
		do
		{
			try
			{
				system("cls");
				flag = true;
				cout << "Меню:" << endl
					<< "[1] Добавить лошадь" << endl
					<< "[2] Выбрать лошадь" << endl
					<< "[0] Выход" << endl
					<< "> ";
				while (!(cin >> input) || (cin.peek() != '\n'))
				{
					flag = false;
					cin.clear();
					while (cin.get() != '\n');
					throw (string)"Вводить нужно число.";
				}
				if (input < 0 || input > 2)
				{
					flag = false;
					throw (string)"Вводить нужно число от 0 до 2.";
				}
			}
			catch (string err)
			{
				cout << err << endl;
				system("pause");
			}
		} while (!flag);
		switch (input)
		{
		case 1:
			add_new_horse(myIppo);
			break;
		case 2:
			try
			{
				if (!myIppo.size())
				{
					cout << "Нет лошадей. Сначала добавьте лошадей" << endl;
					break;
				}
				cout << "Введите ваше имя" << endl;
				cin >> tmp;
				output_to_console(myIppo);
				cout << "Выберите лошадь" << endl;
				while (!(cin >> input) || (cin.peek() != '\n'))
				{
					flag = false;
					cin.clear();
					while (cin.get() != '\n');
					throw (string)"Вводить нужно число.";
				}
				if (input < 0 || input > myIppo.size() - 1)
				{
					flag = false;
					throw (string)"Вводить нужно число от 0 до 2.";
				}
				obs1 = new Observer(&myIppo[input], tmp);
				for (int i = 0; i < 5; i++)//количество забегов
				{
					cout << endl << endl << "Забег под номером " << i << endl
						<< "-------------------" << endl;
					for (int j = 0; j < myIppo.size(); j++)//все лошади на забеге
					{
						myIppo[j].setspeed(rand() % 50 + 1);
						cout << "Лошадь с номером " << j << " со скоростью " << myIppo[j].getspeed() << endl;
					}
					int max = 0;
					for (int j = 1; j < myIppo.size(); j++)
					{
						if (myIppo[j].getspeed() > myIppo[max].getspeed())
						{
							max = j;
						}
					}
					myIppo[max].setwin();
				}
				get_win(myIppo, input);
				out.open("out" + to_string(numst) + ".txt");
				for (int i = 0; i < myIppo.size(); i++)
				{
					out << myIppo[i].myprint() << endl;
				}
				out.close();
				numst++;
				delete obs1;
			}
			catch (string err)
			{
				cout << err << endl;
				system("pause");
			}
			break;
		case 0:
			save_data(myIppo);
			return 0;
		default:
			break;
		}
		system("pause");
	}
	return 0;
}
