#ifndef TABLE_HPP
#define TABLE_HPP

#include <map>
#include <string>
#include <fstream>

class Table {
    public:
    Table() = default;
    ~Table();

    void CreateTable();

    friend std::ostream& operator<<(std::ostream& os, const Table& table);

    private:
    std::map<unsigned int, void**> rows_;
    unsigned int num_rows_;
    unsigned int num_cols_;
};

std::ostream& operator<<(std::ostream& os, const Table& table);

#endif