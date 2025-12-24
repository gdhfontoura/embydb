#pragma once
#include <cstring>
#include "common/config.h"

namespace embydb {

class Page{
public:
    // memory reset so it has no garbage
    Page() {ResetMemory();}
    ~Page() = default;

    inline char *GetData() {return data_;}

    inline page_id_t GetPageId() {return page_id_; }

    inline void ResetMemory() { memset(data_, 0, PAGE_SIZE);}

protected:

    char data_[PAGE_SIZE]{};

    page_id_t page_id_ = INVALID_PAGE_ID;
};

}