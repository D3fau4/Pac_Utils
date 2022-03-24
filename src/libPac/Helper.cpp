//
// Created by raul2 on 23/03/2022.
//

#include <filesystem>
#include <fstream>
#include "pac.h"
#include "systemfilesource.h"
#include "defines.h"

namespace fs = std::filesystem;

static fs::path
path_make_relative(const fs::path& from, const fs::path& to)
{
    auto from_iter = from.begin();
    auto to_iter = to.begin();

    while (from_iter != from.end() && to_iter != to.end() && (*to_iter) == (*from_iter))
    {
        ++to_iter;
        ++from_iter;
    }

    fs::path final_path;
    while (from_iter != from.end())
    {
        final_path /= "..";
        ++from_iter;
    }

    while (to_iter != to.end())
    {
        final_path /= *to_iter;
        ++to_iter;
    }

    return final_path;
}

EXPORTS void testlib(const char* s) {

    const fs::path& path = s;
    std::ofstream outfile ("test.txt");

    outfile << path.string() << std::endl;

    outfile.close();
}

EXPORTS void
patch_archive(const char* s)
{
    const fs::path& path = s;
    fs::path root = path.parent_path();
    fs::path base = path.stem();

    fs::path source = path;
    source.replace_extension();

    fs::path target = path;
    target.replace_extension(".pac");

    fs::path bak_file = target;
    bak_file.replace_extension(".pac.bak");

    if (!is_regular_file(target) && !is_regular_file(bak_file))
    {
        return;
    }

    if (!is_regular_file(bak_file))
    {
        fs::rename(target, bak_file);
    }


    lib_pac::pac_archive archive(bak_file.string());

    fs::recursive_directory_iterator iter(path);

    int n_repl = 0;
    for (auto& it : iter)
    {
        if (fs::is_regular_file(it))
        {
            fs::path virt_path = path_make_relative(path, it);
            if (archive.get(virt_path.string()) != nullptr)
            {
                n_repl++;
                auto ptr = std::make_unique<lib_pac::system_file_source>(it.path().string());
                archive.insert(virt_path.string(), std::move(ptr));
            }
            else
            {

            }
        }
    }

    const auto save_info = archive.save(target.string(), nullptr);

    const float ratio = (save_info.compressed_size + save_info.header_size) * 100.f / (save_info.original_size);
}
