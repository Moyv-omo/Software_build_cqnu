/// This program caclulate one stu's grades.
// Created: Li Mingyang  2026-11-14 19:02:36

// SPDX-License-Identifier: AGPL-3.0-or-later
// SPDX-FileCopyrightText: 2026 FreeTech <3250348014@qq.com>

#include <iostream>
#include <stdexcept>
#include <span>
#include <print>
#include <vector>
#include <string>
import median;

using std::println;
struct Grade {
    std::string name;
    double midterm = 0;
    double final = 0;
    std::vector<double> hw;
    double hwAverage = 0;
    double finalGrade = 0;
};
using GradeList = std::vector<Grade>;
extern double cal(const Grade& student);
extern void print_grade(const Grade& student);
extern std::istream& operator>>(std::istream& inputFile, GradeList& student);
extern int read(std::string path, GradeList& student);

int main() {
    println("本程序用于计算多个学生的成绩");
    GradeList student;

    read("../grades.dat", student);
    
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