/* 
 * File:   item_transaction.h
 * Author: user
 *
 * Created on 22 November, 2017, 9:22 PM
 */

#ifndef ITEM_TRANSACTION_H
#define	ITEM_TRANSACTION_H

typedef struct ITEM_TRANSACTION {
    long item_trans_id;
    long timestamp;
    unsigned int changes_count;
    std::string *changes_list;
    ITEM_TRANSACTION(long transID, long ts, int changesCount) {
        item_trans_id = transID;
        timestamp = ts;
        changes_count = changesCount;
        // TODO: changes list
    }
} ItemTransaction;

#endif	/* ITEM_TRANSACTION_H */

