//コンセプトをもとにインターフェースの差異を吸収する。(head first design patternのadapter patternのtemplate version)
#include <iostream>
#include <memory>
using namespace std;

/*既存ライブラリ群*/
//具象化クラス
class MallardDuck
{
public:
	void quack() const
	{
		cout << "Quack" << endl;
	}
	
	void fly() const
	{
		cout << "I'm flying" << endl;
	}
};

class WildTurkey
{
public:
	void gobble() const
	{
		cout << "Gobble : gobble" << endl;
	}
	
	void fly() const
	{
		cout << "I'm flying a short distance" << endl;
	}
};


//あらゆる動物型が持つインターフェースを統合するための中間インターフェース
template<class T>
struct animal_traits
{
    static void makeSound(const T&);
    static void fly(const T&);
};

//特殊化
template<>
struct animal_traits<MallardDuck>
{
    static void makeSound(const MallardDuck& animal)
    {
        animal.quack();
    }

    static void fly(const MallardDuck& animal)
    {
        animal.fly();
    }
};

//特殊化
template<>
struct animal_traits<WildTurkey>
{
    static void makeSound(const WildTurkey& animal)
    {
        animal.gobble();
    }
    static void fly(const WildTurkey& animal)
    {
        constexpr int N = 5;
        for(int i = 0; i < N; i++)
        {
            animal.fly();
        }
    }
};

//ヘルパー関数
template<class Animal>
void makeSound(const Animal& animal)
{
    animal_traits<Animal>::makeSound(animal);
}

template<class Animal>
void fly(const Animal& animal)
{
    animal_traits<Animal>::fly(animal);
}


int main(void)
{
    WildTurkey wt;
    MallardDuck md;
    
    makeSound(wt); fly(wt);
    makeSound(md); fly(md);
    
    return 0;
}