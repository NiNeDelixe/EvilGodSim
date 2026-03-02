#include <gtest/gtest.h>

#include <filesystem>
#include <fstream>

#include "enginecore/core/lang/Localization.h"

TEST(Translation, ReturnsCurrentLanguageWhenKeyExists)
{
    const auto root = std::filesystem::temp_directory_path() / "evilgodsim_translation_test";
    std::filesystem::remove_all(root);
    std::filesystem::create_directories(root / "lang");

    std::ofstream(root / "lang" / "en_en.json") << R"({"menu":{"play":"Play"}})";
    std::ofstream(root / "lang" / "ru_ru.json") << R"({"menu":{"play":"Играть"}})";

    Localization::init(root, "ru_ru");

    EXPECT_EQ(Localization::tr("menu.play"), "Играть");

    std::filesystem::remove_all(root);
}

TEST(Translation, FallsBackToEnglishWhenMissingInCurrentLanguage)
{
    const auto root = std::filesystem::temp_directory_path() / "evilgodsim_translation_fallback_test";
    std::filesystem::remove_all(root);
    std::filesystem::create_directories(root / "lang");

    std::ofstream(root / "lang" / "en_en.json") << R"({"menu":{"play":"Play","quit":"Quit"}})";
    std::ofstream(root / "lang" / "ru_ru.json") << R"({"menu":{"play":"Играть"}})";

    Localization::init(root, "ru_ru");

    EXPECT_EQ(Localization::tr("menu.quit"), "Quit");

    std::filesystem::remove_all(root);
}