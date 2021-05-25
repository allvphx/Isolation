//
// Created by pan on 25/5/21.
//

#ifndef ENCODINGS_TXN_H
#define ENCODINGS_TXN_H

#include <vector>

struct Tnx_item {
    char cmd;   // r or w
    int key, val = -1;
};

struct Tnx {
    int TnxID = 0;
    std::vector<Tnx_item> items;
};

#endif //ENCODINGS_TXN_H
