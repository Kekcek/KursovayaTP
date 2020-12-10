#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

class Ippo
{
protected:
	class Observer* views;
	string por;
	string name;
	int year;
	int win;
	int speed;
	bool winner;
public:
	Ippo() {};
	Ippo(string por, string name, int year);
	void setspeed(int a);
	int getspeed();
	void setwin();
	int getwin();
	void setwinner(bool flag);
	bool getwinner();
	string getData(int type);
	void attach(Observer* obs);
	string myprint();
	void notify();
	~Ippo() {};
};

