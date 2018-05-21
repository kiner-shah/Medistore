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
        Customer **customers;
        long totalCustomers;
        Staff **staff;                             // defining a Singleton so that only one instance of store exists
        long totalStaff;
        bool loadCustomerData();
        bool loadStaffData();
        bool loadItemsData();
        bool loadItemTransactionsData();
        Store() {                                 // private constructor for Singleton
            customers = NULL;
            totalCustomers = 0;
            staff = NULL;
            totalStaff = 0;
            items = NULL;
            totalItems = 0;
            item_transactions = NULL;
            totalItemTransactions = 0;
            if(!loadCustomerData()) {
                std::cerr << "ERROR: loadCustomerData(): FAILED" << std::endl;
            }
            if(!loadStaffData()) {
                std::cerr << "ERROR: loadStaffData(): FAILED" << std::endl;
            }
            if(!loadItemsData()) {
                std::cerr << "ERROR: loadItemsData(): FAILED" << std::endl;
            }
            if(!loadItemTransactionsData()) {
                std::cerr << "ERROR: loadItemTransactionsData(): FAILED" << std::endl;
            }
        }
    protected:
        Item **items;
        long totalItems;
        ItemTransaction **item_transactions;
        long totalItemTransactions;
    public:
        Bill generate_bill();
        void display_items();
        bool modify_stock();
//        bool validate_customer();
        bool validate_staff();
        Staff *getStaff();
        Staff *getCustomers();
        static Store& get_instance_of_store() {
            static Store instance;
            return instance;
        }
};

#endif	/* STORE_H */

