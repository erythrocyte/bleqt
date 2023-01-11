#include "workDir.hpp"

#include <errno.h>
#include <experimental/filesystem>
#include <limits.h> /* PATH_MAX */
#include <sstream>
#include <string.h>
#include <sys/stat.h> /* mkdir(2) */

#include "workString.hpp"

namespace efs = std::experimental::filesystem;

namespace ble::src::common::services::work_dir {

void make_dir_my(const std::string& full_path)
{
    efs::create_directories(efs::path(full_path));
}

std::string combine_dir_my(const std::string& dir1, const std::string& val)
{
    efs::path root_dir(dir1);
    efs::path val_dir(val);
    efs::path result = root_dir / val_dir;
    return result.string();
}

void remove_dir_my(const std::string& full_path)
{
    efs::remove_all(efs::path(full_path));
}

std::string get_file_dir(const std::string& file_full_path)
{
    return efs::path(file_full_path).parent_path().string();
}

}