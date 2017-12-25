/* 
 * File:   customer.h
 * Author: Kiner Shah
 *
 * Created on 22 November, 2017, 9:22 PM
 */

#ifndef CUSTOMER_H
#define	CUSTOMER_H

#include "transaction.h"
#include <string>

class Customer {
private:
    std::string cName;
    std::string cSSN;
    std::string cGender;
    struct tm *cDOB;
    std::string cAddress;
    float cBalance;
    Transaction *transactions;
    std::string cPassword;
    
public:
    void purchaseItems();
    void checkBalance();
    void checkTransactions();
};

#endif	/* CUSTOMER_H */