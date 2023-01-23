#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <fstream>

#include "vector.hpp"
#include "utils.hpp"

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

void	test_vector_constructor()
{
	std::cout << "<Vector Constructor>" << std::endl;
	
	std::vector<int> a;

	a.push_back(1);
	a.push_back(2);
	a.push_back(3);
	a.push_back(4);
	a.push_back(5);

	ft::vector<int> v1;
	ft::vector<int> v2(v1);
	ft::vector<int> v3((size_t)5, 42);
	ft::vector<int> v4(a.begin(), a.end());
	std::vector<int> v5(a.begin(), a.end());

	//ft::vector<int> v5(std::allocator<int>);
	display_vector(v4);
	display_vector(v5);
}

int	main(void)
{
	test_vector_constructor();
}