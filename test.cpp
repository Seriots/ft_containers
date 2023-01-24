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

	for (int i = 11; i >= 0; i--)
	{
		//red ascii color
		std::cout << "\033[1;31mInserting: " << i << "\033[0m" << std::endl;
		tree.insert(ft::make_pair(i, i));
		tree.display();
	}
}