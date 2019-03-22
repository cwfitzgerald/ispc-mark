#include <cstdlib>

extern "C" void noop() {
    // noop
}

extern "C" float avg(float* array, std::size_t size) {
    float acc = 0;
    for (std::size_t i = 0; i < size; ++i) {
        acc += array[i];
    }
    return acc / (float) size;
}
