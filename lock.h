//
// Created by pan on 25/5/21.
//

#ifndef ENCODINGS_LOCK_H
#define ENCODINGS_LOCK_H

#include "mutex"


class Lock {
    std::mutex atom_lock;   // the lock used for atomic execution.
    int8_t state;           // the state of the lock item.
    int share_count;

public:
    const int8_t NL = 0, S = 1,X = 2;

    Lock() {
        share_count = 0;
        state = NL;
    }

    Lock(int x) {
        state = int8_t(x);
    }

    int8_t State() const {
        return state;
    }

    void Release() {
        atom_lock.lock();
        if (state == S) {
            share_count -= 1;
            if (share_count == 0) {
                state = NL;
            }
        } else {
            state = NL;
        }
        atom_lock.unlock();
    }

    bool Share() {
        atom_lock.lock();
        bool suc = true;
        if (state == NL) {
            state = S;
            share_count = 0;
        } else if (state == S) {
            share_count += 1;
        } else {
            share_count = 0;
            suc = false;
        }
        atom_lock.unlock();
        return suc;
    }

    bool Exclusive() {
        atom_lock.lock();
        bool suc = true;
        if (state != NL) {
            suc = false;
        } else {
            state = X;
        }
        atom_lock.unlock();
        return suc;
    }
};

// one thread maintaining the queue ?

#endif //ENCODINGS_LOCK_H
