/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_vector.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgiband <lgiband@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 10:51:17 by lgiband           #+#    #+#             */
/*   Updated: 2023/01/19 14:55:46 by lgiband          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <string>
#include <list>
#include <fstream>
#include <vector>

#if NAMESPACE == 0
	namespace ft = std;
#else
	#include "vector.hpp"
#endif

#include "utils.hpp"

extern std::string name;

void	display_vector(ft::vector<int> v, std::ofstream& out)
{
	out << v.size() << " " << v.capacity() << " " << v.max_size() << " " << v.empty() << " ";
	for (size_t i = 0; i < v.size(); i++)
		out << v[i] << " ";
	out << std::endl;
}

void	test_vector_constructor(std::ofstream& out)
{
	out << "<Vector Constructor>" << std::endl;
	
	std::vector<int> a;

	a.push_back(1);
	a.push_back(2);
	a.push_back(3);
	a.push_back(4);
	a.push_back(5);

	ft::vector<int> v1;
	ft::vector<int> v2(v1);
	ft::vector<int> v3((size_t)5, 42);
	ft::vector<int> v4(a.begin() + 2, a.end());

	ft::vector<int, std::allocator<int> > v5;

	display_vector(v1, out);
	display_vector(v2, out);
	display_vector(v3, out);
	display_vector(v4, out);
	display_vector(v5, out);
}

void	test_vector_element_access(std::ofstream& out)
{
	out << "<Vector Element Access>" << std::endl;

	std::vector<int> a;
	std::vector<int> a2;

	a.push_back(1);
	a.push_back(2);
	a.push_back(3);
	a.push_back(4);
	a.push_back(5);
	
	a2.push_back(6);
	a2.push_back(7);
	a2.push_back(8);
	a2.push_back(9);
	a2.push_back(10);
	
	ft::vector<int> v(a.begin(), a.end());
	ft::vector<int> v2(a2.begin(), a2.end());
	
	out << "<Set: v={1, 2, 3, 4, 5}, v2={6, 7, 8, 9, 10}>" << std::endl;
	
	out << "v.front() = " << v.front() << std::endl;
	out << "v2.front() = " << v2.front() << std::endl;
	out << "v.back() = " << v.back() << std::endl;
	out << "v2.back() = " << v2.back() << std::endl;
	out << "v[2] = " << v[2] << std::endl;
	out << "v2[2] = " << v2[2] << std::endl;
	out << "v.at(2) = " << v.at(2) << std::endl;
	out << "v2.at(2) = " << v2.at(2) << std::endl;
}

void	test_vector(std::ofstream &out)
{
	out << name << "vector" << std::endl;

	time_test(&test_vector_constructor, out);
	time_test(&test_vector_element_access, out);
}