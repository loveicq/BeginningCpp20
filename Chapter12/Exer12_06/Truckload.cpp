// Truckload.cpp
module truckload;

import <iostream>;

class Truckload::Package
{
public:
    SharedBox m_box;
    Package* m_next;

    Package(SharedBox box) : m_box{box}, m_next{nullptr} {}

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

Truckload::Iterator Truckload::getIterator() const
{
    return Iterator{m_head};
}

SharedBox Truckload::Iterator::getFirstBox()
{
    m_current = m_head;
    return m_current ? m_current->m_box : nullptr;
}

SharedBox Truckload::Iterator::getNextBox()
{
    if (!m_current)
        return getFirstBox();

    m_current = m_current->m_next;

    return m_current ? m_current->m_box : nullptr;
}

void Truckload::addBox(SharedBox box)
{
    auto package{new Package{box}};

    if (m_tail)
        m_tail->m_next = package;
    else
        m_head = package;

    m_tail = package;
}

bool Truckload::removeBox(SharedBox boxToRemove)
{
    Package* previous{nullptr};
    Package* current{m_head};
    while (current)
    {
        if (current->m_box == boxToRemove)
        {
            if (previous)
                previous->m_next = current->m_next;

            if (current == m_head)
                m_head = current->m_next;
            if (current == m_tail)
                m_tail = previous;

            current->m_next = nullptr;
            delete current;

            return true;
        }

        previous = current;
        current  = current->m_next;
    }

    return false;
}