#pragma once

#include <string>
#include <atomic>
#include "common/config.h"

namespace embydb {

class DiskManager {
public:
    explicit DiskManager(const std::string &db_file);
    ~DiskManager();

    DiskManager(const DiskManager &) = delete;
    DiskManager &operator=(const DiskManager &) = delete;

    void WritePage(page_id_t page_id, const char *page_data);
    void ReadPage(page_id_t page_id, char *page_data);

    int GetFileSize(const std::string &file_name);

private:
    std::string file_name_;
    
    int db_io_fd_; 
    
    std::atomic<page_id_t> next_page_id_;
};

}