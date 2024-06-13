#include "JsonExplorerContext.h"

JsonExplorerContext &JsonExplorerContext::registry(const std::string &name, const std::string &containerIcon,
                                                   const std::string &leafIcon)
{
    if (mIconFamilies.find(name) != mIconFamilies.end())
    {
        std::cout
            << "Register icon family " << name
            << " failed: Duplicate name, please check the configuration file!"
            << std::endl;
    }
    else
        mIconFamilies[name] = std::make_pair(containerIcon, leafIcon);
    return *this;
}

JsonExplorerContext &JsonExplorerContext::registry(const std::string &name, CreateFunc createFunc)
{
    if (mStyleFactory.find(name) != mStyleFactory.end())
    {
        std::cout
            << "Register style factory " << name
            << " failed: Duplicate name!"
            << std::endl;
    }
    else
        mStyleFactory[name] = createFunc;
    return *this;
}

void JsonExplorerContext::setStrategy(const std::string &styleName, const std::string &iconFamilyName)
{
    if (mStyleFactory.find(styleName) == mStyleFactory.end())
    {
        std::cout << "Unregistered style: " << styleName << std::endl;
        mStrategy = nullptr;
    }
    // 根据风格名称获取对应的风格类
    auto styleFactory = mStyleFactory[styleName];

    // 如果指定的图标族存在则创建带有指定图标族的explorer，否则图标族为空字符串
    if (mIconFamilies.find(iconFamilyName) == mIconFamilies.end())
    {
        std::cout << "Unregistered icon family: " << iconFamilyName << std::endl;
        mStrategy = styleFactory({"", ""});
    }
    else
        mStrategy = styleFactory(mIconFamilies[iconFamilyName]);
}

void JsonExplorerContext::doRender(const std::string &jsonFilename)
{
    if (mStrategy == nullptr)
        throw std::logic_error("Please set render strategy first!!");
    mStrategy->render(jsonFilename);
}