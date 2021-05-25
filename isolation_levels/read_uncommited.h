//
// Created by pan on 25/5/21.
//

#ifndef ENCODINGS_READ_UNCOMMITED_H
#define ENCODINGS_READ_UNCOMMITED_H

#include "../res_lock/lock.h"
#include "../transaction/txn.h"
#include <cstring>
#include "storage.h"
#include "queue"

using namespace std;

class RU_storage: public Storage {
public:
    static const int max_txn = 100;
    std::vector<int> pool[max_txn];

    void Get(int key, int &val) {
        val = items[key];
    }

    void Put(int TID, int key, int val) {
        while (!lock_items[key].Exclusive(TID));
        items[key] = val;
        pool[TID].emplace_back(key);
    }

    void Release(int TID) {
        for (int i : pool[TID]) {
            lock_items[i].Release();
        }
        pool[TID].clear();
    }
};


#endif //ENCODINGS_READ_UNCOMMITED_H
