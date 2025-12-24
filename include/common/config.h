#pragma once
#include <cstdint>

namespace embydb {

    static constexpr int PAGE_SIZE = 4096;

    using page_id_t = int32_t;
    using frame_id_t = int32_t;

    static constexpr page_id_t INVALID_PAGE_ID = -1;
    static constexpr frame_id_t INVALID_FRAME_ID = -1;

}