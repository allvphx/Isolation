//
// Created by pan on 25/5/21.
//

#ifndef ENCODINGS_TXN_H
#define ENCODINGS_TXN_H

#include <vector>

struct Txn_item {
    char cmd;   // r or w
    int key, val;

    Txn_item(char _cmd, int _key, int _val) {
        cmd = _cmd;
        key = _key;
        val = _val;
    }
};

struct Txn {
    int TxnID = 0;
    std::vector<Txn_item> items;

    void setID(int x) {
        TxnID = x;
    }

    void insert(char cmd, int key, int val) {
        items.emplace_back(cmd, key, val);
    }
};

#endif //ENCODINGS_TXN_H
