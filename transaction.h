/* 
 * File:   transaction.h
 * Author: user
 *
 * Created on 17 December, 2017, 1:16 PM
 */

#ifndef TRANSACTION_H
#define	TRANSACTION_H

#include "bill.h"

typedef struct TRANS {
    long transID;
    struct tm *transTimestamp;
    float transAmt;
    char transType;
    Bill *transBill;
} Transaction;

#endif	/* TRANSACTION_H */