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

	for (int i = 0; i < 50 ; i++)
	{
		//red ascii color
		std::cout << "\033[1;34mInserting: " << i << "\033[0m" << std::endl;
		tree.insert(ft::make_pair(i, i));
		map.insert(std::make_pair(i, i));
	}

	ft::rbTree<int, int> tree2(tree);

	for (int i = 20; i < 35 ; i++)
	{
		std::cout << "\033[1;34mErasing: " << i << "\033[0m" << std::endl;
		tree.remove(i);
		map.erase(i);

	}
	

	std::cout << "\033[1;34mTree1: \033[0m" << std::endl;
	tree.display();
	
	std::cout << "\033[1;34mTree2: \033[0m" << std::endl;
	tree2.display();

	//std::cout << "\033[1;34mIterator ++ :\033[0m" << std::endl;
	//for (std::map<int, int>::iterator it = map.begin(); it != map.end(); it++)
	//	std::cout << it->first << std::endl;
	//std::cout << std::endl;

	//for (ft::rbTree<int, int>::iterator it = tree.begin(); it != tree.end(); it++)
	//	std::cout << it->first << std::endl;
	//std::cout << std::endl;



	//std::cout << "\033[1;34mIterator -- :\033[0m" << std::endl;
	//for (std::map<int, int>::iterator it = --(map.end()); it != map.begin(); it--)
	//	std::cout << it->first << std::endl;
	//std::cout << std::endl;

	//for (ft::rbTree<int, int>::iterator it = --(tree.end()); it != tree.begin(); it--)
	//	std::cout << it->first  << std::endl;
	

	//std::cout << "\033[1;34mReverse Iterator ++ :\033[0m" << std::endl;
	//for (std::map<int, int>::reverse_iterator it = map.rbegin(); it != map.rend(); it++)
	//	std::cout << it->first << std::endl;
	//std::cout << std::endl;

	//for (ft::rbTree<int, int>::reverse_iterator it = tree.rbegin(); it != tree.rend(); it++)
	//	std::cout << it->first  << std::endl;
	

	//std::cout << "\033[1;34mReverse Iterator -- :\033[0m" << std::endl;
	//for (std::map<int, int>::reverse_iterator it = --(map.rend()); it != map.rbegin(); it--)
	//	std::cout << it->first << std::endl;
	//std::cout << std::endl;

	//for (ft::rbTree<int, int>::reverse_iterator it = --(tree.rend()); it != tree.rbegin(); it--)
	//	std::cout << it->first  << std::endl;

	//std::cout << (itest+2)->first << std::endl;
	//itest2 = itest2 + 2;
	
	//std::cout << (itest[3]).first << std::endl;

	//tree.display();
}