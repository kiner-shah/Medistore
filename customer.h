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
#include <vector>
//typedef struct STRUCT_TRANSID_BILLNO {
//    int transactionID;
//    int billNo;
//} transIdBillNoPair;

typedef std::pair<int, int> transIdBillNoPair;
class Customer {
private:
//    transIdBillNoPair *trans_id_bill_no_pair;
    std::vector<transIdBillNoPair*> trans_id_bill_no_pair;
    unsigned int trans_id_bill_no_p_count;
    std::string cAddress;
    std::string cName;
    std::string cGender;
    
public:
    // TODO: trans_id_bill_no pairs in constructor
    Customer(std::string name, std::string gender, std::string address) : cAddress(address), cName(name), cGender(gender) {
        trans_id_bill_no_p_count = 0;
    }
    std::string getName() { return cName; }
    std::string getGender() { return cGender; }
    std::string getAddress() { return cAddress; }
    void setTransIDPairs();
    void purchaseItems();
    void checkBalance();
    void checkTransactions();
};

#endif	/* CUSTOMER_H */