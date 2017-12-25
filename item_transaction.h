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
    std::string *changes_list;
} ItemTransaction;

#endif	/* ITEM_TRANSACTION_H */

