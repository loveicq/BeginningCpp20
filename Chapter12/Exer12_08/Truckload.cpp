// Truckload.cpp
module truckload;

import <iostream>;

class Truckload::Package
{
public:
    SharedBox m_box;
    Package* m_next;
    Package* m_previous;

    Package(SharedBox box) : m_box{box}, m_next{}, m_previous{} {}
    ~Package() { delete m_next; }
};

Truckload::Truckload(SharedBox box)
{
    m_head = m_tail = new Package{box};
}

Truckload::Truckload(const std::vector<SharedBox>& boxes)
{
    for (const auto& box : boxes)
        addBox(box);
}

Truckload::Truckload(const Truckload& src)
{
    for (Package* package{src.m_head}; package; package = package->m_next)
        addBox(package->m_box);
}

Truckload::~Truckload()
{
    delete m_head;
}

void Truckload::listBoxes() const
{
    const size_t boxesPerLine{4};
    size_t count{};
    for (Package* package{m_head}; package; package = package->m_next)
    {
        std::cout << ' ';
        package->m_box->listBox();
        if (!(++count % boxesPerLine))
            std::cout << std::endl;
    }
    if (count % boxesPerLine)
        std::cout << std::endl;
}

void Truckload::listBoxesReversed() const
{
    const size_t boxesPerLine{4};
    size_t count{};
    for (Package* package{m_tail}; package; package = package->m_previous)
    {
        std::cout << ' ';
        package->m_box->listBox();
        if (!(++count % boxesPerLine))
            std::cout << std::endl;
    }
    if (count % boxesPerLine)
        std::cout << std::endl;
}

Truckload::Iterator Truckload::getIterator() const
{
    return Iterator{m_head, m_tail};
}

SharedBox Truckload::Iterator::getFirstBox()
{
    m_current = m_head;
    return getCurrentBox();
}

SharedBox Truckload::Iterator::getLastBox()
{
    m_current = m_tail;
    return getCurrentBox();
}

SharedBox Truckload::Iterator::getNextBox()
{
    if (!m_current)
        return getFirstBox();

    m_current = m_current->m_next;

    return getCurrentBox();
}

SharedBox Truckload::Iterator::getPreviousBox()
{
    if (!m_current)
        return getLastBox();

    m_current = m_current->m_previous;

    return getCurrentBox();
}

SharedBox Truckload::Iterator::getCurrentBox() const
{
    return m_current ? m_current->m_box : nullptr;
}

void Truckload::addBox(SharedBox box)
{
    auto package{new Package{box}};

    if (m_tail)
    {
        package->m_previous = m_tail;
        m_tail->m_next      = package;
    }
    else
        m_head = package;

    m_tail = package;
}

bool Truckload::removeBox(SharedBox boxToRemove)
{
    for (auto* current{m_head}; current != nullptr; current = current->m_next)
    {
        if (current->m_box == boxToRemove)
        {
            removePackage(current);
            return true;
        }
    }

    return false;
}

bool Truckload::removeBox(Iterator iter)
{
    if (iter.m_current)
    {
        removePackage(iter.m_current);
        return true;
    }
    else
        return false;
}

void Truckload::removePackage(Package* package)
{
    if (package->m_previous)
        package->m_previous->m_next = package->m_next;
    if (package->m_next)
        package->m_next->m_previous = package->m_previous;

    if (package == m_head)
        m_head = package->m_next;
    if (package == m_tail)
        m_tail = package->m_previous;

    package->m_next = nullptr;
    delete package;
}