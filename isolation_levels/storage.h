//
// Created by pan on 25/5/21.
//

#ifndef ENCODINGS_STORAGE_H
#define ENCODINGS_STORAGE_H

#include "../res_lock/lock.h"
#include "cstring"

class Storage {
public:
    static const int SIZE = 10000;
    Lock lock_items[SIZE];
    int items[SIZE];

    Storage() {
        memset(items, -1, sizeof (items));
    }

    virtual void Get(int TID, int key, int &val) = 0;
    virtual void Put(int TID, int key, int val) = 0;
    virtual void Release(int TID) = 0;
};

#endif //ENCODINGS_STORAGE_H
