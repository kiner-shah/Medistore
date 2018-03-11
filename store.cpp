/* 
 * File:   store.cpp
 * Author: Kiner Shah
 *
 * Created on 3 November, 2017, 9:20 PM
 */

#include "store.h"
Bill Store::generate_bill() {
    Bill bill;
    return bill;
}

void Store::display_items() {
    std::cout << "Items list" << std::endl;
}

bool Store::modify_stock() {
    return true;
}

//bool Store::validate_customer() {
//    return authenticate_customer();
//}

bool Store::validate_staff() {
    return authenticate_staff();
}

bool Store::loadCustomerData() {
    std::ifstream i;
    i.open("customer_data.bin", std::ios::binary);
    std::string val;
    while(getline(i, val, ',')) {
        std::cout << val << " ";
    }
    std::cout << std::endl;
}

bool Store::loadStaffData() {
    std::ifstream i;
    i.open("staff_data.bin", std::ios::binary);
    std::string val;
    while(getline(i, val, ',')) {
        std::cout << val << " ";
    }
    std::cout << std::endl;    
}

bool Store::loadItemsData() {
    std::ifstream i;
    i.open("items_data.bin", std::ios::binary);
    std::string val;
    while(getline(i, val, ',')) {
        std::cout << val << " ";
    }
    std::cout << std::endl;    
}

bool Store::loadItemTransactionsData() {
    std::ifstream i;
    i.open("item_transactions_data.bin", std::ios::binary);
    std::string val;
    while(getline(i, val, ',')) {
        std::cout << val << " ";
    }
    std::cout << std::endl;    
}