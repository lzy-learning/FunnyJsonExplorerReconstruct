#include "JsonExplorerBuilder.h"

Builder::Builder()
{
    mJsonExplorerContext = std::make_shared<JsonExplorerContext>();
}
Builder::~Builder() {}

std::shared_ptr<JsonExplorerContext> Builder::getContext()
{
    return mJsonExplorerContext;
}

Director::Director() {}
Director::~Director() {}

void Director::makeDefaultJsonExplorerContext(std::shared_ptr<Builder> factoryBuilder)
{
    // 注册图标族
    factoryBuilder->registerIconFamily();
    // 注册具体风格
    factoryBuilder->registerStyle();
}

DefaultBuilder::DefaultBuilder() {}
DefaultBuilder::~DefaultBuilder() {}

void DefaultBuilder::registerIconFamily()
{
    std::string iconFamilyFilename = "icon-family.ini";
    auto iconFamilies = readIconFamily(iconFamilyFilename);
    for (auto it = iconFamilies.begin(); it != iconFamilies.end(); it++)
        mJsonExplorerContext->registry(it->first, it->second.first, it->second.second);
}

void DefaultBuilder::registerStyle()
{
    (*mJsonExplorerContext).registry("tree", TreeStyleFactory::Create).registry("rect", RectangleStyleFactory::Create);
}