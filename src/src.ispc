export void noop(){
    // noop
}

export uniform float avg(uniform float array[], uniform unsigned int64 size) {
    float acc = 0;
    foreach(i = 0 ... size) {
        acc += array[i];
    }
    return reduce_add(acc) / (float) size;
}