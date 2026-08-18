// Truckload.cppm
export module truckload;

import box;
import <memory>;
import <vector>;

export using SharedBox = std::shared_ptr<Box>;

export class Truckload
{
public:
    Truckload() = default;
    Truckload(SharedBox box);
    Truckload(const std::vector<SharedBox>& boxes);
    Truckload(const Truckload& src);

    ~Truckload();

    class Iterator;

    Iterator getIterator() const;

    void addBox(SharedBox box);
    void removeBox(SharedBox box);
    void removeBox(Iterator iter);

    void listBoxes() const;
    void listBoxesReversed() const;

private:
    class Package;

    void removePackage(Package* package);

    Package* m_head{};
    Package* m_tail{};
};

class Truckload::Iterator
{
public:
    SharedBox getFirstBox();
    SharedBox getLastBox();
    SharedBox getNextBox();
    SharedBox getPreviousBox();
    SharedBox getCurrentBox() const;

private:
    Package* m_head;
    Package* m_tail;
    Package* m_current;

    friend class Truckload;
    explicit Tterator(Package* head, Package* tail)
        : m_head{head}, m_tail{tail}, m_current{nullptr} {}
};