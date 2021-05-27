//
// Created by pan on 27/5/21.
//

#ifndef ENCODINGS_TIMESTAMP_H
#define ENCODINGS_TIMESTAMP_H

#include "mutex"

class TS_producer {
    int TS;
    std::mutex atom;

public:
    TS_producer() {
        TS = 0;
    }

    void init() {
        atom.lock();
        TS = 0;
        atom.unlock();
    }

    int get_TS() {
        int res;
        atom.lock();
        TS += 1;
        res = TS;
        atom.unlock();
        return res;
    }
};

#endif //ENCODINGS_TIMESTAMP_H
