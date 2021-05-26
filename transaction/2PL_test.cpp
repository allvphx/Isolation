//
// Created by pan on 26/5/21.
//

//
// Created by pan on 25/5/21.
//

#include "../isolation_levels/2pl_serializable.h"
#include "txn.h"
#include "iostream"

using namespace std;

namespace PL2 {
    PL2_storage store;
    Txn tx1, tx2;

    void *handleTxn(void *cur) {
        Txn *s = (Txn *) (cur);
        int ans = 0;
        printf("Begin TxN %d\n", s->TxnID);
        PL2_storage *tmp = &PL2::store;
        for (Txn_item cr : s->items) {
            printf("TxN %d: processing %c\n", s->TxnID, cr.cmd);
            if (cr.cmd == 'r') {
                tmp->Get(s->TxnID, cr.key, ans);
                printf("TxN %d: Get(%d) = %d\n", s->TxnID, cr.key, ans);
            } else {
                tmp->Put(s->TxnID, cr.key, cr.val);
                printf("TxN %d: Put(%d) = %d\n", s->TxnID, cr.key, cr.val);
            }
        }
        tmp->Release(s->TxnID);
        printf("Commit TxN %d\n", s->TxnID);
        return 0;
    }
}

#include "pthread.h"

using namespace PL2;

int test_2PL() {
    tx1.setID(1);
    tx1.insert('w', 1, 1);
    tx1.insert('r', 1, -1);
    tx1.insert('r', 1, -1);
    tx1.insert('r', 1, -1);

    tx2.setID(2);
    tx2.insert('r', 1, -1);
    tx2.insert('r', 1, -1);
    tx2.insert('w', 1, 2);
    tx2.insert('r', 1, -1);

    pthread_t tid1, tid2;
    int ret = pthread_create(&tid1, nullptr, handleTxn, (void*)(&tx1));
    ret |= pthread_create(&tid2, nullptr, handleTxn, (void*)(&tx2));
    if (ret != 0) {
        cout << "pthread_create error: error_code=" << ret << endl;
    }
    pthread_exit(NULL);
}