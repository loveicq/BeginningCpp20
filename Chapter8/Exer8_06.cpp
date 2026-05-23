/*************************第8章_练习_第6题************************
编写一个程序，请示用户输入多个成绩。成绩是0~100之间的一个整数（包括0和
100在内）。收集了所有成绩后，程序将输出以下数据：最高的5个成绩，最低的
5个成绩，平均成绩，中值成绩，以及成绩的标准差和方差。当然，需要为计算
每个统计数据分别编写函数。另外，代码只能输出5个值一次。为了进行练习，
使用数组来存储5个极值，而不使用vector对象。注意，作为一个预处理步骤，
应该首先对用户输入的成绩排序；之后，编写函数来计算统计数据就简单多了。
可以通过调整EX8_17.cpp中的快速排序算法来处理成绩数字。一定要合理地处
理用户输入的成绩少于5个（甚至没有输入成绩）的情况。怎么处理都可以，只
要保证程序不崩溃即可。中值是出现在排序列表中间位置的值。如果成绩的个数
是偶数，显然没有单独的一个中间值。此时，将中值定义为两个中间值的平均值。
计算n个成绩xᵢ的中值（μ）和标准差（σ）的公式如下所示：
μ=1/n∑_{i=0}^{n-1}xᵢ         σ=√(1/n∑_{i=0}^{n-1}(xᵢ-μ)²)
方差被定义为σ²。标准库的<cmath>模块中定义了用于计算平方根的
std::sqrt()函数。
*****************************************************************/
#include <iostream>
#include <cmath>
#include <vector>
#include <string>

void inputGrades(std::vector<int> &grades);
void sortGrades(std::vector<int> &grades);
void sortGrades(std::vector<int> &grades, int left, int right);
void getGradeValues(
    std::vector<int> &grades,
    int TOPscores[],
    int LOWscores[],
    const size_t size,
    double *gradeAverage,
    double *gradeMiddle,
    double *gradeVariance,
    double *gradeStdDev);

int main()
{
    std::vector<int> all_grades;
    // 输入成绩
    inputGrades(all_grades);
    if (all_grades.size() < 5)
        return 1; // 输入的成绩数据不满足要求

    // 成绩从小到大排序
    sortGrades(all_grades);

    // 输出全部成绩
    // for (auto a : all_grades)
    //     std::cout << a << std::endl;

    const size_t size{5};
    int top5grades[size]{};    // 最高的5个成绩
    int bottom5grades[size]{}; // 最低的5个成绩
    double gradeAverage{};     // 平均成绩
    double gradeMiddle{};      // 中值成绩
    double gradeVariance{};    // 成绩方差
    double gradeStdDev{};      // 成绩标准差

    // 计算题目要求的各项数据
    getGradeValues(
        all_grades,
        top5grades,
        bottom5grades,
        size,
        &gradeAverage,
        &gradeMiddle,
        &gradeVariance,
        &gradeStdDev);

    // 输出题目要求的各项数据
    std::cout << "\n前5名成绩为：\n";
    for (size_t i{}; i < size; ++i)
        std::cout << top5grades[i] << std::endl;

    std::cout << "后5名成绩为：\n";
    for (size_t i{}; i < size; ++i)
        std::cout << bottom5grades[i] << std::endl;

    std::cout << "平均成绩是：" << gradeAverage << std::endl;
    std::cout << "中值成绩是：" << gradeMiddle << std::endl;
    std::cout << "成绩方差是：" << gradeVariance << std::endl;
    std::cout << "成绩标准差是：" << gradeStdDev << std::endl;
}

void inputGrades(std::vector<int> &grades)
{
    int grade{};

    while (true)
    {
        std::cout << "请输入成绩(0~100)，输入‘#’结束：";
        if (std::cin >> grade)
        {
            if (grade >= 0 && grade <= 100)
                grades.push_back(grade);
            else
                std::cout << "无效成绩，请输入0~100之间的整数！" << std::endl;
        }
        else
        {
            char ch{};
            std::cin.clear(); // 清除错误的状态
            std::cin >> ch;
            if (ch == '#')
                break;
            else
                std::cout << "输入无效，请输入整数或‘#’结束！" << std::endl;
        }
    }
}

void sortGrades(std::vector<int> &grades)
{
    if (grades.empty())
    {
        std::cout << "你没输入成绩，程序即将退出！" << std::endl;
        return;
    }

    sortGrades(grades, 0, static_cast<int>(grades.size()) - 1);
}

void sortGrades(std::vector<int> &grades, int left, int right)
{
    // 递归终止条件
    if (left >= right)
        return;

    // 选择基准（中间位置的元素）
    int pivot{grades[(left + right) / 2]};

    // 分区
    int i{left}, j{right};
    while (i <= j)
    {
        // 从左找第一个 >= pivot的元素
        while (grades[i] < pivot)
            i++;
        // 从右找第一个 <= pivot的元素
        while (grades[j] > pivot)
            j--;

        if (i <= j)
        {
            // 交换数据
            int temp{grades[i]};
            grades[i] = grades[j];
            grades[j] = temp;
            // 继续移动指针
            i++;
            j--;
        }
    }

    // 递归排序左右两部分
    sortGrades(grades, left, j);  // 左半部分
    sortGrades(grades, i, right); // 右半部分
}

void getGradeValues(
    std::vector<int> &grades,
    int TOPscores[],
    int LOWscores[],
    const size_t size,
    double *gradeAverage,
    double *gradeMiddle,
    double *gradeVariance,
    double *gradeStdDev)
{
    int socoreNum{static_cast<int>(grades.size())};

    // 计算前、后五名成绩并填充数组
    for (size_t i{}; i < size; ++i)
    {
        LOWscores[i] = grades[i];
        TOPscores[i] = grades[socoreNum - size + i];
    }

    // 计算平均成绩
    int totalGrade{};
    for (auto a : grades)
        totalGrade += a;
    *gradeAverage = totalGrade / socoreNum;

    // 计算中值成绩
    if (!(socoreNum % 2))
        *gradeMiddle = grades[socoreNum / 2];
    else
        *gradeMiddle = (grades[socoreNum / 2 - 1] + grades[socoreNum / 2]) / 2;

    // 计算标准差
    double sumStdDev{};
    for (int a : grades)
        sumStdDev = (a - *gradeAverage) * (a - *gradeAverage);
    *gradeStdDev = std::sqrt(sumStdDev / socoreNum);

    // 计算方差
    *gradeVariance = *gradeStdDev * *gradeStdDev;
}