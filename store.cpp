/* 
 * File:   store.cpp
 * Author: Kiner Shah
 *
 * Created on 3 November, 2017, 9:20 PM
 */

#include "store.h"
// TODO
Bill Store::generate_bill() {
    Bill bill;
    return bill;
}

// TODO
void Store::display_items() {
    std::cout << "Items list" << std::endl;
}

// TODO
bool Store::modify_stock() {
    return true;
}

//bool Store::validate_customer() {
//    return authenticate_customer();
//}

/**
 * Function which validates staff member
 * @return Validation result
 */
bool Store::validate_staff() {
    return authenticate_staff();
}

/**
 * Function that loads customer data
 * @return Boolean value indicating load success / failure
 */
bool Store::loadCustomerData() {
    std::ifstream i;
    i.open("customer_data.bin", std::ios::binary | std::ios::in);
    while(true) {
        char *buf;
        i.read(buf, sizeof(Customer));
        if(i.fail() || i.bad()) return false; 
        else if(i.eof()) break;
        Customer *temp_customer = (Customer *) realloc(*customers, sizeof(Customer) * (++totalCustomers));
        if(temp_customer == NULL) {
            std::cerr << "ERROR: loadCustomerData(): Cannot allocate more memory" << std::endl;
            return false;
        }
        *customers = temp_customer;
        customers[totalCustomers - 1] = (Customer *) buf;
    }
    i.close();
    return true;
}

/**
 * Function that loads staff data
 * @return Boolean value indicating load success / failure
 */
bool Store::loadStaffData() {
    std::ifstream i;
    i.open("staff_data.bin", std::ios::binary | std::ios::in);
    while(true) {
        char *buf;
        i.read(buf, sizeof(Staff));
        if(i.fail() || i.bad()) return false; 
        else if(i.eof()) break;
        Staff *temp_staff = (Staff *) realloc(*staff, sizeof(Staff) * (++totalStaff));
        if(temp_staff == NULL) {
            std::cerr << "ERROR: loadStaffData(): Cannot allocate more memory" << std::endl;
            return false;
        }
        *staff = temp_staff;
        staff[totalStaff - 1] = (Staff *) buf;
    }
    i.close();   
    return true;
}

// TODO
bool Store::loadItemsData() {
    std::ifstream i;
    i.open("items_data.bin", std::ios::binary);
    std::string val;
    while(getline(i, val, ',')) {
        std::cout << val << " ";
    }
    std::cout << std::endl;    
    return true;
}

// TODO
bool Store::loadItemTransactionsData() {
    std::ifstream i;
    i.open("item_transactions_data.bin", std::ios::binary);
    std::string val;
    while(getline(i, val, ',')) {
        std::cout << val << " ";
    }
    std::cout << std::endl;    
    return true;
}