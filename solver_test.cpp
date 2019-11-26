#include <iostream>

class T{
public:
	T(int a, double b) 
		: a_(a), b_(b)
	{}

	void print_value() {
		std::cout << "a = " << a_ << std::endl;
		std::cout << "b = " << b_ << std::endl;
	}

private:
	int a_;
	double b_;
};

void print_info(T *t) {
	t->print_value();
}

int main()
{
	T *t = new T(1, 2.0);

	print_info(t);
	delete t;
	t = nullptr;
}