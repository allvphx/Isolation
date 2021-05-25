//
// Created by pan on 25/5/21.
//

#ifndef ENCODINGS_2PL_SERIALIZABLE_H
#define ENCODINGS_2PL_SERIALIZABLE_H

#include "storage.h"

class PL2_storage: public Storage {
public:
    void Get(int key, int &val) {
        while (!lock_items[key].Share());
        val = items[key];
        lock_items[key].Release();
    }

    void Put(int key, int val) {
        while (!lock_items[key].Exclusive());
        items[key] = val;
        lock_items[key].Release();
    }
};

#endif //ENCODINGS_2PL_SERIALIZABLE_H
