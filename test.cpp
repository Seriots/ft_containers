#include <iostream>
#include <vector>
#include "vector.hpp"

void	ft_resize(void)
{
    ft::vector<int> myvector;
    std::vector<int> stdvector;

    // set some initial content:
    for (int i=1;i<10;i++) myvector.push_back(i);
    for (int i=1;i<10;i++) stdvector.push_back(i);

    myvector.resize(5);
    stdvector.resize(5);
    std::cout << "myvector contains: size = " << stdvector.capacity() << std::endl;
    for (size_t i=0;i<myvector.size();i++)
        std::cout << ' ' << myvector[i];
    std::cout << std::endl;
    std::cout << "stdvector contains: size = " << stdvector.capacity() << std::endl;
    for (size_t i=0;i<stdvector.size();i++)
        std::cout << ' ' << stdvector[i];
    std::cout << std::endl;
    myvector.resize(8,100);
    stdvector.resize(8,100);

    std::cout << "myvector contains: size = " << stdvector.capacity() << std::endl;
    for (size_t i=0;i<myvector.size();i++)
        std::cout << ' ' << myvector[i];
    std::cout << std::endl;
    std::cout << "stdvector contains: size = " << stdvector.capacity() << std::endl;
    for (size_t i=0;i<stdvector.size();i++)
        std::cout << ' ' << stdvector[i];
    std::cout << std::endl;
    myvector.resize(12);
    stdvector.resize(12);
    std::cout << "myvector contains: size = " << stdvector.capacity() << std::endl;
    for (size_t i=0;i<myvector.size();i++)
        std::cout << ' ' << myvector[i];
    std::cout << std::endl;
    std::cout << "stdvector contains: size = " << stdvector.capacity() << std::endl;
    for (size_t i=0;i<stdvector.size();i++)
        std::cout << ' ' << stdvector[i];
    std::cout << std::endl;
}

static void	ft_insert(void)
{
    ft::vector<std::string> myvector (3,"100");
    ft::vector<std::string>::iterator it;
    std::vector<std::string> svector (3,"100");
    std::vector<std::string>::iterator sit;

    it = myvector.begin();
    it = myvector.insert ( it , "200" );
    sit = svector.begin();
    sit = svector.insert ( sit , "200" );

    myvector.insert (it,2,"300");
    svector.insert (sit,2,"300");

    // // "it" no longer valid, get a new one:
    // it = myvector.begin();

    // ft::vector<std::string> anothervector (2,400);
    // myvector.insert (it+2,anothervector.begin(),anothervector.end());

    // std::string myarray [] = { 501,502,503 };
    // myvector.insert (myvector.begin(), myarray, myarray+3);

    std::cout << "myvector contains: size = " << myvector.capacity() << std::endl;
    for (it=myvector.begin(); it<myvector.end(); it++)
        std::cout << ' ' << *it;
    std::cout << std::endl;
    std::cout << "stdvector contains: size = " << svector.capacity() << std::endl;
    for (sit=svector.begin(); sit<svector.end(); sit++)
        std::cout << ' ' << *sit;
    std::cout << std::endl;
}

int        main(void)
{
    ft_insert();
    return (0);
}