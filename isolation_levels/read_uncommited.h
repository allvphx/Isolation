//
// Created by pan on 25/5/21.
//

#ifndef ENCODINGS_READ_UNCOMMITED_H
#define ENCODINGS_READ_UNCOMMITED_H

#include "../res_lock/lock.h"
#include "../transaction/txn.h"
#include <cstring>
#include "storage.h"

class RU_storage: public Storage {
public:
    void Get(int key, int &val) {
        val = items[key];
    }

    void Put(int key, int val) {
        while (!lock_items[key].Exclusive());
        items[key] = val;
        lock_items[key].Release();
    }
};


#endif //ENCODINGS_READ_UNCOMMITED_H
