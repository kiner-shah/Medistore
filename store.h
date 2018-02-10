/* 
 * File:   store.h
 * Author: Kiner Shah
 *
 * Created on 3 November, 2017, 9:03 PM
 */

#ifndef STORE_H
#define	STORE_H

#include "item.h"
#include "item_transaction.h"
#include "bill.h"
#include "staff.h"
#include "customer.h"
#include "authentication.h"
#include <iostream>
#include <fstream>
#include <string>

class Store {
    private:
        Customer *customers;
        Staff *staff;                             // defining a Singleton so that only one instance of store exists
        bool loadCustomerData();
        bool loadStaffData();
        bool loadItemsData();
        bool loadItemTransactionsData();
        Store() {                                 // private constructor for Singleton
            customers = 0;
            staff = 0;
            items = 0;
            item_transactions = 0;
        }
    protected:
        Item *items;
        ItemTransaction *item_transactions;
    public:
        virtual Bill generate_bill() final;
        virtual void display_items() final;
        virtual bool modify_stock() final;
        virtual bool validate_customer() final;
        virtual bool validate_staff() final;
        
        static Store& get_instance_of_store() {
            static Store instance;
            return instance;
        }
};

#endif	/* STORE_H */

