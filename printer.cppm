export module cg.print;

import std;
import cg.data;

using GradeList = std::vector<Grade>;
using std::println;
void print_one_grade(const Grade& student);

export void print_grade(const GradeList& student) {
    for (const auto& s : student) {
        print_one_grade(s);
    }
}

void print_one_grade(const Grade& student) {
    println("{}, 期中成绩: {}, 期末成绩: {}, 作业中值: {}, 最终成绩: {:.2f}",
            student.name,
            student.midterm,
            student.final,
            student.hwAverage,
            student.finalGrade);
}