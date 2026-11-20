/// This program caclulate one stu's grades.
// Created: Li Mingyang  2026-11-14 19:02:36

// SPDX-License-Identifier: AGPL-3.0-or-later
// SPDX-FileCopyrightText: 2026 FreeTech <3250348014@qq.com>

#include <iostream>
#include <numeric>
#include <stdexcept>
#include <fstream>
#include <span>
#include <print>
#include <vector>
#include <sstream>
#include <algorithm>

using std::println;

struct Grade{
    std::string name;
    double midterm=0;
    double final=0;
    std::vector<double> hw;
    double hwAverage=0;
    double finalGrade=0;
};

using GradeList = std::vector<Grade>;

extern double cal(Grade student);
extern double median(std::span<const double> vec);
extern void print_grade(Grade student);
extern std::ifstream& operator>>(std::ifstream& inputFile, GradeList& student);
extern std::istream& operator>>(std::istream& is, Grade& student);
extern double median(std::span<const double> vec);

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

void print_grade(Grade student) {
    println("{}, 期中成绩: {}, 期末成绩: {}, 作业中值: {}, 最终成绩: {:.2f}",
            student.name,
            student.midterm,
            student.final,
            student.hwAverage,
            student.finalGrade);
}

std::ifstream& operator>>(std::ifstream& inputFile, GradeList& student) {
    if (!inputFile) {
        throw std::runtime_error("无法打开输入文件");
    }
    std::string line;
    std::istringstream iss;
    while(std::getline(inputFile, line)) {
        iss.str(line);
        Grade s;
        if(iss>>s){
            student.push_back(s);
        } else {
            iss.clear();
        }
    }
    if(inputFile.eof()) {
        inputFile.clear();
        //因为这里是文件流输入,所以好像不需要清除标准输入流的错误状态
        // std::clearerr(stdin);
    }
    return inputFile;
}

std::istream& operator>>(std::istream& is, Grade& student) {
    if(is){
        is >> student.name >> student.midterm >> student.final;
    }
    if(!is.eof()&&is.fail()){
        throw std::runtime_error("输入错误于姓名、期中成绩或期末成绩");
    }
    if(is){
        for(double h; is >> h;){
            student.hw.push_back(h);
        }
        if(!is.eof()&&is.fail()){
            throw std::runtime_error("输入错误于作业成绩");
        }
        if(is.eof()&&!student.hw.empty()){
            is.clear();
        }
    }
    if(!is){
        std::println("错误：输入流错误");
    }
    return is;
}

double cal(Grade student) {
    return 0.2 * student.midterm + 0.4 * student.final + 0.4 * student.hwAverage;
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