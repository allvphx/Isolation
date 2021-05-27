//
// Created by pan on 27/5/21.
//

#ifndef ENCODINGS_CAS_H
#define ENCODINGS_CAS_H

#include "mutex"

namespace CAS {
    std::mutex atom;

    template<class T> bool atom_change2(T& val,T s,T t) {
        atom.lock();
        bool eq = val == s;
        if (eq) {
            val = t;
        }
        atom.unlock();
        return eq;
    }
}


#endif //ENCODINGS_CAS_H
