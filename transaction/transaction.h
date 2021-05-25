//
// Created by pan on 25/5/21.
//

#ifndef ENCODINGS_TRANSACTION_H
#define ENCODINGS_TRANSACTION_H

#include "../isolation_levels/read_uncommited.h"

class Tnx_manager {
    RU_storage *store;

public:
    explicit Tnx_manager(RU_storage* _store) {
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
};

#endif //ENCODINGS_TRANSACTION_H
