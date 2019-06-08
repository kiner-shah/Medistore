/* 
 * File:   store.h
 * Author: Kiner Shah
 *
 * Created on 3 November, 2017, 9:03 PM
 */

#ifndef STORE_H
#define	STORE_H

#include "item.h"
#include "bill.h"
#include "staff.h"
#include "customer.h"
#include "authentication.h"
#include "file_mngr.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>

class Store {
    private:
        std::vector<Customer*> customers;
        unsigned int totalCustomers; 
        std::vector<Staff*> staff; // defining a Singleton so that only one instance of store exists
        unsigned int totalStaff;
        std::vector<Item*> items;
        long totalItems;
        std::vector<Bill*> bills;
        long totalBills;
        FileMngr *customer_data;
        FileMngr *staff_data;
        FileMngr *items_data;
        FileMngr *bill_data;
        bool loadCustomerData();
        bool loadStaffData();
        bool loadItemsData();
        bool loadBillData();
        bool unloadCustomerData();
        bool unloadStaffData();
        bool unloadItemsData();
        bool unloadBillData();
        static Store* instance;
        Store() {                                 // private constructor for Singleton
//            customers = NULL;
            totalCustomers = 0;
//            staff = NULL;
            totalStaff = 0;
//            items = NULL;
            totalItems = 0;
//            item_transactions = NULL;
            totalBills = 0;
            
            if(!loadBillData()) {
                std::cerr << "ERROR: loadBillData(): FAILED" << std::endl;
            }
            if(!loadCustomerData()) {
                std::cerr << "ERROR: loadCustomerData(): FAILED" << std::endl;
            }
            if(!loadStaffData()) {
                std::cerr << "ERROR: loadStaffData(): FAILED" << std::endl;
            }
            if(!loadItemsData()) {
                std::cerr << "ERROR: loadItemsData(): FAILED" << std::endl;
            }
        }
        
    public:
        Bill* generate_bill(std::map<std::string, int> items_qty_map, long, std::string, float);
        Customer* generate_customer(std::string name, long bill_no);
        void display_items();
        bool modify_stock();
//        bool validate_customer();
        int validate_staff();
        std::vector<Staff*> getStaff() { return staff; } 
        unsigned int getTotalStaff() { return totalStaff; }
        std::vector<Customer*> getCustomers() { return customers; }
        unsigned int getTotalCustomers() { return totalCustomers; }
        std::vector<Item*> getItems() { return items; }
        unsigned int getTotalItems() { return totalItems; }
        std::vector<Bill*> getBills() { return bills; }
        unsigned int getTotalBills() { return totalBills; }
        void addNewBill(Bill* bill);
        void addNewCustomer(Customer* customer);
//        static Store& get_instance_of_store() {       // Another alternative for Singleton
//            static Store instance;
//            return instance;
//        }
        static Store* get_instance_of_store() {
            if(instance == NULL) {
                instance = new Store();
            }
            return instance;
        }
        ~Store() {
            if(!unloadBillData()) {
                std::cerr << "ERROR: unloadBillData(): FAILED" << std::endl;
            }
            if(!unloadCustomerData()) {
                std::cerr << "ERROR: unloadCustomerData(): FAILED" << std::endl;
            }
            if(!unloadStaffData()) {
                std::cerr << "ERROR: unloadStaffData(): FAILED" << std::endl;
            }
            if(!unloadItemsData()) {
                std::cerr << "ERROR: unloadItemsData(): FAILED" << std::endl;
            }
        }
};

#endif	/* STORE_H */

