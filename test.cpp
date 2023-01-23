#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <fstream>

#include "vector.hpp"
#include "utils.hpp"
#include "lexicographical_compare.hpp"

void	display_vector(ft::vector<int> v)
{
	std::cout << v.size() << " " << v.capacity() << " " << v.max_size() << " " << v.empty() << " ";
	for (size_t i = 0; i < v.size(); i++)
		std::cout << v[i] << " ";
	std::cout << std::endl;
}

void	display_vector(std::vector<int> v)
{
	std::cout << v.size() << " " << v.capacity() << " " << v.max_size() << " " << v.empty() << " ";
	for (size_t i = 0; i < v.size(); i++)
		std::cout << v[i] << " ";
	std::cout << std::endl;
}
template <class Value>
bool	comparator_equal(Value& first, Value& second)
{
	return (first == second);
}


void	test_vector_constructor()
{
	std::cout << "<Vector Constructor>" << std::endl;
	
	std::vector<int> a;

	a.push_back(1);
	a.push_back(2);
	a.push_back(3);
	a.push_back(4);
	a.push_back(5);

		std::vector<int> a2;

	a2.push_back(1);
	a2.push_back(2);
	a2.push_back(3);
	a2.push_back(4);
	a2.push_back(5);

	std::cout << "a == a2: " << ft::lexicographical_compare(a.begin(), a.end(), a2.begin(), a2.end(), comparator_equal<int>) << std::endl;
	//ft::vector<int> v5(std::allocator<int>);

}

int	main(void)
{
	test_vector_constructor();
}