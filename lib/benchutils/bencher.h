#include <CircularBuffer.h>

#define MAX_BUFFER 50

typedef struct 
{
    void intit() {}

    void push(float v) {
        if (buf_.isFull()) {
            buf_.shift();
        }
        buf_.push(v);
    }

    float avg() {
        if (buf_.size() == 0) return 0;
        return sum()/buf_.size();
    }

    float sum() {
        float sums = -0.0f;
        for (int i = 0; i < buf_.size(); i++) {
            sums += buf_[i];
        }
        return sums;
    }

    void begin() {
        begin_stamp_ = millis();
    }

    void end() {
        uint32_t delta = millis() - begin_stamp_;
        push((float) delta);
    }

    CircularBuffer<float, MAX_BUFFER> buf_;
    uint32_t begin_stamp_ = 0;

} Bencher;
