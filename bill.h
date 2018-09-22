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
    std::string doctor_name;
    unsigned int item_id_no;
    std::string *item_id_list;
    int *item_qty;
    float total_amount;
    
    BILL(long bno, std::string doctor, unsigned int items_no, float tot) {
        bill_no = bno;
        doctor_name = doctor;
        item_id_no = items_no;
        item_id_list = NULL;
        item_qty = NULL;
        total_amount = tot;
    }
    ~BILL() {
        if(item_id_list != NULL) {
            delete[] item_id_list;
            item_id_list = NULL;
        }
        if(item_qty != NULL) {
            delete[] item_qty;
            item_qty = NULL;
        }
    }
} Bill;

#endif	/* BILL_H */

