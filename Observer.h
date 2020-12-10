#pragma once
#include "Ippo.h"

using namespace std;
class Observer //смотрящий класс, типа пользователь
{
	Ippo* model;
	string o_name;
public:
	Observer(Ippo* mod, string n);
	Observer();
	void update();
protected:
	Ippo* getSubject();
};

