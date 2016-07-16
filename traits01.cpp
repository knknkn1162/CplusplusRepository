// testUnion.cpp : �R���\�[�� �A�v���P�[�V�����̃G���g�� �|�C���g���`���܂��B
//
//#include "stdafx.h"
#include <iostream>

template<class T>
struct hoge_traits
{
	
};

template<typename T>
class Hoge
{
public:
	//typename�C���q��t����
	using traits_type = typename hoge_traits<T>::traits_type;
	traits_type func()
	{
		return hoge_traits<T>::f();
	}
private:
};


template<>
struct hoge_traits<char>
{
	using traits_type = char;
	static char f() { return 'A'; };
};


template<>
struct hoge_traits<int>
{
	using traits_type = int;
	static int f() { return 'A'; };
};



int main()
{

	Hoge<int> ch;
	std::cout << ch.func() << std::endl;

	Hoge<char> i;
	std::cout << i.func() << std::endl;
    
//   	Hoge<double> d;
//	std::cout << d.func() << std::endl;
    return 0;
}

