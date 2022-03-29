
#include <iostream>
#include <stdexcept>
#include <unordered_map>
#include "Direction.hpp"
#include "Notebook.hpp"
#include <string.h>
#include <vector>

using ariel::Direction;
using ariel::Notebook;
using namespace std;

Notebook::Notebook() {
}

void Notebook::write(int page, int row, int column, Direction dir, string const &word) {
    int len = word.length();
    if (page < 0 || row < 0 || column < 0 || column >= hundred) {
        throw invalid_argument("invalid value of location");
    }
    for (unsigned int l = 0; l < len; l++) {
        char a = word[l];
        if (a < low || a >= high) {
            throw invalid_argument("invalid input of word");
        }
    }

    if (this->notebook.find(page) == this->notebook.end()) {
        for (int i = 0; i < hundred; i++) {
            notebook[page][row][i] = '_';
        }
    }

    if (dir == Direction::Horizontal) {
        if (column + len >= hundred) {
            throw invalid_argument("reading go's out of bounds");
        }
        if (this->notebook[page].find(row) == this->notebook[page].end()) {
            for (int i = 0; i < hundred; i++) {
                notebook[page][row][i] = '_';
            }
        }
        for (int l = 0; l < len; l++) {
            if (notebook[page][row][(unsigned int) (column + l)] !='_') { //notebook[page][row][(unsigned int) (column + l)] != '\0' &&
                throw invalid_argument("you can't write twice in the same place");
            }
        }
    } else {
        for (int l = row; l < row + len; l++) {
            if (this->notebook[page].find(l) == this->notebook[page].end()) {
                for (int i = 0; i < hundred; i++) {
                    notebook[page][l][i] = '_';
                }
            }
            if (this->notebook[page][l][(unsigned int) column] !='_') { // notebook[page][l][(unsigned int) column] != '\0' &&
                throw invalid_argument("you can't write twice in the same place");
            }

        }
    }

    if (dir == Direction::Horizontal) {
        int cc = 0;
        for (int i = 0; i < len; i++) {
            this->notebook[page][row][(unsigned int) (column + cc)] = word[(unsigned int) i];
            cc++;
        }
    } else if (dir == Direction::Vertical) {
        int rc = 0;
        for (int i = 0; i < len; i++) {
            this->notebook[page][row + rc][(unsigned int) column] = word[(unsigned int) i];
            rc++;
        }
    }
}

string Notebook::read(int page, int row, int column, Direction dir, int count) {
    string str = string("");
    if (page < 0 || row < 0 || column < 0 || count < 0 || column >= hundred) {
        throw invalid_argument("invalid value of location");
    }
    if (this->notebook.find(page) == this->notebook.end()) {
        for (int i = 0; i < hundred; i++) {
            notebook[page][row][i] = '_';
        }
    }


    if (dir == Direction::Horizontal) {
        if (column + count > hundred) {
            throw invalid_argument("reading go's out of bounds");
        }
        if (this->notebook.at(page).find(row) == this->notebook.at(page).end()) {
            for (int i = 0; i < hundred; i++) {
                notebook[page][row][i] = '_';
            }
        }
        for (int i = 0; i < count; i++) {
            str = str.operator+=(this->notebook[page][row][(unsigned int) column++]);
        }
    } else if (dir == Direction::Vertical) {
        for (int l = row; l <row + count; l++) {
            if (this->notebook[page].find(l) == this->notebook[page].end()) {
                for (int i = 0; i < hundred; i++) {
                    notebook[page][l][i] = '_';
                }
            }
            str = str.operator+=(notebook[page][l][(unsigned int) column]);
        }
    } else {
        throw invalid_argument("Direction is invalid");
    }
    return str;
}

void Notebook::erase(int page, int row, int column, Direction dir, int count) {

    if (page < 0 || row < 0 || column < 0 || column >= hundred || count < 0) {
        throw invalid_argument("invalid value of location");
    }

    if (this->notebook.find(page) == this->notebook.end()) {
        for (int i = 0; i < hundred; i++) {
            notebook[page][row][i] = '_';
        }
    }

    if (dir == Direction::Horizontal) {
        if (column + count > hundred) {
            throw invalid_argument("you cant erase more then 100 chars");
        }
        if (this->notebook[page].find(row) == this->notebook[page].end()) {
            for (int i = 0; i < hundred; i++) {
                notebook[page][row][i] = '_';
            }
        }
        for (int i = 0; i < count; i++) {
            notebook[page][row][(unsigned int) column++] = '~';
        }
    } else if (dir == Direction::Vertical) {
        for (int l = row; l < row + count; l++) {
            if (this->notebook[page].find(l) == this->notebook[page].end()) {
                for (int i = 0; i < hundred; i++) {
                    this->notebook[page][l][i] = '_';
                }
            }
            notebook[page][l][(unsigned int) column] = '~';
        }
    } else {
        throw invalid_argument("Direction is invalid");
    }
}

void Notebook::show(int page) {
    if (page < 0) {
        throw invalid_argument("invalid value of location");
    }
    for (auto const &pair: notebook[page]) { // page,row
        for (unsigned int i = 0; i < hundred; i++) {
            if (pair.second[i] == '\0') {
                cout << "_";
            } else {
                cout << pair.second[i];
            }
        }
        cout << "\n";
    }

}