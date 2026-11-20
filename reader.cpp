/// This program caclulate one stu's grades.
// Created: fanzijun  2026-11-20 15:43:00

// SPDX-License-Identifier: AGPL-3.0-or-later
// SPDX-FileCopyrightText: 2026 FreeTech <fanzijun@hotmail.com>

#include <iostream>
#include <vector>
#include <fstream>
#include <print>
#include <string>

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