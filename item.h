/* 
 * File:   item.h
 * Author: user
 *
 * Created on 22 November, 2017, 9:21 PM
 */

#ifndef ITEM_H
#define	ITEM_H

#include <ctime>
#include <string>

typedef struct ITEM {
    std::string item_id;
    std::string item_name;
    int item_stock;
    float item_price;
    struct tm item_expiry;
} Item;

#endif	/* ITEM_H */

