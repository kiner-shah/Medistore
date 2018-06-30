/* 
 * File:   store.cpp
 * Author: Kiner Shah
 *
 * Created on 3 November, 2017, 9:20 PM
 */

#include <sys/_default_fcntl.h>

#include "store.h"

Store* Store::instance = NULL;
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
    customer_data = new FileMngr("customer_data.bin", READ_FILE);
    if(customer_data->file_des == -1) return false;
    return true;
}

/**
 * Function that loads staff data
 * @return Boolean value indicating load success / failure
 */
bool Store::loadStaffData() {
    staff_data = new FileMngr("staff_data.bin", READ_FILE);
    if(staff_data->file_des == -1) return false;
    return true;
}

/**
 * Function that loads items data
 * @return Boolean value indicating load success / failure
 */
bool Store::loadItemsData() {
    items_data = new FileMngr("items_data.bin", READ_FILE);
    if(items_data->file_des == -1) return false;
    return true;
}

/**
 * Function that loads item transactions data
 * @return Boolean value indicating load success / failure
 */
bool Store::loadItemTransactionsData() {
    item_trans_data = new FileMngr("item_transactions_data.bin", READ_FILE);
    if(item_trans_data->file_des == -1) return false;
    return true;
}