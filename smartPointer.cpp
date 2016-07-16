//スマートポインタ more effective C++ ch.28
#include <iostream>
#include <complex>
using namespace std;

template<typename T>
class auto_ptr
{
private:
    T* pointee;
    //template<typename U> 
    //friend class auto_ptr<U>;
public:
    explicit auto_ptr(T *p = nullptr) : pointee(p) {}
    
    //暗黙の型変換を許容する
    template<class U>
    auto_ptr(auto_ptr<U>& rhs) : pointee(rhs.release()) {}
    
    ~auto_ptr() 
    {
        delete pointee;
    }
    
    template<class U>
    auto_ptr<T>& operator=(auto_ptr<U>& rhs)
    {
        if(this != &rhs) reset(rhs.release() );
        return *this;
    }
    
    T& operator*() const
    {
        return *pointee;
    }
    
    T* operator->() const
    {
        return pointee;
    }
    
    T* get() const
    {
        return pointee;
    }
    
    T* release()
    {
        T* old = pointee;
        pointee = nullptr;
        return old;
    }
    
    void reset(T *p = 0)
    {
        if(pointee != p)
        {
            delete pointee;
            pointee = p;
        }
    }
};


int main(void)
{
    auto_ptr<double> m(new double());
    auto_ptr<complex<double>> cm(new complex<double>(3.0, 4.0));
    cout << *m << endl;
    cout << cm->real() << endl;
    
    auto_ptr<complex<double>> cm2 = cm;
    cout << cm2->real() << endl;
    cout << cm->real() << endl;
    return 0;
}