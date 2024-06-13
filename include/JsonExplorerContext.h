#pragma once

#include <unordered_map>
#include <memory>
#include "Utils/Utility.h"
#include "Style/AbstractStyleFactory.h"

// 实体类提供的创建对象的Create方法，体现为函数指针
typedef std::shared_ptr<AbstractStyleFactory> (*CreateFunc)(const std::pair<std::string, std::string> &);

/**
 * 策略模式：Context是策略模式中的上下文对象，添加了registry和setStrategy方法
 */
class JsonExplorerContext
{
public:
    // 构造析构函数
    JsonExplorerContext() = default;
    ~JsonExplorerContext() = default;

    /**
     * @description: 注册图标族
     * @param {string&} name 图标族名称
     * @param {string&} containerIcon 容器结点的图标
     * @param {string&} leafIcon 叶子节点的图标
     * @return {JsonExplorerContext&} 返回自身，支持链式调用
     */
    JsonExplorerContext &registry(const std::string &name, const std::string &containerIcon,
                                  const std::string &leafIcon);

    /**
     * @description: 注册风格
     * @param {string} &name 风格名称
     * @param {CreateFunc} createFunc 风格类提供的Create函数
     * @return {JsonExplorerContext&} 返回自身，支持链式调用
     */
    JsonExplorerContext &registry(const std::string &name, CreateFunc createFunc);

    /**
     * @description: 设置当前strategy，也就是哪种风格、哪种图标族的工厂
     * @param {string} &styleName
     * @param {string} &iconFamilyName
     * @return {*}
     */
    void setStrategy(const std::string &styleName, const std::string &iconFamilyName);

    void doRender(const std::string& jsonFilename);

private:
    // 保存名称到图标族的映射
    std::unordered_map<std::string, std::pair<std::string, std::string>>
        mIconFamilies;
    // 保存名称到风格工厂的Create方法的映射
    std::unordered_map<std::string, CreateFunc> mStyleFactory;
    // 当前策略
    std::shared_ptr<AbstractStyleFactory> mStrategy;
};