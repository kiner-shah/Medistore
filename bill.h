/* 
 * File:   bill.h
 * Author: user
 *
 * Created on 22 November, 2017, 9:22 PM
 */

#ifndef BILL_H
#define	BILL_H

#include "item.h"
typedef struct BILL {
    long bill_no;
    Item *item_list;
    int *item_qty;
    float total_amount;
} Bill;

#endif	/* BILL_H */

