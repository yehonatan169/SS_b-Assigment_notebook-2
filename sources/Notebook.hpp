#ifndef NOTEBOOK_H
#define NOTEBOOK_H
#include <iostream>
#include <stdexcept>
using namespace std;
#include <map>
#include <unordered_map>
#include "Direction.hpp"
int const hundred = 100;
int const low = 32;
int const high = 126;
namespace ariel{

    class Notebook{
        unordered_map<int,unordered_map<int,char[100]>> notebook;

    public:
        Notebook();
        void write( int page,  int row,  int column, Direction dir, string const &word);
        string read( int page,  int row,  int column, Direction dir, int count);
        void erase( int page,  int row,  int column, Direction dir, int count);
        void show( int page);

    };
}
#endif