#include "storage/disk/disk_manager.h"
#include <sys/stat.h>
#include <fcntl.h>  
#include <unistd.h> 
#include <iostream> 
#include <stdexcept> 


namespace embydb {
    DiskManager::DiskManager(const std::string &db_file) : db_io_fd_ (-1), file_name_(db_file), next_page_id_(0) {
        db_io_fd_ = open(db_file.c_str(), O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
        if (db_io_fd_ < 0) {
            throw std::runtime_error("Failed to open or create database file: " + db_file);
        }

        off_t file_size = lseek(db_io_fd_, 0, SEEK_END);
        next_page_id_ = static_cast<page_id_t>(file_size / PAGE_SIZE);
    }

    DiskManager::~DiskManager() {
        if (db_io_fd_ >= 0) {
            close(db_io_fd_);
        }
    }

    void DiskManager::WritePage(page_id_t page_id, const char *page_data) {
        off_t offset = static_cast<off_t>(page_id) * PAGE_SIZE;
        if (lseek(db_io_fd_, offset, SEEK_SET) == static_cast<off_t>(-1)) {
            throw std::runtime_error("Failed to seek to position for writing page: " + std::to_string(page_id));
        }

        ssize_t bytes_written = write(db_io_fd_, page_data, PAGE_SIZE);
        if (bytes_written != PAGE_SIZE) {
            throw std::runtime_error("Failed to write full page data for page: " + std::to_string(page_id));
        }
    }

    void DiskManager::ReadPage(page_id_t page_id, char *page_data) {
        off_t offset = static_cast<off_t>(page_id) * PAGE_SIZE;
        if (lseek(db_io_fd_, offset, SEEK_SET) == static_cast<off_t>(-1)) {
            throw std::runtime_error("Failed to seek to position for reading page: " + std::to_string(page_id));
        }

        ssize_t bytes_read = read(db_io_fd_, page_data, PAGE_SIZE);
        if (bytes_read != PAGE_SIZE) {
            throw std::runtime_error("Failed to read full page data for page: " + std::to_string(page_id));
        }
    }

    int DiskManager::GetFileSize(const std::string &file_name) {
        struct stat file_stat;
        if (stat(file_name.c_str(), &file_stat) != 0) {
            throw std::runtime_error("Failed to get file size for: " + file_name);
        }
        return static_cast<int>(file_stat.st_size);
    }
}