//
// Created by pan on 25/5/21.
//

#ifndef ENCODINGS_READ_UNCOMMITED_H
#define ENCODINGS_READ_UNCOMMITED_H

#include "lock.h"
#include "rw.h"
#include "txn.h"

class Txn_manager {
    Storage *store;

public:
    explicit Txn_manager(Storage* _store) {
        store = _store;
    }

    void handleTxn(const Tnx& s) {
        int ans = 0;
        printf("Begin TxN %d\n", s.TnxID);
        for(auto it=s.items.begin() ; it!=s.items.end(); it++) {
            if (it->cmd=='r') {
                store->Get(it->key, ans);
                printf("TxN %d: Get(%d) = %d\n", s.TnxID, it->key, ans);
            } else {
                store->Put(it->key, it->val);
                printf("TxN %d: Put(%d) = %d\n", s.TnxID, it->key, it->val);
            }
        }
        printf("Commit TxN %d\n", s.TnxID);
    }
}


#endif //ENCODINGS_READ_UNCOMMITED_H
