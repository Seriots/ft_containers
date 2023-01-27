/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_map.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgiband <lgiband@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 16:57:24 by lgiband           #+#    #+#             */
/*   Updated: 2023/01/27 17:59:43 by lgiband          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <iomanip>
#include <cstdlib>
#include <map>

#include "utils.hpp"

#if NAMESPACE == 0
	namespace ft = std;
#else
	#include "map.hpp"
#endif

#include "utils.hpp"

extern std::string name;

void	display_map(std::ofstream &out, ft::map<int, int> &map, std::string str = "")
{
	out << str << "s:" << map.size() << ", e:" << map.empty();
	for (ft::map<int, int>::iterator it = map.begin(); it != map.end(); it++)
		out << " " << it->first << ":" << it->second;
	out << std::endl;
}

void	test_constructor_map(std::ofstream &out)
{
	out << name << "constructor" << std::endl;

	ft::map<int, int>		map;

	for (int i = 0; i < 10; i++)
		map.insert(ft::make_pair(i, i * 2));

	ft::map<int, int>		map2(map);
	ft::map<int, int>		map3;
	ft::map<int, int>		map4(map.begin(), map.end());
	map3 = map2;

	out << "<Set map(),map2(map),map3=map2,map4(m.b(),m.e())>" << std::endl;

	display_map(out, map, "map: ");
	display_map(out, map2, "map2: ");
	display_map(out, map3, "map3: ");
	display_map(out, map4, "map4: ");

	out << "<Remove 1 element from each map>" << std::endl;
	map.erase(2);
	map2.erase(3);
	map3.erase(4);
	map4.erase(5);
	
	display_map(out, map, "map: ");
	display_map(out, map2, "map2: ");
	display_map(out, map3, "map3: ");
	display_map(out, map4, "map4: ");

	out << "<Set map4.clear(), map3=map4>" << std::endl;
	map4.clear();
	map3 = map4;

	display_map(out, map3, "map3: ");
	display_map(out, map4, "map4: ");
	
	map3.insert(ft::make_pair(1, 2));
	map3.insert(ft::make_pair(2, 4));
	map3.insert(ft::make_pair(3, 6));

	map4.insert(ft::make_pair(1, 2));

	display_map(out, map3, "map3: ");
	display_map(out, map4, "map4: ");
}

void	test_map(std::ofstream &out)
{
	out << name << "map" << std::endl;

		void	(*fonc[])(std::ofstream&) = {&test_constructor_map};
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