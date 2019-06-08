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
/**
 * @param item_id ID of the item whose stock is to be checked
 * @return boolean value indicating where the stock for that item is present
 */
bool Staff::check_item_stock(std::string item_id) {
    static Store* store_instance = Store::get_instance_of_store();
    std::vector<Item*> items = store_instance->getItems();
    unsigned int items_sz = store_instance->getTotalItems();
    bool stock_present = false, item_present = false;
//    std::cout << "HERE1" << std::endl;
    for(unsigned int i = 0; i < items_sz; i++) {
//        std::cout << "HERE2 " << items[i]->item_id << " " << item_id << std::endl;
        if(item_id == items[i]->item_id) {
            item_present = true;
            if(items[i]->item_stock > 0) {
                stock_present = true;
            }
            else {
                stock_present = false;
            }
            break;
        }
    }
    if (!item_present) {
        std::cout << "\033[1;31mItem Not Found\033[0m\n";
    }
//    std::cout << "Stock present = " << stock_present << std::endl;
    return stock_present;
}
/**
 * @param mode  the type of modification to be done on the item
 * @return  boolean value indicating modification success / failure
 */
bool Staff::modify_item(ModifyModes mode, std::string item_id) {
    static Store* store_instance = Store::get_instance_of_store();
    if (mode == DEFAULT_MODE)
        return true;
    std::vector<Item*> items = store_instance->getItems();
    unsigned int len_items = store_instance->getTotalItems();
    unsigned int i = 0;
    bool flag = false;
    for (; i < len_items; i++) {
        if (items[i]->item_id == item_id) {
            flag = true;
            break;
        }
    }
    if (!flag) {
        std::cout << "\033[1;31mItem not found\033[0m" << std::endl;
        return false;
    }
    Item* target_item = items[i];
    // TODO: Complete below
    switch(mode) {
        case MODIFY_NAME: {
            std::string new_name;
            std::cout << "MODIFY NAME" << std::endl;
            std::cin >> new_name;
            target_item->item_name = new_name;
        }
            break;
        case MODIFY_PRICE: {
            float new_price;
            std::cout << "MODIFY PRICE" << std::endl;
            std::cin >> new_price;
            target_item->item_price = new_price;
        }
            break;
        case MODIFY_STOCK: {
            unsigned int new_stock;
            std::cout << "MODIFY STOCK" << std::endl;
            std::cin >> new_stock;
            target_item->item_stock = new_stock;
        }
            break;
        case MODIFY_EXPIRY: {
            std::string new_expiry;
            std::cout << "MODIFY EXPIRY" << std::endl;
            std::cin >> new_expiry;
            target_item->convertToTM(new_expiry);
        }
            break;
        default:
            std::cout << "\033[1;31mIncorrect choice, please enter choice from 1 to 4\n\033[0m" << std::endl;
            return false;
    }
    return true;
}