// Truckload.cppm
export module truckload;

import <memory>;
import <vector>;
import box;                  // 需要完整的 Box 定义

export using SharedBox = std::shared_ptr<Box>;   // 导出共享指针类型别名

class Package;              // 前置声明，隐藏内部链表节点的定义

export class Truckload      // 导出卡车装载类
{
public:
    Truckload() = default;                          // 默认构造函数 - 空卡车
    Truckload(SharedBox box);                       // 构造函数 - 添加单个箱子
    Truckload(const std::vector<SharedBox>& boxes); // 构造函数 - 从向量初始化
    Truckload(const Truckload& src);                // 拷贝构造函数

    ~Truckload(); // 析构函数，负责释放链表

    SharedBox getFirstBox();       // 获取第一个箱子，并重置遍历指针
    SharedBox getNextBox();        // 获取下一个箱子
    void addBox(SharedBox box);    // 向链表尾部添加箱子
    bool removeBox(SharedBox box); // 从链表移除指定箱子（成功返回 true）
    void listBoxes() const;        // 打印所有箱子

private:
    Package* m_head{};    // 链表头节点
    Package* m_tail{};    // 链表尾节点（用于快速追加）
    Package* m_current{}; // 遍历时指向当前节点
};