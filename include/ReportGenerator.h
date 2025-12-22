#pragma once
#include <vector>
#include <iostream>

template <typename T>
class ReportGenerator
{
public:
    static void generate(const std::vector<T> &items,
                         const std::string &title)
    {
        std::cout << "==== " << title << " ====\n";
        for (const auto &i : items)
        {
            std::cout << i << "\n";
        }
    }
};
