#include "JsonParser/Iterator.h"

Iterator::~Iterator() {}

int Iterator::getLevel() { return -1; }

JsonComponentIterator::JsonComponentIterator(std::shared_ptr<Component> component)
{
    if (!std::dynamic_pointer_cast<Container>(component))
        throw std::logic_error("You need to use Container to initialize JsonComponentIter!!!");
    auto container = std::dynamic_pointer_cast<Container>(component);
    mStack.push(std::make_pair(container, 0));
}

JsonComponentIterator::~JsonComponentIterator() {}

std::shared_ptr<Component> JsonComponentIterator::next()
{
    auto container = mStack.top().first;
    auto idx = mStack.top().second;

    auto component = container->getComponents()[idx];
    // 指针后移
    mStack.top().second += 1;

    // 遇到新的Container则入栈
    if (std::dynamic_pointer_cast<Container>(component))
    {
        auto container = std::dynamic_pointer_cast<Container>(component);
        mStack.push(std::make_pair(container, 0));
    }
    return component;
}

bool JsonComponentIterator::hasMore()
{
    // 把弹栈逻辑放在hasMore中
    while (!mStack.empty())
    {
        if (mStack.top().second >= mStack.top().first->getSize())
            mStack.pop();
        else
            return true;
    }
    return false;
}

int JsonComponentIterator::getLevel()
{
    return mStack.size() - 1;
}