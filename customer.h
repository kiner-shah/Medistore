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

class Customer {
private:
    long *bill_nos;
    unsigned int no_of_bill_nos;
    std::string cAddress;
    std::string cName;
    std::string cGender;
    
public:
    Customer(std::string name, std::string gender, std::string address, unsigned int count) : cAddress(address), 
            cName(name), cGender(gender), bill_nos(NULL), no_of_bill_nos(count) {
    }
    ~Customer() {
        if(bill_nos != NULL) {
            delete[] bill_nos;
            bill_nos = NULL;
        }
        no_of_bill_nos = 0;
    }
    std::string getName() { return cName; }
    std::string getGender() { return cGender; }
    std::string getAddress() { return cAddress; }
    void setBillNos(long *list) { bill_nos = list; }
    void purchaseItems();
    void checkTransactions();
};

#endif	/* CUSTOMER_H */