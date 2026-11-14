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
double median(std::span<const double> vec);
void read_hw(std::string &name, double &midterm, 
            double &final, double hwAverage, 
            double finalGrade, std::vector<double>& hw, 
            std::ifstream& inputFile);

int main() {
    println("This program calculates one stu's grade.");
    std::string name;
    double midterm=0, final=0;

    println("stu's name, midterm score, final score and homework scores are read by file: grades.txt");
    std::ifstream inputFile("../../grades.txt");
    if (!inputFile){
        println(std::cerr, "grades.txt not found.");
        return 1;
    }
    std::vector<double> homeworkScores;

    read_hw(name, midterm, final, 0, 0, homeworkScores, inputFile);
    if(!inputFile);
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

//使用span重构中值函数,使用快速选择进行中值计算,时间复杂度为O(n)
//使用midpoint函数计算中值,避免溢出
double median(std::span<const double> vec) {
    auto size = std::ssize(vec);
    if (size == 0) {
        throw std::domain_error("median of an empty vector");
    }//在这抛出异常的意义是使其变成一个可移植的封装函数

    std::vector<double> temp(vec.begin(), vec.end());
    std::ranges::nth_element(temp.begin(), temp.begin() + size / 2, temp.end());
    auto mid = temp.begin() + (size / 2);

    if(size % 2 == 0) {
        auto max_it = std::ranges::max_element(temp.begin(), mid);
        return std::midpoint(*max_it, *mid);
    } else {
        return *mid;
    }
}

//使用文件流输入的读作业函数
void read_hw(std::string &name,double &midterm, double &final, double hwAverage, double finalGrade, std::vector<double>& hw, std::ifstream& inputFile) {
    if (!inputFile) {
        println(std::cerr, "No homework grades to read.");
        return;
    }

    inputFile >> name >> midterm >> final;
    for(double h; inputFile >> h;) {
        hw.push_back(h);
    }
    if(inputFile.eof()) {
        inputFile.clear();
        //因为这里是文件流输入,所以好像不需要清除标准输入流的错误状态
        // std::clearerr(stdin);
    }
    return;
}
