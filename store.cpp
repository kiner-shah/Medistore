/* 
 * File:   store.cpp
 * Author: Kiner Shah
 *
 * Created on 3 November, 2017, 9:20 PM
 */

#include "store.h"
#include <iostream>
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

bool Store::validate_customer() {
    return true;
}