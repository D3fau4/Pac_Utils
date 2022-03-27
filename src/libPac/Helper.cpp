//
// Created by raul2 on 23/03/2022.
//

#include "Helper.h"

namespace fs = std::experimental::filesystem;

static fs::path
path_make_relative(const fs::path &from, const fs::path &to)
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

EXPORTS void testlib(const char *s)
{
    const fs::path &path = s;
    std::ofstream outfile("test.txt");

    outfile << path.string() << std::endl;

    outfile.close();
}

EXPORTS void testpath(const char *s){
    const fs::path &path = s;
    std::ofstream outfile("test.txt");
    std::string str = path.string();
    std::replace(str.begin(), str.end(), '\\', '/');
    outfile << path.string() + "\n" + path.parent_path().make_preferred().string() + "\n" + 
    str << std::endl;

    outfile.close();
}

EXPORTS void
patch_archive(const char *pac, const char* folder)
{
    const fs::path& path = folder;
    fs::path root = path.parent_path();
    fs::path base = path.stem();

    fs::path source = path;
    source.replace_extension();

    fs::path target = pac;
    target.replace_extension(".pac");

    fs::path bak_file = target;
    bak_file.replace_extension(".pac.bak");

    if (!is_regular_file(target) && !is_regular_file(bak_file))
    {
        //std::cout << "Unable to find PAC file or Backup: " << base;
        return;
    }

    if (!is_regular_file(bak_file))
    {
        fs::rename(target, bak_file);
    }

    lib_pac::pac_archive archive(bak_file);
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
                auto ptr = std::make_unique<lib_pac::system_file_source>(it.path());
                archive.insert(virt_path.string(), std::move(ptr));
            }
        }
    }

    const auto save_info = archive.save(target, NULL);

    const float ratio = (save_info.compressed_size + save_info.header_size) * 100.f / (save_info.original_size);
}

EXPORTS void
extract_archive(const char *pac, const char *folder)
{
    fs::path path = pac;
    if (folder == NULL)
    {
        fs::path temp = path;
        temp.replace_extension();
        folder = temp.filename().string().c_str();
    }
    fs::path outputfolder = folder;
    memory_buffer comp_buffer;
    memory_buffer dec_buffer;

    std::wcout << L"Extracting Archive: " << path.filename() << std::endl;
    lib_pac::pac_archive archive(path);


    const int n_files = archive.num_files();
    const int f_digits = ceil(log10(n_files));

    int cur_file = 0;

    for (auto& elem : archive)
    {
        const fs::path v_path = elem;
        auto file_source = archive.get(elem);

        size_t dec_sz;

        if (file_source->compressed())
        {
            comp_buffer.reserve(file_source->data_size());

            file_source->copy_data(comp_buffer.data(), 0, file_source->data_size());

            const auto dec_info = lib_pac::compressor::prepare_decompression(comp_buffer.data(), file_source->data_size());

            dec_sz = dec_info->output_size();
            const uint32_t expected_size = file_source->unpacked_size();

            if (dec_sz != expected_size)
            {
                std::cerr << "Size Mismatch: " << v_path;
                std::cerr << " - Expected " << expected_size << " got " << dec_sz << std::endl;
            }

            dec_buffer.reserve(dec_sz);

            lib_pac::compressor::decompress(*dec_info, dec_buffer.data());
        }
        else
        {
            dec_sz = file_source->unpacked_size();
            dec_buffer.reserve(dec_sz);

            file_source->copy_data(dec_buffer.data(), 0, dec_sz);
        }
        fs::create_directories(v_path.parent_path());

#if 0
        HANDLE hFile = CreateFileA(v_path.string().c_str(), GENERIC_WRITE, 0, nullptr, CREATE_NEW,
            FILE_ATTRIBUTE_NORMAL | FILE_FLAG_SEQUENTIAL_SCAN | FILE_FLAG_WRITE_THROUGH,
            nullptr);

        WriteFile(hFile, dec_buffer.data(), dec_sz, nullptr, nullptr);
        CloseHandle(hFile);
#endif
#if 0
        std::ofstream output(v_path, std::ios::trunc | std::ios::binary);
        output.write(dec_buffer.data(), dec_sz);
        output.flush();
        output.close();
#endif
#if 1
        FILE* f;
        std::string tmp = v_path.string();
        std::replace(tmp.begin(), tmp.end(), '\\', '/');
        fs::path fixedpath = folder;
        fixedpath /= tmp;
        if (!fs::exists(fixedpath.parent_path()))
            fs::create_directories(fixedpath.parent_path());
        fopen_s(&f, fixedpath.string().c_str(), "wb");
        fwrite(dec_buffer.data(), 1, dec_sz, f);
        fflush(f);
        fclose(f);
#endif

        cur_file++;
    }
}

