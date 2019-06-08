/* 
 * File:   customer.h
 * Author: Kiner Shah
 *
 * Created on 22 November, 2017, 9:22 PM
 */

#ifndef CUSTOMER_H
#define	CUSTOMER_H

#include <string>
#include <vector>
#include <cstdlib>
#include <sstream>

class Customer {
public:
    Customer(std::string name, std::string date, long bill_no) : bill_no(bill_no), cName(name), bill_date_str(date) {
        std::stringstream ss;
        int day, mon, year;
        char separator;
        ss >> day >> separator >> mon >> separator >> year;
        bill_date.tm_year = year - 1900;
        bill_date.tm_mon = mon - 1;
        bill_date.tm_mday = day;
    }
    
    std::string getName() { return cName; }
    long getBillNo() { return bill_no; }
    std::string getBillDate() { return bill_date_str; }
    void purchaseItems();
    void checkTransactions();
    std::string to_string() {
        std::ostringstream os;
        os << cName << ',' << bill_date_str << ',' << bill_no;
        return os.str();
    }
    
private:
    struct tm bill_date;
    long bill_no;
    std::string cName;
    std::string bill_date_str;
    
};

#endif	/* CUSTOMER_H */