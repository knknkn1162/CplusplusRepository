//プログラミング言語C++ 第4版　22.3.1 ダブルディスパッチ
#include <iostream>
#include <vector>
#include <utility>
using namespace std;

// Derived classes of Shape class.
class Circle;
class Triangle;
//class Rectangle; //A

class Shape
{
public:
    virtual bool intersect(const Shape&) const = 0;
    virtual bool intersect(const Circle&) const = 0;
    virtual bool intersect(const Triangle&) const = 0;
    //virtual bool intersect(const Rectangle&) const = 0; // B
};

//Shape Classに対する新しい派生クラス(たとえば、Rectangle)を追加するたびに、階層内の全クラス(具体的には、A ~ Eまで)を修正しなければならない。
class Circle : public Shape
{
public:
    bool intersect(const Shape& s) const override
    {
        return s.intersect(*this);
    }
    
    virtual bool intersect(const Circle&) const override
    {
        cout << "intersect(circle, circle)" << endl;
        return true;
    }
    
    virtual bool intersect(const Triangle&) const override
    {
        cout << "intersect(triangle, circle)" << endl;
        return true;
    }
	/* //C
    virtual bool intersect(const Rectangle&) const override
    {
        cout << "intersect(rectangle, circle)" << endl;
        return true;
    }
	*/
};

class Triangle : public Shape
{
public:
    bool intersect(const Shape& s) const override
    {
        return s.intersect(*this);
    }
    
    virtual bool intersect(const Circle&) const override
    {
        cout << "intersect(circle, triangle)" << endl;
        return true;
    }
    
    virtual bool intersect(const Triangle&) const override
    {
        cout << "intersect(triangle, triangle)" << endl;
        return true;
    }
	/* //D
    virtual bool intersect(const Rectangle&) const override
    {
        cout << "intersect(rectangle, triangle)" << endl;
        return true;
    }
	*/
};

/* //E
class Rectangle : public Shape
{
public:
    bool intersect(const Shape& s) const override
    {
        return s.intersect(*this);
    }
    
    virtual bool intersect(const Circle&) const override
    {
        cout << "intersect(circle, rectangle)" << endl;
        return true;
    }
    
    virtual bool intersect(const Triangle&) const override
    {
        cout << "intersect(triangle, rectangle)" << endl;
        return true;
    }
	
    virtual bool intersect(const Rectangle&) const override
    {
        cout << "intersect(rectangle, rectangle)" << endl;
        return true;
    }
};
*/


//void test(Triangle& t, Circle& c, Rectangle& r)
void test(Triangle& t, Circle& c)
{
    vector<pair<Shape*, Shape*>> vs = { {&t, &t}, {&t, &c}, {&c, &t}, {&c, &c} };
    // vector<pair<Shape*, Shape*>> vs = { 
        // {&t, &t}, {&t, &c}, {&t, &r},
        // {&c, &t}, {&c, &c}, {&c, &r},
        // {&r, &t}, {&r, &c}, {&r, &r},
    // }; 
    for(auto p : vs)
    {
        p.first->intersect(*(p.second));
    }
}

int main(void)
{
    Triangle t;
    Circle c;
    //Rectangle r;
	test(t, c);
    //test(t, c, r);
    
    return 0;
}