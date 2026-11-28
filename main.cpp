/// This program caclulate one stu's grades.
// Created: Li Mingyang  2026-11-14 19:02:36

// SPDX-License-Identifier: AGPL-3.0-or-later
// SPDX-FileCopyrightText: 2026 FreeTech <3250348014@qq.com>

import std;

import cg.data;
import cg.input;
import cg.cal;
import cg.print;



using std::println;
using GradeList = std::vector<Grade>;
import cg.print;
extern std::istream& operator>>(std::istream& inputFile, GradeList& student);

int main() {
    println("本程序用于计算多个学生的成绩");
    GradeList student;

    read("../grades.dat", student);
    
    println();

    grade(student);

    print_grade(student);

    return 0;
}