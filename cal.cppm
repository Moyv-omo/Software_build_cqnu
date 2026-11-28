export module cg.cal;

import cg.data;
import std;
import cg.median;

using GradeList = std::vector<Grade>;

double calc(const Grade& student);

export double grade(GradeList& student) {
    try{
        for(auto& s : student){
            s.hwAverage = median(s.hw);
            s.finalGrade = calc(s);
        }
    } catch (std::domain_error& e) {
        println(std::cerr, "错误：{}", e.what());
        return 1;
    }
    return 0;
}

double calc(const Grade& student) {
    return 0.2 * student.midterm + 0.4 * student.final + 0.4 * student.hwAverage;
}