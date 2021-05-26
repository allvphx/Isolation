//
// Created by pan on 25/5/21.
//

#ifndef ENCODINGS_LOCK_H
#define ENCODINGS_LOCK_H

#include "mutex"
#include "set"

class Lock {
    std::mutex atom_lock;   // the lock used for atomic execution.
    int8_t state;           // the state of the lock item.
    std::set<int> shared_txn;

public:
    const int8_t NL = 0, S = 1,X = 2;

    Lock() {
        shared_txn.clear();
        state = NL;
    }

    Lock(int x) {
        state = int8_t(x);
    }

    int8_t State() const {
        return state;
    }

    void Release(int TID) {
        atom_lock.lock();
        if (state == S) {
            auto it = shared_txn.find(TID);
            shared_txn.erase(it);
            if (shared_txn.empty()) {
                state = NL;
            }
        } else {
            state = NL;
            shared_txn.clear();
        }
        atom_lock.unlock();
    }

    bool Share(int TID) {
        atom_lock.lock();
        bool suc = true;
        bool exist = shared_txn.find(TID) != shared_txn.end();
        if (state == NL) {
            state = S;
            shared_txn.insert(TID);
        } else if (state == S) {
            shared_txn.insert(TID);
        } else if(!(state == X && exist)) {
            suc = false;
        }
        atom_lock.unlock();
        return suc;
    }

    bool Exclusive(int TID) {
        atom_lock.lock();
        bool suc = true;
        // thread unsafe here.
        bool exist = shared_txn.find(TID) != shared_txn.end();
        if (state == X && exist) {
            suc = true;
        } else if(state == NL || (state == S && shared_txn.size()==1 && exist)) {
            shared_txn.clear();
            state = X;
            shared_txn.insert(TID);
        } else {
            suc = false;
        }
        atom_lock.unlock();
        return suc;
    }
};

// one thread maintaining the queue ?

#endif //ENCODINGS_LOCK_H
