#include <gtest/gtest.h>

#include "enginecore/core/CoreDefines.h"
#include "enginecore/interfaces/ISystem.h"

class TestSystem : public ISystem
{
public:
    TestSystem(const SystemCategory& cat) : ISystem(cat) {}
    ~TestSystem() = default;

    void update(EntityRegistry<DefaultEntityIndentifier>& registry) override {}

private:
    
};


TEST(SystemsContainer, AddTest)
{
    SystemsContainer test;

    test.add(std::make_shared<TestSystem>(SystemCategory::AI));
    test.add(std::make_shared<TestSystem>(SystemCategory::AI));

    test.add(std::make_shared<TestSystem>(SystemCategory::IO));
    test.add(std::make_shared<TestSystem>(SystemCategory::IO));
    
    test.add(std::make_shared<TestSystem>(SystemCategory::CAMERA_BEHAVIOR));
    test.add(std::make_shared<TestSystem>(SystemCategory::CAMERA_BEHAVIOR));


    SystemsContainer example;
    example.add(std::make_shared<TestSystem>(SystemCategory::AI));
    example.add(std::make_shared<TestSystem>(SystemCategory::IO));    
    example.add(std::make_shared<TestSystem>(SystemCategory::CAMERA_BEHAVIOR));

    EXPECT_EQ(test.getUncategorized().size(), example.getUncategorized().size());
    EXPECT_EQ(test.getCategorized().size(), example.getCategorized().size());
}