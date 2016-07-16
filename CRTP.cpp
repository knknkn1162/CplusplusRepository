#include <iostream>
#include <memory>
using namespace std;

//CRTPÇ…ÇÊÇÈê√ìIåpè≥
template<typename Derived>
class QuackBehavior
{
public:
	void quack() const
	{
		static_cast<const Derived&>(*this).quack_derived();
	}
	static void quack(const Derived& d)
	{
		d.quack_derived();
	}
};

//makeä÷êî
template<typename Derived>
void quack(const Derived& d)
{
	QuackBehavior<Derived>::quack(d);
}

class Quack : public QuackBehavior<Quack>
{
public:
	void quack_derived() const
	{
		cout << "gua-gua" << endl;
	}
};
class Squeak : public QuackBehavior<Squeak>
{
public:
	void quack_derived() const
	{
		cout << "kyu-kyu" << endl;
	}
};
class Mute : public QuackBehavior<Mute>
{
public:
	void quack_derived() const
	{
		cout << "<<mute>>" << endl;//Do Nothing;
	}
};


template<typename T>
class Duck
{
private:
	T q;
public:
	void quack() const
	{
		q.quack();
		::quack(q); //makeä÷êîÇÃÇåƒÇ‘
		QuackBehavior<T>::quack(q);
	}
};


class MallardDuck : public Duck<Quack>
{
private:
public:
	void anotherMethod1() {}
};

class RubberDuck : public Duck<Squeak>
{
private:
public:
	void anotherMethod2() {}
};

class DecoyDuck : public Duck<Mute>
{
private:
public:
	void anotherMethod3() {}
};

int main(void)
{
	auto d1 = MallardDuck();
	auto d2 = RubberDuck();
	auto d3 = DecoyDuck();
	
	d1.quack();
	d2.quack();
	d3.quack();
	cout << endl;

	

	return 0;
}