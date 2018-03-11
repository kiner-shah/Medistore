/* 
 * File:   admin.h
 * Author: user
 *
 * Created on 10 February, 2018, 4:12 PM
 */

#ifndef ADMIN_H
#define	ADMIN_H

#include <string>
#include "staff.h"

class Admin : public Staff {
    private:
        std::string generatePassword();
    public:
        bool addStaff(Staff newStaff) {
            static Store store_object = Store::get_instance_of_store();
            Staff *staff = store_object.getStaff();
            
            return true;
        }
        bool removeStaff(Staff staff) {
            static Store store_object = Store::get_instance_of_store();
            Staff *staff = store_object.getStaff();
            
            return true;
        }
};

#endif	/* ADMIN_H */