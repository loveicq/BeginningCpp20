// Truckload.cppm
export module truckload;

export import :shared_box;
import :package;
import <vector>;

export class Truckload
{
public:
    Truckload() = default;                          // 默认构造函数 - 空卡车装载
    Truckload(SharedBox box);                       // 构造函数 - 一个箱子
    Truckload(const std::vector<SharedBox> &boxes); // 构造函数 - 箱子向量
    Truckload(const Truckload &src);                // 拷贝构造函数

    ~Truckload(); // 析构函数

    SharedBox getFirstBox();       // 获取第一个箱子
    SharedBox getNextBox();        // 获取下一个箱子
    void addBox(SharedBox box);    // 添加一个新的 SharedBox
    void removeBox(SharedBox box); // 从卡车装载中移除一个箱子
    void listBoxes() const;        // 输出箱子

private:
    Package *m_head{};    // 列表中的第一个
    Package *m_tail{};    // 列表中的最后一个
    Package *m_current{}; // 最后从列表中获取的
};