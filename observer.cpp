#include "Observer.h"

Observer::Observer(Ippo* mod, string n)
{
	model = mod;
	o_name = n;
	model->attach(this);
}

Observer::Observer()
{
	model = NULL;
}

void Observer::update()//приходит сюда после заврешения забега
{
	bool win = getSubject()->getwinner();
	cout << o_name;
	if (win)
	{
		cout << " выиграл " << '\n';
	}
	else
		cout << " проиграл " << '\n';
}

Ippo* Observer::getSubject()
{
	return model;
}

void Ippo::notify()
{
	views->update();
}