EXPORTS void
extract_archive_withlist(const char* pac, char** ListFiles, int numoffiles, const char* folder)
{
    fs::path path = pac;
    if (folder == NULL)
    {
        fs::path temp = path;
        temp.replace_extension();
        folder = temp.filename().string().c_str();
    }
    fs::path outputfolder = folder;
    memory_buffer comp_buffer;
    memory_buffer dec_buffer;

    std::wcout << L"Extracting Archive: " << path.filename() << std::endl;
    lib_pac::pac_archive archive(path);


    const int n_files = archive.num_files();
    const int f_digits = ceil(log10(n_files));

    int cur_file = 0;

    for (auto& elem : archive)
    {
        const fs::path v_path = elem;

        bool found = false;
        for (int i = 0; i < numoffiles; i++) {
            if (v_path.string().compare(ListFiles[i]) == 0) {
                found = true;
                break;
            }
        }
        if (!found)
            continue;

        auto file_source = archive.get(elem);

        size_t dec_sz;

        if (file_source->compressed())
        {
            comp_buffer.reserve(file_source->data_size());

            file_source->copy_data(comp_buffer.data(), 0, file_source->data_size());

            const auto dec_info = lib_pac::compressor::prepare_decompression(comp_buffer.data(), file_source->data_size());

            dec_sz = dec_info->output_size();
            const uint32_t expected_size = file_source->unpacked_size();

            if (dec_sz != expected_size)
            {
                std::cerr << "Size Mismatch: " << v_path;
                std::cerr << " - Expected " << expected_size << " got " << dec_sz << std::endl;
            }

            dec_buffer.reserve(dec_sz);

            lib_pac::compressor::decompress(*dec_info, dec_buffer.data());
        }
        else
        {
            dec_sz = file_source->unpacked_size();
            dec_buffer.reserve(dec_sz);

            file_source->copy_data(dec_buffer.data(), 0, dec_sz);
        }
        fs::create_directories(v_path.parent_path());

#if 0
        HANDLE hFile = CreateFileA(v_path.string().c_str(), GENERIC_WRITE, 0, nullptr, CREATE_NEW,
            FILE_ATTRIBUTE_NORMAL | FILE_FLAG_SEQUENTIAL_SCAN | FILE_FLAG_WRITE_THROUGH,
            nullptr);

        WriteFile(hFile, dec_buffer.data(), dec_sz, nullptr, nullptr);
        CloseHandle(hFile);
#endif
#if 0
        std::ofstream output(v_path, std::ios::trunc | std::ios::binary);
        output.write(dec_buffer.data(), dec_sz);
        output.flush();
        output.close();
#endif
#if 1
        FILE* f;
        std::string tmp = v_path.string();
        std::replace(tmp.begin(), tmp.end(), '\\', '/');
        fs::path fixedpath = folder;
        fixedpath /= tmp;
        if (!fs::exists(fixedpath.parent_path()))
            fs::create_directories(fixedpath.parent_path());
        fopen_s(&f, fixedpath.string().c_str(), "wb");
        fwrite(dec_buffer.data(), 1, dec_sz, f);
        fflush(f);
        fclose(f);
#endif

        cur_file++;
    }
}