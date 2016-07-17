//�R���Z�v�g�����ƂɃC���^�[�t�F�[�X�̍��ق��z������B(head first design pattern��adapter pattern��template version)
#include <iostream>
#include <memory>
using namespace std;

/*�������C�u�����Q*/
//��ۉ��N���X
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


//�����铮���^�����C���^�[�t�F�[�X�𓝍����邽�߂̒��ԃC���^�[�t�F�[�X
template<class T>
struct animal_traits
{
    static void makeSound(const T&);
    static void fly(const T&);
};

//���ꉻ
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

//���ꉻ
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

//�w���p�[�֐�
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