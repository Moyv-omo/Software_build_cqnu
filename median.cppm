export module median;
import std;

//使用span重构中值函数,使用快速选择进行中值计算,时间复杂度为O(n)
//使用midpoint函数计算中值,避免溢出
export double median(std::span<const double> vec) {
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
