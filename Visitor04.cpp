//�v���O���~���O����C++ ��4�Ł@22.3.2 Visitor Pattern: �_�u���f�B�X�p�b�`�̉��P���@
//���Ȃ��Ƃ��A�錾�����ƁA��������(Impl)�̕������ł��Ă���FShape�̃T�u�N���X��ύX���Ȃ��Ă��AVisitor�N���X�̕ύX�݂̂ōςނƂ������_������B
#include <iostream>
#include <vector>
#include <utility>
#include <memory>
using namespace std;

// Derived classes of Shape class.
class Circle;
class Triangle;
//class Rectangle; //A

//intersect : Visitor �p�^�[����accept�ɑ���
//�T�u�N���X��Circle, Triangle�̎��ۂ̎����������B
class Visitor
{
public:
    virtual void intersect(Circle&) = 0;
    virtual void intersect(Triangle&) = 0;
	//virtual void intersect(Rectangle&) = 0; // B
};

class Shape
{
public:
    virtual void intersect(Visitor&) = 0;
};

class Circle : public Shape
{
public:
    void intersect(Visitor& v) override
    {
        v.intersect(*this);
    }
};

class Triangle : public Shape
{
public:
    void intersect(Visitor& v) override
    {
        v.intersect(*this);
    }
};

/*
class Rectangle : public Shape
{
public:
    void intersect(Visitor& v) override
    {
        v.intersect(*this);
    }
};
*/ // C


class CircleImpl : public Visitor
{
public:
    void intersect(Circle&) override
    {
        cout << "intersect(CircleImpl, circle)" << endl;
    }
    void intersect(Triangle&) override
    {
        cout << "intersect(CircleImpl, Triangle)" << endl;
    }
	/*
    void intersect(Rectangle&) override
    {
        cout << "intersect(CircleImpl, Rectangle)" << endl;
    }
	*/ //D
};

class TriangleImpl : public Visitor
{
public:
    void intersect(Circle&) override
    {
        cout << "intersect(TriangleImpl, circle)" << endl;
    }
    void intersect(Triangle&) override
    {
        cout << "intersect(TriangleImpl, Triangle)" << endl;
    }
	/*
    void intersect(Rectangle&) override
    {
        cout << "intersect(TriangleImpl, Rectangle)" << endl;
    }
	*/ //E
};

class RectangleImpl : public Visitor
{
public:
    void intersect(Circle&) override
    {
        cout << "intersect(RectangleImpl, circle)" << endl;
    }
    void intersect(Triangle&) override
    {
        cout << "intersect(RectangleImpl, Triangle)" << endl;
    }
	/*
    void intersect(Rectangle&) override
    {
        cout << "intersect(RectangleImpl, Rectangle)" << endl;
    }
	*/ // F
};

void traverse(Triangle& t, Circle& c /*, Rectangle& r */)
{
    shared_ptr<Visitor> v1(new CircleImpl());
    shared_ptr<Visitor> v2(new TriangleImpl());
	//shared_ptr<Visitor> v3(new RectangleImpl());
    vector<pair<Shape*, Visitor*>> vs = { {&t, v1.get()}, {&c, v1.get()}, {&t, v2.get()}, {&c, v2.get()} };
	
    // vector<pair<Shape*, Visitor*>> vs = {
	// {&t, v1.get()}, {&c, v1.get()},{&r, v1.get()},
	// {&t, v2.get()}, {&c, v2.get()},{&r, v2.get() },
	// {&t, v3.get()}, {&c, v3.get()}, {&r, v3.get() }
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
    traverse(t, c/*, r */);
    
    return 0;
}