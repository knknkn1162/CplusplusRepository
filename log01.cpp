#include <iostream>
#include <typeinfo>
using namespace std;


template<int N>
class Test
{
private:
public:
    static int num;
    int getNum() const
    {
        return num;
    }
};

template<int N>
int Test<N>::num = N;

int main(void)
{
    Test<4> n4;
    Test<7> n7;
    auto fn4 = &Test<4>::getNum;
    auto fn7 = &Test<7>::getNum;
    cout << n4.getNum() << endl;
    cout << n7.getNum() << endl;
    
    cout << &Test<4>::getNum << endl; //出力1とは？
    cout << fn4 << ":" << typeid(fn4).name() << endl;
    cout << &fn4 << endl;
    
    cout << &Test<7>::getNum << endl; //出力1とは？
    cout << fn7 << ":" << typeid(fn7).name() << endl;
    cout << &fn7 << endl;
    
    cout << Test<6>::num << endl;
    cout << Test<8>::num << endl;
    cout << &Test<6>::num << endl;
    cout << &Test<8>::num << endl;
}
    
    
    
    