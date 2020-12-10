#include "Ippo.h"

Ippo::Ippo(string por, string name, int year)
{
	this->por = por;
	this->name = name;
	this->year = year;
	this->win = 0;
	views = NULL;
}

void Ippo::setspeed(int a)
{
	this->speed = a;
}

int Ippo::getspeed()
{
	return this->speed;
}

void Ippo::setwin()
{
	this->win++;
}

int Ippo::getwin()
{
	return this->win;
}

void Ippo::setwinner(bool flag)
{
	this->winner = flag;
	notify();
}

bool Ippo::getwinner()
{
	return this->winner;
}

string Ippo::getData(int type)
{
	switch (type)
	{

	case 1:
		return por;
	case 2:
		return name;
	case 3:
		return to_string(year);
	default:
		throw (string)"Не правильный индекс для вызова данных";
	}
}

void Ippo::attach(Observer* obs) {
	views = (obs);
}

string Ippo::myprint()
{
	string res, res1;
	res = "name: " + this->name + " poroda: " + this->por;
	res += " year: " + to_string(this->year);
	res += " win: " + to_string(this->win);
	res += " speed: " + to_string(this->speed);
	return res;
}
