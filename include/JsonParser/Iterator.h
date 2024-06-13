#pragma once

#include "Component.h"
#include <stack>

/**
 * 迭代器模式：迭代器抽象类，提供next方法和hasMore方法
 * 同时为了适配本任务，还新增了getLevel方法标明当前结点所属的层级，提供默认实现
 */
class Iterator
{
public:
    virtual ~Iterator();
    virtual std::shared_ptr<Component> next() = 0;
    virtual bool hasMore() = 0;
    virtual int getLevel();
};

/**
 * 特定实现的Iterator：实现hasMore和next方法，如果需要还可以实现getLevel方法
 */
class JsonComponentIterator : public Iterator
{
private:
    // 为了保存层级信息，需要用stack模拟递归栈，保存Container和对应的idx
    std::stack<std::pair<std::shared_ptr<Container>, int>> mStack;
    // 迭代器所处的当前结点
    std::shared_ptr<Container> mCurContainer;
    // 如果当前结点是Container结点，那么mIdx保存了当前结点的位置
    int mIdx;

public:
    /**
     * @description: 根据Json文件的特点，文件必从Container开始
     * @param {shared_ptr<Component>} component
     * @return {*}
     */
    JsonComponentIterator(std::shared_ptr<Component> component);

    /**
     * @description: 虚析构，仅让代码看起来规范一点
     * @return {*}
     */
    virtual ~JsonComponentIterator();

    /**
     * @description: 根据Json树状的结构编写特定的next
     * @return {*}
     */
    virtual std::shared_ptr<Component> next();

    /**
     * @description: 判断是否还有下一个结点
     * @return {*}
     */
    virtual bool hasMore();

    /**
     * @description: 获取当前层级，递归栈的深度就是level
     * @return {*}
     */
    virtual int getLevel();
};