#include <print>
#include "main.h"

using std::println;

void print_grade(Grade student) {
    println("{}, 期中成绩: {}, 期末成绩: {}, 作业中值: {}, 最终成绩: {:.2f}",
            student.name,
            student.midterm,
            student.final,
            student.hwAverage,
            student.finalGrade);
}