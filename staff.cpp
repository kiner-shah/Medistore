/* 
 * File:   store.cpp
 * Author: Kiner Shah
 *
 * Created on 3 November, 2017, 9:19 PM
 */

#include "staff.h"
#include "store.h"
#include <vector>
/* Global variables */
bool Staff::check_item_stock(std::string item_name) {
    static Store* store_instance = Store::get_instance_of_store();
    std::vector<Item*> items = store_instance->getItems();
    unsigned int items_sz = store_instance->getTotalItems();
    
    for(int i = 0; i < items_sz; i++) {
        if(item_name == items[i]->item_name) {
            if(items[i]->item_stock > 0)
                return true;
            else 
                return false;
        }
    }
    
    std::cout << "\033[1;31mItem Not Found\033[0m\n";
    return false;
}

bool Staff::modify_item(int mode) {
    return true;
}

void Staff::check_item_transactions() {
    
}