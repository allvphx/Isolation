//
// Created by pan on 27/5/21.
//

//
// Created by pan on 26/5/21.
//

//
// Created by pan on 25/5/21.
//

#include "../isolation_levels/mvcc_mvto.h"
#include "txn.h"
#include "iostream"

using namespace std;

namespace MVCC {
    auto store = &MVTO::heads;
    Txn tx1, tx2;

    void *handleTxn(void *cur) {
        Txn *s = (Txn *) (cur);
        int name = s->TxnID;
        printf("Begin TxN %d, ts = %d\n", name, s->TxnID = MVTO::ts.get_TS());
        for (Txn_item cr : s->items) {
            printf("TxN %d: processing %c\n", name, cr.cmd);
            if (cr.cmd == 'r') {
                int ans = MVTO::Get(cr.key, s->TxnID);
                if (ans == -1) {
                    MVTO::Abort(s->TxnID);
                    printf("TxN %d: Aborted\n", name);
                    return 0;
                } else {
                    printf("TxN %d: Get(%d) = %d\n", name, cr.key, ans);
                }
            } else {
                if(!MVTO::Put(cr.key, s->TxnID, cr.val)) {
                    MVTO::Abort(s->TxnID);
                    printf("TxN %d: Aborted\n", name);
                    return 0;
                } else {
                    printf("TxN %d: Put(%d) = %d\n", name, cr.key, cr.val);
                }
            }
        }
        MVTO::Commit(s->TxnID);
        printf("Commit TxN %d\n", name);
        return 0;
    }
}

#include "pthread.h"

using namespace MVCC;

int main() {
    tx1.setID(1);
    tx1.insert('w', 1, 1);
    tx1.insert('r', 1, -1);
    tx1.insert('r', 1, -1);
    tx1.insert('r', 1, -1);

    tx2.setID(2);
    tx2.insert('w', 1, 4);
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