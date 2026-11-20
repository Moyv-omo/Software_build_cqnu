/// This program caclulate one stu's grades.
// Created: fanzijun  2026-11-20 15:43:00

// SPDX-License-Identifier: AGPL-3.0-or-later
// SPDX-FileCopyrightText: 2026 FreeTech <fanzijun@hotmail.com>

#include <iostream>
#include <vector>
#include <fstream>
#include <print>
#include "main.h"

//使用文件流输入的读作业函数
void read_hw(Grade& student, std::ifstream& inputFile) {
    if (!inputFile) {
        println(std::cerr, "错误：无法打开输入文件。");
        return;
    }
    inputFile >> student.name >> student.midterm >> student.final;
    for(double h; inputFile >> h;) {
        student.hw.push_back(h);
    }
    if(inputFile.eof()) {
        inputFile.clear();
        //因为这里是文件流输入,所以好像不需要清除标准输入流的错误状态
        // std::clearerr(stdin);
    }
    return;
}