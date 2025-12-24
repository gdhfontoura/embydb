#pragma once
#include "common/config.h"
#include <vector>
#include <mutex>


namespace embydb {


class ClockReplacer {
    public:
        ClockReplacer(size_t num_pages);
        ~ClockReplacer();

        void Pin(frame_id_t frame_id);
        void Unpin(frame_id_t frame_id);
        bool Victim(frame_id_t &frame_id);
        size_t Size() const;

    private:
        std::vector<bool> reference_bits_;
        std::vector<bool> pinned_;
        size_t clock_hand_;
        mutable std::mutex latch_;
    };
} 