/* 
 * File:   store.cpp
 * Author: Kiner Shah
 *
 * Created on 3 November, 2017, 9:19 PM
 */

#include "staff.h"
#include "store.h"
/* Global variables */
bool Staff::check_item_stock(std::string item_name) {
    static Store store_instance = Store::get_instance_of_store();
    return true;
}

bool Staff::add_customer() {
    /*
     * 1. Search if customer is present already
     * 2. If not, then add the new customer
     */
    
    return true;
}

bool Staff::modify_item(int mode) {
    return true;
}

void Staff::check_item_transactions() {
    
}

bool Staff::login() {
    return true;
}