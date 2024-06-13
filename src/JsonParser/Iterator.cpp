#include "JsonParser/Iterator.h"

Iterator::~Iterator() {}

int Iterator::getLevel() { return -1; }

JsonComponentIterator::JsonComponentIterator(std::shared_ptr<Component> component) : mIdx(0)
{
    if (!std::dynamic_pointer_cast<Container>(component))
        throw std::logic_error("You need to use Container to initialize JsonComponentIter!!!");
    mCurContainer = std::dynamic_pointer_cast<Container>(component);
}

JsonComponentIterator::~JsonComponentIterator() {}

std::shared_ptr<Component> JsonComponentIterator::next()
{
    auto component = mCurContainer->getComponents()[mIdx];
    mIdx++;

    if (std::dynamic_pointer_cast<Container>(component))
    {
        auto container = std::dynamic_pointer_cast<Container>(component);
        // 如果当前容器仍有结点的时候才需要入栈，否则就不保存了，因为当前容器已经遍历完了
        if (mIdx < mCurContainer->getComponents().size())
            mStack.push(std::make_pair(mCurContainer, mIdx));
        mCurContainer = container;
        mIdx = 0;
        return container;
    }
    else
    {
        // 判断是否还有下一个结点
        if (mIdx >= mCurContainer->getComponents().size())
        {
            if (mStack.empty())
                mCurContainer = nullptr;
            else
            {
                mCurContainer = mStack.top().first;
                mIdx = mStack.top().second;
                mStack.pop();
            }
        }
        return component;
    }
}

bool JsonComponentIterator::hasMore()
{
    if (mCurContainer == nullptr || mIdx >= mCurContainer->getComponents().size())
        return false;
    return true;
}

int JsonComponentIterator::getLevel()
{
    return mStack.size();
}