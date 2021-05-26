//
// Created by pan on 25/5/21.
//

#ifndef ENCODINGS_2PL_SERIALIZABLE_H
#define ENCODINGS_2PL_SERIALIZABLE_H

#include "storage.h"
#include "vector"

class PL2_storage: public Storage {
public:
    static const int max_txn = 100;
    std::vector<int> pool[max_txn];

    void Get(int TID, int key, int &val) {
        while (!lock_items[key].Share(TID));
        val = items[key];
        pool[TID].emplace_back(key);
    }

    void Put(int TID, int key, int val) {
        while (!lock_items[key].Exclusive(TID));
        items[key] = val;
        pool[TID].emplace_back(key);
    }

    void Release(int TID) {
        for (int i : pool[TID]) {
            lock_items[i].Release(TID);
        }
        pool[TID].clear();
    }
};

#endif //ENCODINGS_2PL_SERIALIZABLE_H
