/// This program caclulate one stu's grades.
// Created: fanzijun  2026-11-20 15:43:00

// SPDX-License-Identifier: AGPL-3.0-or-later
// SPDX-FileCopyrightText: 2026 FreeTech <fanzijun@hotmail.com>

#include <iostream>
#include <vector>
#include <fstream>
#include <print>
#include <sstream>

struct Grade {
    std::string name;
    double midterm = 0;
    double final = 0;
    std::vector<double> hw;
    double hwAverage = 0;
    double finalGrade = 0;
};
using GradeList = std::vector<Grade>;
std::istream& operator>>(std::istream& inputFile, GradeList& student);
extern std::istream& operator>>(std::istream& is, Grade& student);

int read(std::string path, GradeList& student) {
    std::println("学生姓名、期中成绩、期末成绩和作业成绩从文件: grades.dat 中读取");
    std::ifstream inputFile(path);
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
}

std::istream& operator>>(std::istream& inputFile, GradeList& student) {
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
        std::println("学生{}读取成功", student.name);
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