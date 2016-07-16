#include <iostream>
#include <memory>
using namespace std;


class Quack
{
public:
	static void quack()
	{
		cout << "gua-gua" << endl;
	}
};
class Squeak
{
public:
	static void quack()
	{
		cout << "kyu-kyu" << endl;
	}
};
class Mute
{
public:
	static void quack()
	{
		cout << "<<mute>>" << endl;//Do Nothing;
	}
};


class MallardDuck
{
private:
public:
	typedef Quack QuackBehavior;
	void quack() const
	{
		QuackBehavior::quack();
	}
	void anotherMethod1() {}
};

class RubberDuck
{
private:
public:
	typedef Squeak QuackBehavior;
	void quack() const
	{
		QuackBehavior::quack();
	}
	void anotherMethod2() {}
};

class DecoyDuck
{
private:
public:
	typedef Mute QuackBehavior;
	void quack() const
	{
		QuackBehavior::quack();
	}
	void anotherMethod3() {}
};

template<typename Duck>
void quack()
{
	Duck::QuackBehavior::quack();
}

template<typename Duck>
void quack(const Duck&)
{
	quack<Duck>();
}


int main(void)
{
	auto d1 = MallardDuck();
	auto d2 = RubberDuck();
	auto d3 = DecoyDuck();
	
	d1.quack();
	d2.quack();
	d3.quack();
	cout << endl;
	quack(d1);
	quack(d2);
	quack(d3);
	

	return 0;
}