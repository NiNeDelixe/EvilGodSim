#include "enginecore/core/EnginePaths.h"

std::list<std::filesystem::path> EnginePaths::listDirectory(const std::string_view& folder_name)
{
    D_PTR(EnginePaths);
    std::list<std::filesystem::path> entries;
    for (size_t i = d->roots().size() - 1; i >= 0; i--)
    {
        auto& root = d->roots()[i];
        std::filesystem::path folder = root.path / folder_name;
        if (!std::filesystem::is_directory(folder)) 
            continue;
        std::filesystem::directory_iterator dir_iter(folder);
        for (const auto& entry : dir_iter)
        {
            entries.push_back(entry);
        }
    }
    return entries;
}

std::list<std::filesystem::path> EnginePaths::listResources()
{
    D_PTR(EnginePaths);
    std::list<std::filesystem::path> entries;

    std::filesystem::path resources = d->resources();

    std::filesystem::directory_iterator iter(resources);
    for (auto& entry : iter)
    {
        if (entry.is_regular_file())
        {
            entries.push_back(entry.path());
        }
        
        if (entry.is_directory())
        {

        }
    }

    return entries;
}
