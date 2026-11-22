#include <print>
#include <vector>

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

void print_grade(const Grade& student) {
    println("{}, 期中成绩: {}, 期末成绩: {}, 作业中值: {}, 最终成绩: {:.2f}",
            student.name,
            student.midterm,
            student.final,
            student.hwAverage,
            student.finalGrade);
}