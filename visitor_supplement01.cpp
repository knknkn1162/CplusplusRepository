//S��T�͕ʂ̎�ނ̃N���X�����A���̂܂܂ł̓I�[�o�[���[�h�ł��Ȃ��I
//��������̓e���v���[�g�p�����[�^������ւ���Ă��邾��������B
#include <iostream>
using namespace std;

template<typename S, typename T>
S func(S s, T t)
{
    return s*t;
}

//template<typename S, typename T>
//T func(T t, S s)
//{
//    return S();
//}

template<typename S>
S func(S s1, S s2)
{
    return s1*s2;
}

//template<typename T>
//T func(T t1, T t2)
//{
//    return T();
//}

int main(void)
{
    cout << func(1, 1.5) << endl;
    cout << func(1.5, 2.3) << endl;
    return 0;
}