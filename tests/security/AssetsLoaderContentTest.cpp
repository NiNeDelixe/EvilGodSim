#include <gtest/gtest.h>

#include <filesystem>
#include <fstream>

#include "enginecore/core/assets/AssetsLoader.h"

TEST(AssetsLoaderContent, ThrowsWhenManifestMissing)
{
    AssetsLoader loader;

    EXPECT_THROW(loader.addResourcesFromContent("./missing_resources"), std::runtime_error);
}

TEST(AssetsLoaderContent, EnqueuesResourcesFromContentManifest)
{
    const auto test_root = std::filesystem::temp_directory_path() / "evilgodsim_assets_manifest_test";
    std::filesystem::remove_all(test_root);
    std::filesystem::create_directories(test_root / "shaders");
    std::filesystem::create_directories(test_root / "models");
    std::filesystem::create_directories(test_root / "lang");

    std::ofstream(test_root / "shaders" / "main.vert") << "void main() {}";
    std::ofstream(test_root / "shaders" / "main.frag") << "void main() {}";
    std::ofstream(test_root / "models" / "player.obj") << "# test model";
    std::ofstream(test_root / "lang" / "en_en.json") << "{}";

    std::ofstream manifest(test_root / "content.json");
    manifest << R"({
        "shaders": ["main"],
        "models": ["player"],
        "lang": ["en_en"]
    })";
    manifest.close();

    AssetsLoader loader;
    EXPECT_NO_THROW(loader.addResourcesFromContent(test_root));
    EXPECT_TRUE(loader.hasNext());

    std::filesystem::remove_all(test_root);
}