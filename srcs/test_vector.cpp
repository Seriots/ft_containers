/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_vector.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgiband <lgiband@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 10:51:17 by lgiband           #+#    #+#             */
/*   Updated: 2023/01/23 19:20:06 by lgiband          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <string>
#include <list>
#include <fstream>
#include <vector>
#include <typeinfo>

#include "utils.hpp"

#if NAMESPACE == 0
	namespace ft = std;
#else
	#include "vector.hpp"
#endif

#include "utils.hpp"

extern std::string name;

void	display_vector(ft::vector<int> &v, std::ofstream& out)
{
	out << v.size() << " " << v.capacity() << " " << v.empty() << " ";
	for (size_t i = 0; i < v.size(); i++)
		out << v[i] << " ";
	out << std::endl;
}

void	display_vector_content(ft::vector<int> &v, std::ofstream& out, std::string prompt)
{
	out << prompt << " ";
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

	v1 = v3;
	ft::vector<int, std::allocator<int> > v5;

	//v1 = v1;
	v1[0] = 1;
	v3[0] = 1;
	v3[1] = 21;
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

void	test_vector_iterator(std::ofstream &out)
{
	out << "<Vector Iterator>" << std::endl;

	std::vector<int> a;

	a.push_back(1);
	a.push_back(2);
	a.push_back(3);
	a.push_back(4);
	a.push_back(5);

	ft::vector<int> v(a.begin(), a.end());

	out << "<Set: v={1, 2, 3, 4, 5}>" << std::endl;

	out << "v.begin() = " << *v.begin() << std::endl;
	out << "v.end() = " << *(v.end() - 1) << std::endl;
	out << "v.rbegin() = " << *v.rbegin() << std::endl;
	out << "v.rend() = " << *(v.rend() - 1) << std::endl;

	out << "v.begin() + 2 = " << *(v.begin() + 2) << std::endl;
	out << "v.end() - 2 = " << *(v.end() - 2) << std::endl;
	out << "v.rbegin() + 2 = " << *(v.rbegin() + 2) << std::endl;
	out << "v.rend() - 2 = " << *(v.rend() - 2) << std::endl;
}

void	test_vector_comparison(std::ofstream &out)
{
	out << "<Vector Comparison>" << std::endl;

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
	ft::vector<int> v3(a.begin(), a.end());
	ft::vector<int> v4;

	out << "<Set a={1, 2, 3, 4, 5}, a2={6, 7, 8, 9, 10}>" << std::endl;
	out << "<Set a3={1, 2, 3, 4, 5}>" << std::endl;

	//std::cout << typeid(*v.begin()).name() << std::endl;
	//std::cout << typeid(a).name() << std::endl;
	out << "v == v2 = " << (v == v2) << std::endl;
	out << "v == v3 = " << (v == v3) << std::endl;
	out << "v == v4 = " << (v == v4) << std::endl;
	out << "v != v2 = " << (v != v2) << std::endl;
	out << "v != v3 = " << (v != v3) << std::endl;
	out << "v != v4 = " << (v != v4) << std::endl;
	out << "v < v2 = " << (v < v2) << std::endl;
	out << "v < v3 = " << (v < v3) << std::endl;
	out << "v < v4 = " << (v < v4) << std::endl;
	out << "v <= v2 = " << (v <= v2) << std::endl;
	out << "v <= v3 = " << (v <= v3) << std::endl;
	out << "v <= v4 = " << (v <= v4) << std::endl;
	out << "v > v2 = " << (v > v2) << std::endl;
	out << "v > v3 = " << (v > v3) << std::endl;
	out << "v > v4 = " << (v > v4) << std::endl;
	out << "v >= v2 = " << (v >= v2) << std::endl;
	out << "v >= v3 = " << (v >= v3) << std::endl;
	out << "v >= v4 = " << (v >= v4) << std::endl;

	out << "<Swap>" << std::endl;
	
	out << "<From :>" << std::endl;
	display_vector(v, out);
	display_vector(v2, out);

	ft::swap(v, v2);
	
	out << "<To :>" << std::endl;
	display_vector(v, out);
	display_vector(v2, out);

	out << "<From :>" << std::endl;
	display_vector(v, out);
	display_vector(v4, out);

	ft::swap(v, v4);
	
	out << "<To :>" << std::endl;
	display_vector(v, out);
	display_vector(v4, out);
}

void	test_vector_assign(std::ofstream &out)
{
	out << "<Vector Assign>" << std::endl;

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
	a2.push_back(11);
	a2.push_back(12);
	a2.push_back(13);
	a2.push_back(14);
	a2.push_back(15);

	ft::vector<int> v(a.begin(), a.end());
	ft::vector<int> v2(a2.begin(), a2.end());
	ft::vector<int> v3(a.begin(), a.end());

	out << "<Set v={1, 2, 3, 4, 5}>\n<Set v2={6, 7, 8, 9, 10, 11, 12, 13, 14, 15}>\n<Set v={1, 2, 3, 4, 5}>" << std::endl;
	
	display_vector(v, out);

	out << "<Set v=v2>" << std::endl;
	v.assign(v2.begin(), v2.end());
	display_vector(v, out);
	out << "<Set v=v3>" << std::endl;
	v.assign(v3.begin(), v3.end());
	display_vector(v, out);

	ft::vector<int> v4(a.begin(), a.end());

	v4.assign((size_t)10, 42);
	out << "<Set v4.assign(10, 42)>" << std::endl;
	display_vector(v4, out);
	
	v4.assign((size_t)2, 21);
	out << "<Set v4.assign(2, 21)>" << std::endl;
	display_vector(v4, out);
}

void	test_vector_pushback_ten(std::ofstream& out)
{
	out << "<Vector Pushback 10>" << std::endl;

	ft::vector<int>	v;

	for (int i = 0; i < 10; i++)
		v.push_back(i);
	out << v.size() << " " << v.capacity() << " " << v.empty() << std::endl;

}

void	test_vector_pushback_hundred(std::ofstream& out)
{
	out << "<Vector Pushback 100>" << std::endl;

	ft::vector<int>	v;

	
	for (int i = 0; i < 100; i++)
		v.push_back(i);
	out << v.size() << " " << v.capacity() << " " << v.empty() << std::endl;

}

void	test_vector_pushback_thousands(std::ofstream& out)
{
	out << "<Vector Pushback 1000>" << std::endl;

	ft::vector<int>	v;
	
	for (int i = 0; i < 1000; i++)
		v.push_back(i);
	out << v.size() << " " << v.capacity() << " " << v.empty() << std::endl;
}

void	test_vector_pushback_too_many(std::ofstream& out)
{
	out << "<Vector Pushback 1000000>" << std::endl;

	ft::vector<int>	v;
	
	for (int i = 0; i < 1000000; i++)
		v.push_back(i);
	out << v.size() << " " << v.capacity() << " " << v.empty() << std::endl;
}

void	test_vector_pop(std::ofstream &out)
{
	out << "<Vector Pop>" << std::endl;
	
	ft::vector<int> v;

	for (int i = 0; i < 10; i++)
	{	
		for (int i = 0; i < 10; i++)
			v.push_back(i);
		display_vector(v, out);
		
		for (int i = 0; i < 10; i++) //std crash if pop_back() is called on empty vector
			v.pop_back();
		display_vector(v, out);

	}
}

void	test_vector_insert(std::ofstream& out)
{
	out << "<Vector Insert>" << std::endl;

	ft::vector<int> v;

	for (int i = 0; i < 7; i++)
		v.push_back(i);

	for (int i = 0; i < 10; i++)
	{
		v.insert(v.begin() + 3, 10 + i);
		display_vector(v, out);
	}
	for (int i = 0; i < 10; i++)
	{
		v.insert(v.begin(), 20 + i);
		display_vector(v, out);
	}
	out << "v.insert(v.begin() + 3, 100 + i) = " << *(v.insert(v.begin() + 3, 100 + 15)) << std::endl;
}

void	test_vector_insert_fill(std::ofstream& out)
{
	out << "<Vector Insert Fill>" << std::endl;

	ft::vector<int> v;

	for (int i = 0; i < 7; i++)
		v.push_back(i);

	v.insert(v.begin() + 3, (size_t)10, 42);
	display_vector(v, out);
	v.push_back(42);
	display_vector(v, out);

	v.insert(v.begin() + 8, (size_t)1000, 21);
	display_vector(v, out);
}

void	test_vector_insert_range(std::ofstream& out)
{
	out << "<Vector Insert Range>" << std::endl;

	ft::vector<int> v;
	ft::vector<int> v2;
	ft::vector<int> v3;

	for (int i = 0; i < 7; i++)
		v2.push_back(i);

	for (int i = 0; i < 10; i++)
		v.push_back(i);

	out << "<Set v: >" << std::endl;
	display_vector(v, out);
	out << "<Set: v2.insert(v2.begin() + 3, v.begin(), v.end())>" << std::endl;
	v2.insert(v2.begin() + 3, v.begin(), v.end());
	display_vector(v2, out);
	v2.push_back(42);
	display_vector(v2, out);

	out << "<Set same x20000>" << std::endl;
	for (int i = 0; i < 2000; i++)
		v2.insert(v2.begin(), v.begin(), v.end());
	display_vector_content(v2, out, "v2: ");

	out << "<Set v3 empty and run v x20000>" << std::endl;
	for (int i = 0; i < 2000; i++)
		v3.insert(v3.begin(), v.begin(), v.end());
	v3.push_back(42);
	display_vector_content(v3, out, "v3: ");
}

void	test_vector_insert_toomany(std::ofstream& out)
{
	out << "<Vector Insert Too Many>" << std::endl;

	ft::vector<int> v;

	for (int i = 0; i < 10000; i++)
		v.insert(v.begin(), i);
	display_vector(v, out);
}

void	test_vector_erase(std::ofstream &out)
{
	out << "<Vector Erase>" << std::endl;
	
	ft::vector<int> v;
	ft::vector<int> v2;
	
	for (int i = 0; i < 10; i++)
		v.push_back(i);

	for (int i = 0; i < 10000; i++)
		v2.push_back(i);
		
	out << "ret: " << *(v.erase(v.begin() + 3)) << std::endl;
	out << "ret: " << *(v2.erase(v2.begin() + 3, v2.begin() + 7)) << std::endl;

	display_vector(v, out);
	display_vector(v2, out);

	for (int i = 0; i < 4000; i++)
		v2.erase(v2.begin() + 2);
	display_vector(v2, out);
}

void	test_vector_clear(std::ofstream &out)
{
	out << "<Vector Clear>" << std::endl;
	
	ft::vector<int> v;

	for (int i = 0; i < 10; i++)
		v.push_back(i);

	display_vector(v, out);
	v.clear();
	display_vector(v, out);
}

void	test_vector_swap(std::ofstream &out)
{
	out << "<Vector Swap>" << std::endl;

	ft::vector<int> v;
	ft::vector<int> v2;

	for (int i = 0; i < 10; i++)
		v.push_back(i);

	for (int i = 0; i < 10000; i++)
		v2.push_back(i);

	display_vector(v, out);
	display_vector(v2, out);
	v.swap(v2);
	display_vector(v, out);
	display_vector(v2, out);
	v.swap(v);
	display_vector(v, out);
}

void	test_vector_resize(std::ofstream &out)
{
	out << "<Vector Resize>" << std::endl;

	ft::vector<int> v;
	
	for (int i = 0; i < 10; i++)
		v.push_back(i);
	
	display_vector(v, out);
	v.resize(5);
	display_vector(v, out);
	for (int i = 0; i < 10; i++)
		v.push_back(i);
	v.resize(20, 42);
	display_vector_content(v, out, "v.resize(20, 42): ");
	v.resize(118, 21);
	display_vector_content(v, out, "v.resize(118, 21): ");
	v.resize(1000000, 5);
	display_vector_content(v, out, "v.resize(100000, 5): ");
}

void	test_vector(std::ofstream &out)
{
	out << name << "vector" << std::endl;

		void	(*fonc[])(std::ofstream&) = {&test_vector_constructor, &test_vector_element_access, &test_vector_iterator,
										&test_vector_comparison, &test_vector_assign,
										&test_vector_pushback_ten, &test_vector_pushback_hundred, &test_vector_pushback_thousands,
										&test_vector_pushback_too_many, &test_vector_pop, &test_vector_insert,
										&test_vector_insert_toomany, &test_vector_insert_fill, &test_vector_insert_range,
										&test_vector_erase, &test_vector_swap, &test_vector_clear, &test_vector_resize};
	//std::cout  << "\n";
	for (long unsigned int i = 0; i < sizeof(fonc) / sizeof(fonc[0]); i++)
	{
		std::cout << "\33[2K\r" << "\033[0;33m"
			<< "[" << progressBar(i, sizeof(fonc) / sizeof(fonc[0]), 40, '=') << "]  "
			<< i << "/" << sizeof(fonc) / sizeof(fonc[0]) << "\033[0m"
			<< std::flush;
		time_test(fonc[i], out);
	}
	
}