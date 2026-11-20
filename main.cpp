/// This program caclulate one stu's grades.
// Created: Li Mingyang  2026-11-14 19:02:36

// SPDX-License-Identifier: AGPL-3.0-or-later
// SPDX-FileCopyrightText: 2026 FreeTech <3250348014@qq.com>

#include <iostream>
#include <vector>
#include <stdexcept>
#include <fstream>
#include <span>
#include <print>
#include <string>

using std::println;

extern double grade(double midterm, double final, double hwAverage);
extern double grade(double midterm, double final, const std::vector<double>& hw);
extern double median(std::span<const double> vec);
extern void read_hw(std::string &name, double &midterm, 
            double &final, double hwAverage, 
            double finalGrade, std::vector<double>& hw, 
            std::ifstream& inputFile);

int main() {
    println("This program calculates one stu's grade.");
    std::string name;
    double midterm=0, final=0;

    println("stu's name, midterm score, final score and homework scores are read by file: grades.txt");
    std::ifstream inputFile("../stuGrades/grades.txt");
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