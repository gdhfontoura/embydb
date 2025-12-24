#include <gtest/gtest.h>
#include <cstring>
#include "storage/disk/disk_manager.h"
#include "common/config.h"

namespace embydb {
    class DiskManagerTest : public ::testing::Test {
    protected:
        
        void SetUp() override {
            remove("test.db");
        }

        void TearDown() override {
            remove("test.db");
        }
    };

    TEST_F(DiskManagerTest, WriteAndReadPage) {
        char buf[PAGE_SIZE];
        char data[PAGE_SIZE];
        std::string db_file = "test.db";

        {
            DiskManager dm(db_file);
            
        
            std::memset(data, 'A', PAGE_SIZE);
            
            std::string msg = "Test Page functionality";
            std::memcpy(data, msg.c_str(), msg.length());

            dm.WritePage(0, data);
            
        }
        {
            DiskManager dm(db_file);
        
            std::memset(buf, 0, PAGE_SIZE);

            dm.ReadPage(0, buf);

            EXPECT_EQ(std::memcmp(buf, data, PAGE_SIZE), 0);
        }
    }

}