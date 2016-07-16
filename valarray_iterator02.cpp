#include <boost/iterator/iterator_adaptor.hpp>
#include <iostream>
#include <valarray>
using std::valarray;

class container : private valarray<int>
{
private:
public:
    struct iterator :
        public boost::iterator_adaptor<iterator, int *>
    {
        iterator(int *p) :
            iterator::iterator_adaptor_( p )
        { }
    };
    struct const_iterator :
        public boost::iterator_adaptor<const_iterator,const int *>
    {
        const_iterator(const int *p) :
            const_iterator::iterator_adaptor_( p )
        { }
    };
    using reverse_iterator = std::reverse_iterator<iterator>;
    using const_reverse_iterator = std::reverse_iterator<const_iterator>;

    container(int size) : valarray<int>(size) {}

    iterator begin()
    { return iterator( &(this->operator[](0)) ); }

    iterator end()
    { return iterator( &(this->operator[](size()))); }
    
    const_iterator cbegin() const
    { return const_iterator( &(this->operator[](0)) ); }

    const_iterator cend() const
    { return const_iterator( &(this->operator[](size()))); }
    
    reverse_iterator rbegin()
    {
        return reverse_iterator( &(this->operator[](size() )) );
    }
    reverse_iterator rend()
    {
        return reverse_iterator( &(this->operator[](0)) );
    }
    const_reverse_iterator crbegin() const
    {
        return const_reverse_iterator( &(this->operator[](size() )) );
    }
    const_reverse_iterator crend() const
    {
        return const_reverse_iterator( &(this->operator[](0)) );
    }

    using valarray<int>::operator[];
};

int main(void)
{
    container c(10);
    c[2] = 100;
    for( container::iterator itr = c.begin(); itr != c.end(); ++itr ) {
        std::cout << *itr << " ";
    }
    std::cout << std::endl;
    
    for( container::const_iterator itr = c.cbegin(); itr != c.cend(); ++itr ) {
        std::cout << *itr << " ";
    }
    std::cout << std::endl;
    for( container::reverse_iterator itr = c.rbegin(); itr != c.rend(); ++itr ) {
        std::cout << *itr << " ";
    }
    std::cout << std::endl;
    
    for(auto itr = c.crbegin(); itr != c.crend(); ++itr)
    {
        std::cout << *itr << " ";
    }
    std::cout << std::endl;
    
    return 0;
}