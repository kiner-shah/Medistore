/* 
 * File:   admin.h
 * Author: user
 *
 * Created on 10 February, 2018, 4:12 PM
 */

#ifndef ADMIN_H
#define	ADMIN_H
#include <string>
class Admin {
    private:
        std::string generatePassword();
    public:
        bool addStaff(Staff newStaff);
        bool removeStaff(Staff staff);
};

#endif	/* ADMIN_H */

