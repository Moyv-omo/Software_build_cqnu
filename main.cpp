/// This program caclulate one stu's grades.
// Created: Li Mingyang  2026-11-14 19:02:36

// SPDX-License-Identifier: AGPL-3.0-or-later
// SPDX-FileCopyrightText: 2026 FreeTech <3250348014@qq.com>

#include <iostream>
#include <vector>
#include <algorithm>
#include <stdexcept>
#include <numeric>
#include <ranges>
#include <fstream>
#include <span>
#include <print>
#include <string>
//#include <cstdio>

using std::cin;
using std::println;

double grade(double midterm, double final, double hwAverage);
double grade(double midterm, double final, const std::vector<double>& hw);
double median(std::vector<double> vec);
std::istream& read_hw(std::istream &is, std::vector<double>& hw);

int main() {
    println("This program calculates one stu's grade.");
    std::string name;
    double midterm=0, final=0;
    println("Please enter name, midterm score, and final score: ");
    cin >> name >> midterm >> final;

    println("Please enter stu's grades ,end by eof.");
    std::ifstream inputFile("../../grades.txt");
    if (!inputFile){
        println(std::cerr, "grades.txt not found.");
        return 1;
    }
    std::vector<double> homeworkScores;

    read_hw(cin, homeworkScores);
    if(!inputFile) {
        println("No homework scores read from file.");
    }//这个判空因为后面的read_hw1已经由异常处理了，好像没用
    println();

    try{
        //在println外部计算中值和最终成绩能够避免副作用1.求值顺序确定 2.避免脏输出
        double hwAverage = median(homeworkScores);
        double finalGrade = grade(midterm, final, hwAverage);
        println("{}, midterm: {}, final: {}, homework average: {}, final grade: {:.2f}",
                name,
                midterm,
                final,
                hwAverage,
                finalGrade);
    } catch (std::domain_error& e) {
        println(std::cerr, "Error calculating grade: {}", e.what());
        return 1;
    }

    return 0;
}

//grade函数重载
double grade(double midterm, double final, double hwAverage) {
    return 0.2 * midterm + 0.4 * final + 0.4 * hwAverage;
}

double grade(double midterm, double final, const std::vector<double>& hw) {
    if (std::ssize(hw) == 0) {
        throw std::domain_error("no homework grades");
    }
    return grade(midterm, final, median(hw));
}

double median(std::vector<double> vec) {
   auto size = std::ssize(vec);
    if (size == 0) {
        throw std::domain_error("median of an empty vector");
    }

    //使用排序进行中值计算,时间复杂度为O(nlogn)
    std::ranges::sort(vec);
    auto mid(size / 2);
    if(size % 2 == 0) {
        return std::midpoint(vec[mid - 1], vec[mid]);
    } else {
        return vec[mid];
    }
}

std::istream& read_hw(std::istream& is, std::vector<double>& hw) {
    if (!is) {
        print(std::cerr, "No homework grades to read.\n");
        return is;
    }
    for(double h ; cin >> h;) {
        hw.push_back(h);
    }
    if(cin.eof()) {
        cin.clear();
        std::clearerr(stdin);
    }
    return is;
}

