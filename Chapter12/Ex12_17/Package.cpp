module truckload:package;

import :shared_box;

class Package
{
public:
    Package(SharedBox box) : m_box{ box }, m_next{ nullptr } {}//构造函数
    ~Package() { delete m_next; } //析构函数
    // 获取Box指针
    SharedBox getBox() const { return m_box; }

    //获取或更新指向下一个Package的指针
    Package* getNext() { return m_next; }
    void setNext(Package* package) { m_next = package; }

private:
    SharedBox m_box;    // 指向此Package中包含的Box对象的指针
    Package* m_next;    // 指向列表中下一个Package的指针
};