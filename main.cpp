/// This program caclulate one stu's grades.
// Created: Li Mingyang  2026-11-14 19:02:36

// SPDX-License-Identifier: AGPL-3.0-or-later
// SPDX-FileCopyrightText: 2026 FreeTech <3250348014@qq.com>

#include <iostream>
#include <stdexcept>
#include <fstream>
#include <span>
#include <print>
#include "main.h"

using std::println;

extern double cal(Grade student);
extern double median(std::span<const double> vec);
extern void print_grade(Grade student);
extern std::ifstream& operator>>(std::ifstream& inputFile, GradeList& student);

int main() {
    println("本程序用于计算多个学生的成绩");
    GradeList student;

    println("学生姓名、期中成绩、期末成绩和作业成绩从文件: grades.dat 中读取");
    std::ifstream inputFile("../stuGrades/grades.dat");
    if (!inputFile){
        println(std::cerr, "错误：无法找到文件 grades.dat。");
        return 1;
    }
    try{
        inputFile >> student;
    }
    catch (std::runtime_error& e) {
        println(std::cerr, "错误：{}", e.what());
        return 1;
    }
    
    println();

    try{
        //在println外部计算中值和最终成绩能够避免副作用1.求值顺序确定 2.避免脏输出
        for(auto& s : student){
            s.hwAverage = median(s.hw);
            s.finalGrade = cal(s);
            print_grade(s);
        }
    } catch (std::domain_error& e) {
        println(std::cerr, "错误：{}", e.what());
        return 1;
    }

    return 0;
}