//タグディスパッチ(点クラスと線クラスをget_geometry_categoryにより、ふるい分け)をコンセプトにより、実現する(動的タグディスパッチだと、Visitor Patternをもちいる？)
#include <iostream>
#include <cmath>
using namespace std;

//点クラス(既存ライブラリ)
class Point //インターフェ―スの異なる(例：x() => getX()とかの違いがある)クラス
{
private:
    double x_ = 0;
    double y_ = 0;
public:
    Point() = default;
    Point(double x, double y) : x_(x), y_(y) {}
    
    double x() const { return x_; }
    double y() const { return y_; }
};

//線クラス(既存ライブラリ)
template<class Point>
class line_segment
{
private:
    Point p1_;
    Point p2_;
public:
    using point_type = Point;
    line_segment() = default;
    line_segment(const Point& p1, const Point& p2) : p1_(p1), p2_(p2) {}
    
    const Point& p1() const { return p1_; }
    const Point& p2() const { return p2_; }
};


struct point_category {};
struct line_segment_category {};
//タグディスパッチ(Point => point_category, line_segment<Point> => line_segment_categoryと振り分ける)を行うメタ関数
template<class T>
struct get_geometry_category;

template<>
struct get_geometry_category<Point>
{
    using type = point_category;
};

template<>
struct get_geometry_category<line_segment<Point>>
{
    using type = line_segment_category;
};


template<class Point>
double distance_impl(Point a, Point b, point_category, point_category);
template<class Point, class LineSegment>
double distance_impl(Point a, LineSegment b, point_category, line_segment_category);
template<class LineSegment, class Point>
double distance_impl(LineSegment b, Point a, line_segment_category, point_category);

//線と点との距離をdistance関数で汎用化する。
template<class Geometry1, class Geometry2>
double distance(Geometry1 g1, Geometry2 g2)
{
    return distance_impl(g1, g2,
                         typename get_geometry_category<Geometry1>::type(), typename get_geometry_category<Geometry2>::type()
                         );
}

//test
int main(void)
{
    Point p1(0.0, 0.0);
    Point p2(2.0, 3.0);
    line_segment<Point> line(Point(2.0, 2.0), Point(2.0, 2.0));

    cout << distance(p1, p2) << endl;
    cout << distance(p1, line) << endl;
    cout << distance(line, p1) << endl;
    
    return 0;
}

template<class Point>
double distance_impl(Point a, Point b, point_category, point_category)
{
    const Point d = Point(a.x() - b.x(), a.y() - b.y());
    return std::sqrt(d.x() * d.x() + d.y() * d.y());
}
template<class Point, class LineSegment>
double distance_impl(Point a, LineSegment b, point_category, line_segment_category)
{
    return std::min(
        distance(a, b.p1()), distance(a, b.p2()) );
}
template<class LineSegment, class Point>
double distance_impl(LineSegment a, Point b, line_segment_category, point_category)
{
    return distance(b, a);
}





