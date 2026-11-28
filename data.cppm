export module cg.data;

import std;

export struct Grade {
    std::string name;
    double midterm = 0;
    double final = 0;
    std::vector<double> hw;
    double hwAverage = 0;
    double finalGrade = 0;
};