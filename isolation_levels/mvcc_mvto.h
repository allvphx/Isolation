//
// Created by pan on 27/5/21.
//

#ifndef ENCODINGS_MVCC_MVTO_H
#define ENCODINGS_MVCC_MVTO_H

#include <iostream>
#include "../res_lock/timestamp.h"
#include "../res_lock/cas.h"
#include "set"
#include "istream"

namespace MVTO {

    TS_producer ts;

    const int INF = 1000000000, TS_N = 100;
    static const int SIZE = 10000;

    class mvcc_item {
    public:
        int txn_id, begin_ts, end_ts, read_ts, value;
        mvcc_item *next;

        mvcc_item() {
            txn_id = 0;
            begin_ts = end_ts = INF;
            next = nullptr;
            value = -1;
            read_ts = 0;
        };
    };

    mvcc_item *heads[SIZE] = {nullptr};
    std::set<int> record[TS_N]; // the positions that are changed by the transaction.

    int Get(int pos, int Tid) {
        auto it = heads[pos];
        while (it != nullptr && (Tid>=it->end_ts || Tid<it->begin_ts)) {
            it = it->next;
        }
        if (it == nullptr || (it->txn_id!=0 && it->txn_id!=Tid)) { // aborted
            return -1;
        }
        int cur_val = it->read_ts;
        if (cur_val < Tid) {
            if(!CAS::atom_change2(it->read_ts, cur_val, Tid)) {
                return -1;
            }
        }
        return it->value;
    }

    std::mutex atom_set;

    bool Put(int pos, int Tid, int value) {
        auto Bxplus = new mvcc_item();
        Bxplus->txn_id = Tid;
        Bxplus->read_ts = 0;
        Bxplus->value = value;
        Bxplus->next = nullptr;
        Bxplus->begin_ts = Tid;
        Bxplus->end_ts = INF;

        atom_set.lock();
        record[Tid].insert(pos);
        atom_set.unlock();

        if (heads[pos] == nullptr && CAS::atom_change2(heads[pos], (mvcc_item*)(nullptr), Bxplus)) {
            // new node added, thread safe.
            return true;
        } else if (CAS::atom_change2(heads[pos]->txn_id, 0, Tid)) {
            // write lock gain, hence it is thread safe here.
            auto it = heads[pos];
            if (it->read_ts > Tid) {   // invalid read.
                return false;
            }
            Bxplus->next = heads[pos];
            heads[pos]->end_ts = Tid;
            heads[pos] = Bxplus;
            Bxplus->next->txn_id = 0;
            return true;
        } else if (heads[pos]->txn_id == Tid) {
            // it is thread safe, since the write lock is gained.
            heads[pos]->value = value;
            return true;
        }
        else {
            // one of two rules defined in MVTO violated.
            return false;
        }
    }

    bool Commit(int Tid) {
        for (auto pos : record[Tid]) {
            if (heads[pos]->txn_id != Tid) {
                // with lock, it is thread safe.
                return false;
            } else {
                heads[pos]->txn_id = 0;
            }
        }
        record[Tid].clear();
        return true;
    }

    bool Abort(int Tid) {
        for (auto pos : record[Tid]) {
            if (heads[pos]->txn_id != Tid) {
                // with lock, it is thread safe.
                continue;
            } else {
                auto it = heads[pos];
                heads[pos] = heads[pos]->next;
                delete it;
            }
        }
        record[Tid].clear();
        return true;
    }
}

#endif //ENCODINGS_MVCC_MVTO_H
