#include <iostream>
#include <string>

template<typename T, int N>
void func()
{
	T data[N] = {T()}; //ƒ[ƒ‰Šú‰»
	for(int i = 0 ; i < N; i++)
	{
		std::cout << data[i] << std::endl;
	}	
}

class Test
{
private:
	double d;
public:
	Test() : d() {}
	friend std::ostream& operator<<(std::ostream& os, const Test& t)
	{
		os << t.d;
		return os;
	}
};

int main(void)
{
	func<int, 10>();
	func<std::string, 7>();
	func<Test, 8>();
	return 0;
}