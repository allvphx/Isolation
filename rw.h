//
// Created by pan on 25/5/21.
//

#ifndef ENCODINGS_RW_H
#define ENCODINGS_RW_H

#include <cstring>
#include "lock.h"

class Storage {
    static const int SIZE = 10000;
    Lock lock_items[SIZE];
    int items[SIZE];

public:
    Storage() {
        memset(items, -1, sizeof (items));
    }

    void Get(int key, int &val) {
        while (!lock_items[key].Share());    // TO-DO: use a queue to maintain the sleep and awake.
        val = items[key];
        lock_items[key].Release();
    }

    void Put(int key, int val) {
        while (!lock_items[key].Exclusive());
        items[key] = val;
        lock_items[key].Release();
    }
};

#endif //ENCODINGS_RW_H
