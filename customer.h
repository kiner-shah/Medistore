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

typedef struct STRUCT_TRANSID_BILLNO {
    int transactionID;
    int billNo;
} transIdBillNoPair;

class Customer {
private:
    float cBalance;
    transIdBillNoPair *trans_id_bill_no_pair;
    std::string cAddress;
    std::string cName;
    std::string cGender;
    
public:
    void purchaseItems();
    void checkBalance();
    void checkTransactions();
};

#endif	/* CUSTOMER_H */