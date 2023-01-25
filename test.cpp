#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <fstream>
#include <map>

#include "rbtree.hpp"
#include "pair.hpp"


int	main(void)
{

	ft::rbTree<int, int> tree;
	std::map<int, int> map;

	for (int i = 0; i < 6; i++)
	{
		//red ascii color
		std::cout << "\033[1;34mInserting: " << i << "\033[0m" << std::endl;
		tree.insert(ft::make_pair(i, i));
		map.insert(std::make_pair(i, i));
	}

	for (ft::rbTree<int, int>::iterator it = tree.begin(); it != tree.end(); it++)
		std::cout << it->first << std::endl;

	ft::rbTree<int, int>::iterator itest = tree.begin();
	std::map<int, int>::iterator itest2 = map.begin();
	//std::cout << (itest+2)->first << std::endl;
	//itest2 = itest2 + 2;
	
	std::cout << (itest[3]).first << std::endl;
	std::cout << (itest2)->first << std::endl;

	//tree.display();
}