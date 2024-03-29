//
// Created by pan on 25/5/21.
//

#ifndef ENCODINGS_READ_COMMITED_H
#define ENCODINGS_READ_COMMITED_H

//
// Created by pan on 25/5/21.
//

#include "../res_lock/lock.h"
#include "../transaction/txn.h"
#include <cstring>
#include "storage.h"

class RC_storage : public Storage {
public:
    void Get(int TID, int key, int &val) {
        val = items[key];
        lock_items[key].Release(TID);
    }

    void Put(int TID, int key, int val) {
        items[key] = val;
        lock_items[key].Release(TID);
    }

    void Release(int TID) {
    }
};


#endif //ENCODINGS_READ_COMMITED_H
