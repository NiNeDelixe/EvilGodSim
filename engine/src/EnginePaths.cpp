#include "enginecore/core/EnginePaths.h"

std::list<std::filesystem::path> EnginePaths::listDirectory(const std::string_view& folder_name)
{
    std::list<std::filesystem::path> entries;
    for (size_t i = d_ptr->roots().size() - 1; i >= 0; i--)
    {
        auto& root = d_ptr->roots()[i];
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
    std::list<std::filesystem::path> entries;

    std::filesystem::path resources = d_ptr->resources();

    if (!std::filesystem::exists(resources))
    {
        return {};
    }

    std::queue<std::filesystem::path> directories;
    directories.emplace(resources);

    while (!directories.empty())
    {
        std::filesystem::path current_dir = directories.front();
        directories.pop();

        try
        {
            std::filesystem::directory_iterator iter(current_dir);
            for (auto& entry : iter)
            {
                if (entry.is_regular_file())
                {
                    entries.emplace_back(entry.path());
                }
                else if (entry.is_directory())
                {
                    directories.emplace(entry.path());
                }
            }
        }
        catch (const std::filesystem::filesystem_error& ex)
        {
            continue;
        }
    }

    return entries;
}
