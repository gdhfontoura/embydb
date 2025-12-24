#include "storage/disk/disk_manager.h"
#include <sys/stat.h>
#include <fcntl.h>  
#include <unistd.h> 
#include <iostream> 
#include <stdexcept> 


namespace embydb {
    DiskManager::DiskManager(const std::string &db_file) : db_io_fd_ = open(path, flags, permissions);

}