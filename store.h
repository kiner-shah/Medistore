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
#include "file_mngr.h"
#include <iostream>
#include <fstream>
#include <string>

class Store {
    private:
        Customer **customers;
        long totalCustomers;
        Staff **staff;                             // defining a Singleton so that only one instance of store exists
        long totalStaff;
        FileMngr *customer_data;
        FileMngr *staff_data;
        FileMngr *items_data;
        FileMngr *item_trans_data;
        bool loadCustomerData();
        bool loadStaffData();
        bool loadItemsData();
        bool loadItemTransactionsData();
        bool unloadCustomerData();
        bool unloadStaffData();
        bool unloadItemsData();
        bool unloadItemTransactionsData();
        static Store* instance;
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
//        static Store& get_instance_of_store() {
//            static Store instance;
//            return instance;
//        }
        static Store* get_instance_of_store() {
            if(instance == NULL) {
                instance = new Store();
            }
            return instance;
        }
//        ~Store() {
//            if(!unloadCustomerData()) {
//                std::cerr << "ERROR: unloadCustomerData(): FAILED" << std::endl;
//            }
//            if(!unloadStaffData()) {
//                std::cerr << "ERROR: unloadStaffData(): FAILED" << std::endl;
//            }
//            if(!unloadItemsData()) {
//                std::cerr << "ERROR: unloadItemsData(): FAILED" << std::endl;
//            }
//            if(!unloadItemTransactionsData()) {
//                std::cerr << "ERROR: unloadItemTransactionsData(): FAILED" << std::endl;
//            }
//        }
};

#endif	/* STORE_H */

