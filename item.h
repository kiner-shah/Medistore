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
#include <cstring>
#include <iostream>
#include <sstream>

typedef struct ITEM {
    std::string item_id;
    std::string item_name;
    unsigned int item_stock;
    float item_price;
    struct tm item_expiry;
    std::string item_expiry_str;
    void convertToTM(std::string date) {
        if(date != "NIL") {
            int temp_date_len = date.length(), count = 0, j = 0;
            char buf[1024]; memset(buf, '\0', 1024);
            for(int i = 0; i < temp_date_len; i++) {
                if(date[i] != '-') buf[j++] = date[i];
                else if(count == 0) {
                    count++;
                    item_expiry.tm_year = atoi(buf);
                    memset(buf, '\0', 1024); 
                    j = 0;
                }
                else if(count == 1) {
                    count++;
                    item_expiry.tm_mon = atoi(buf);
                    memset(buf, '\0', 1024); 
                    j = 0;
                }
                
            }
            if(count == 2) {
                count++;
                item_expiry.tm_mday = atoi(buf);
                memset(buf, '\0', 1024); 
                j = 0;
            }
            item_expiry.tm_year -= 1900;
            item_expiry.tm_mon--;
            if(count == 2) item_expiry.tm_mday = 1;
        }
        item_expiry_str = date;
    }
    ITEM(std::string id, std::string name, unsigned int stock, float price, std::string date) {
        item_id = id;
        item_name = name;
        item_stock = stock;
        item_price = price;
        item_expiry.tm_gmtoff = 0;
        item_expiry.tm_hour = 0;
        item_expiry.tm_isdst = 0;
        item_expiry.tm_mday = 0;
        item_expiry.tm_min = 0;
        item_expiry.tm_mon = 0;
        item_expiry.tm_sec = 0;
        item_expiry.tm_wday = 0;
        item_expiry.tm_yday = 0;
        item_expiry.tm_year = 0;
        item_expiry.tm_zone = NULL;
        convertToTM(date);
    }
    std::string to_string() {
        //ItemID,ItemName,ItemStock,ItemPrice,ItemExpiry(yyyy-mm-dd)
        std::ostringstream os;
        os << item_id << ',' << item_name << ',' << item_stock << ',' << item_price << ',' << item_expiry_str;
        return os.str();
    }
} Item;

#endif	/* ITEM_H */

