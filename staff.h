/* 
 * File:   staff.h
 * Author: Kiner Shah
 *
 * Created on 3 November, 2017, 9:12 PM
 */

#ifndef STAFF_H
#define	STAFF_H

#include <string>
#include <fstream>

typedef enum MODIFY_MODES {
    MODIFY_NAME     = 1, 
    MODIFY_PRICE    = 2, 
    MODIFY_STOCK    = 3, 
    MODIFY_EXPIRY   = 4,
    DEFAULT_MODE    = 5
} ModifyModes;

class Staff {
    private:
        int staff_age;
        std::string staff_name;
        std::string staff_id;
        std::string staff_gender;
        std::string staff_address;
        std::string staff_password;
    public:
        Staff(std::string name, std::string id, std::string gender, std::string address, int age, std::string password) : staff_age(age), 
                staff_name(name), staff_id(id), staff_gender(gender), staff_address(address), staff_password(password) {
        }
        std::string getName() { return staff_name; }
        std::string getGender() { return staff_gender; }
        std::string getAddress() { return staff_address; }
        std::string getID() { return staff_id; }
        int getAge() { return staff_age; }
        std::string getPasswordHash() { return staff_password; }
        // Get items and item transactions from store for below functions
        bool check_item_stock(std::string item_name);
        bool modify_item(ModifyModes mode, std::string item_name);
};

#endif	/* STAFF_H */

