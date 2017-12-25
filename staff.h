/* 
 * File:   staff.h
 * Author: Kiner Shah
 *
 * Created on 3 November, 2017, 9:12 PM
 */

#ifndef STAFF_H
#define	STAFF_H

#include <string>

class Staff {
    private:
        std::string staff_name;
        std::string password;
        std::string staff_id;
    public:
        bool check_item_stock(std::string item_name);
        bool add_customer();
        bool modify_item(int mode);
        void check_item_transactions();
        bool login();
        Staff() {
            staff_name = "";
            password = "";
            staff_id = "";
            
        }
};

#endif	/* STAFF_H */

