#pragma once

#include <cstdint>

// TODO: there will be several events, how to receive all of them on 1 controller?

class EventReceiver {
public:
    virtual void button_pressed(uint64_t current_time_us) = 0;
};
