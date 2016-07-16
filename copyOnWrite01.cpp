#include <iostream>

class Point
{
private:
    int xval;
    int yval;
public: 
    Point() : xval(0), yval(0) {}
    Point(int x, int y) : xval(x), yval(y) {}
    int x() const {return xval;}
    int y() const {return yval;}
    
    Point& x(int xv) { xval = xv; return *this;}
    Point& y(int yv) { yval = yv; return *this;}
};



class Handle
{
private:
    class UPoint
    {
    public:
        Point p;
        int u;
        UPoint() : u(1) {}
        UPoint(int x, int y) : p(x, y), u(1) {}
        UPoint(const Point& p0) : p(p0), u(1) {}  
    };
    UPoint* up;
public:
    Handle() : up(new UPoint()) {}
    Handle(int x, int y) : up(new UPoint(x, y)) {}
    Handle(const Point& p) : up(new UPoint(p)) {}
    Handle(const Handle& h) : up(h.up) { ++up->u; }
    Handle& operator=(const Handle& h)
    {
        ++h.up->u;
        if(--up->u == 0)
            delete up;
        up = h.up;
        return *this;
    }
    ~Handle() {}
    
    int x() const {return up->p.x(); }
    Handle& x(int x0)
    {
        if(up->u != 1)
        {
            --up->u;
            up = new UPoint(up->p);
        }
        up->p.x(x0);
        return *this;
    }
    int y() const {return up->p.y(); }
    Handle& y(int y0)
    {
        if(up->u != 1)
        {
            --up->u;
            up = new UPoint(up->p);
        }
        up->p.y(y0);
        return *this;
    }
};


int main(void)
{
    Handle h(6,7);
    h.x(10);
    int n1 = h.x();
    int n2 = h.y();
    Handle h2 = h;
    std::cout << n1 << std::endl;
    std::cout << n2 << std::endl;
    std::cout << h2.x() << std::endl;
    return 0;
}