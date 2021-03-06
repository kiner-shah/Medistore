/* 
 * File:   store.cpp
 * Author: Kiner Shah
 *
 * Created on 3 November, 2017, 9:20 PM
 */

#include <sys/_default_fcntl.h>

#include "store.h"
#include <algorithm>
#include <sstream>
//#include <cassert>
Store* Store::instance = NULL;
Bill* Store::generate_bill(std::map<std::string, int> items_qty_map, long bill_no, std::string doctor_name, float total) {
    size_t map_sz = items_qty_map.size();
    Bill* new_bill = new BILL(bill_no, doctor_name, map_sz, total);
    new_bill->item_id_list = new std::string[map_sz];
    new_bill->item_qty = new unsigned int[map_sz];
    int i = 0;
    for (std::pair<std::string, int> p : items_qty_map) {
        new_bill->item_id_list[i] = p.first;
        new_bill->item_qty[i] = p.second;
        i++;
    }
    return new_bill;
}
void Store::addNewBill(Bill* bill) {
    for (unsigned int i = 0; i < bill->item_id_no; i++) {
        Item* it = NULL;
        for (unsigned int j = 0; j < totalItems; j++) {
            it = items[j];
            if (it->item_id == bill->item_id_list[i]) break;
        }
        if (it != NULL) {
            it->item_stock -= bill->item_qty[i];
        }
    }
    bills.push_back(bill);
    totalBills++;
}
Customer* Store::generate_customer(std::string name, long bill_no) {
    struct tm* t;
    time_t cur_time = time(NULL);
    t = localtime(&cur_time);
    int year = t->tm_year + 1900;
    int mon = t->tm_mon + 1;
    int day = t->tm_mday;
    std::ostringstream os;
    os << std::setfill('0') << std::setw(2) << day << '-' << 
        std::setfill('0') << std::setw(2) << mon << '-' << year;
    
    Customer* cust = new Customer(name, os.str(), bill_no);
    return cust;
}
void Store::addNewCustomer(Customer* customer) {
    customers.push_back(customer);
    totalCustomers++;
}
// TODO
void Store::display_items() {
    std::cout << "Items list" << std::endl;
}

// TODO
bool Store::modify_stock() {
    return true;
}

//bool Store::validate_customer() {
//    return authenticate_customer();
//}

/**
 * Function which validates staff member
 * @return Validation result
 */
int Store::validate_staff() {
    return authenticate_staff();
}

/**
 * Function that loads customer data
 * @return Boolean value indicating load success / failure
 */
bool Store::loadCustomerData() {
    customer_data = new FileMngr("customer_data.bin", READ_WRITE_FILE);
    if(customer_data->file_des == -1) return false;
    while (customer_data->acquireRLock() == -1) { ; }
    // File format: CustomerName,DateDDMMYYYY,BillNo
    ssize_t bytes = 0;
    int total_bytes = -1;
    unsigned int BUF_SIZE = 128;
    char buf[BUF_SIZE], ch;
    std::string line = "";
    memset(buf, '\0', sizeof(buf));
    while(true) {
        bytes = read(customer_data->file_des, &ch, 1);
        if(bytes == -1) {
            if(errno == EINTR) continue;
            else return false;
        }
        else if(bytes == 0) {
            if(total_bytes == -1) return true;
            else {
                // Create structure and break
                line += buf;
                std::istringstream iss(line);
                std::string token;
                std::vector<std::string> tokens;
                while(getline(iss, token, ',')) {
                    tokens.push_back(token);
                }
//                std::cout << "Tokens: " << tokens.size() << std::endl;
                if(tokens.size() > 0) {
                    Customer *temp = new Customer(tokens[0], tokens[1], std::stol(tokens[2]));
                    customers.push_back(temp);
//                    std::cout << temp->getName() << " " << temp->getBillDate() << " " << temp->getBillNo() << std::endl;
                    totalCustomers++;
                }
                break;
            }
        }
        else {
            total_bytes += bytes;
            if(total_bytes >= BUF_SIZE - 2) {
                line += buf;
                total_bytes = 0;
                memset(buf, '\0', BUF_SIZE);
                buf[total_bytes] = ch;
            }
            else buf[total_bytes] = ch;
            if(ch == '\n') {
                // Create structure
                line += buf;
                std::istringstream iss(line);
                std::string token;
                std::vector<std::string> tokens;
                while(getline(iss, token, ',')) {
                    tokens.push_back(token);
                }
//                std::cout << "Tokens: " << tokens.size() << std::endl;
                line = ""; total_bytes = -1;
                memset(buf, '\0', BUF_SIZE);
                if(tokens.size() > 0) {
                    Customer *temp = new Customer(tokens[0], tokens[1], std::stol(tokens[2]));
//                    std::cout << temp->getName() << " " << temp->getBillDate() << " " << temp->getBillNo() << std::endl;
                    customers.push_back(temp);
                    totalCustomers++;
                }
            }
        }
//        std::cout << "Total bytes: " << total_bytes << " Buf: " << buf << std::endl;
    }
//    std::cout << "Total customers = " << totalCustomers << std::endl;
    return true;
}
/**
 * Function that unloads customer data
 * @return unload success / failure
 */
bool Store::unloadCustomerData() {
    while (customer_data->acquireWLock() == -1) { ; }  
    
    if (lseek(customer_data->file_des, 0, SEEK_SET) == -1) {
        std::cout << "ERROR lseek(): " << strerror(errno) << "(" << errno << ")\n";
    }
    
    for(unsigned int i = 0; i < totalCustomers; i++) {
        Customer* cust = customers[i];
        std::string cust_str = cust->to_string();
        cust_str += '\n';
        if (write(customer_data->file_des, cust_str.c_str(), sizeof(char) * cust_str.size()) == -1) {
            std::cout << "ERROR write(): " << strerror(errno) << "(" << errno << ")\n";
        }
        if (cust != NULL) {
            delete cust;
            cust = NULL;
        }
//        assert(customers[i] == NULL);
    }
    customers.clear();
//    assert(customers.empty());
    totalCustomers = 0;
    customer_data->closeFile();
    return true;
}

/**
 * Function that loads staff data
 * @return Boolean value indicating load success / failure
 */
bool Store::loadStaffData() {
    staff_data = new FileMngr("staff_data.bin", READ_FILE);
    if(staff_data->file_des == -1) return false;
    while (staff_data->acquireRLock() == -1) { ; }
    // File format: StaffID,StaffName,StaffGender,StaffAddress,StaffAge,StaffPassword
    ssize_t bytes = 0;
    int total_bytes = -1;
    unsigned int BUF_SIZE = 128;
    char buf[BUF_SIZE], ch;
    std::string line = "";
    memset(buf, '\0', sizeof(buf));
    while(true) {
        bytes = read(staff_data->file_des, &ch, 1);
        if(bytes == -1) {
            if(errno == EINTR) continue;
            else return false;
        }
        else if(bytes == 0) {
            if(total_bytes == -1) return true;
            else {
                // Create structure and break
                line += buf;
                std::istringstream iss(line);
                std::string token;
                std::vector<std::string> tokens;
                while(getline(iss, token, ',')) {
                    tokens.push_back(token);
                }
//                std::cout << "Tokens: " << tokens.size() << std::endl;
                if(tokens.size() > 0) {
                    int staff_age;
                    std::stringstream ss;
                    ss << tokens[4];
                    ss >> staff_age;
                    tokens[5] = tokens[5].substr(0, tokens[5].find_last_not_of("\n"));
                    Staff *temp = new Staff(tokens[1], tokens[0], tokens[2], tokens[3], staff_age, tokens[5]);
                    staff.push_back(temp);
//                    std::cout << temp->getName() << " " << temp->getAddress() << " " << temp->getGender() << std::endl;
                    totalStaff++;
                }
            }
        }
        else {
            total_bytes += bytes;
            if(total_bytes >= BUF_SIZE - 2) {
                line += buf;
                total_bytes = 0;
                memset(buf, '\0', BUF_SIZE);
                buf[total_bytes] = ch;
            }
            else buf[total_bytes] = ch;
            if(ch == '\n') {
                // Create structure
                line += buf;
                std::istringstream iss(line);
                std::string token;
                std::vector<std::string> tokens;
                while(getline(iss, token, ',')) {
                    tokens.push_back(token);
                }
//                std::cout << "Tokens: " << tokens.size() << std::endl;
                line = ""; total_bytes = -1;
                memset(buf, '\0', BUF_SIZE);
                if(tokens.size() > 0) {
                    int staff_age;
                    std::stringstream ss;
                    ss << tokens[4];
                    ss >> staff_age;
                    tokens[5] = tokens[5].substr(0, tokens[5].find_last_not_of("\n"));
                    Staff *temp = new Staff(tokens[1], tokens[0], tokens[2], tokens[3], staff_age, tokens[5]);
                    staff.push_back(temp);
//                    std::cout << temp->getName() << " " << temp->getAddress() << " " << temp->getPasswordHash() << std::endl;
                    totalStaff++;
                }
            }
        }
//        std::cout << "Total bytes: " << total_bytes << " Buf: " << buf << " " << strlen(buf) << std::endl;
    }
//    std::cout << "Total staff = " << totalStaff << std::endl;
    return true;
}
/**
 * Function that unloads staff data
 * @return unload success / failure
 */
bool Store::unloadStaffData() {
    for(unsigned int i = 0; i < totalStaff; i++) {
        delete staff[i];
        staff[i] = NULL;
//        assert(staff[i] == NULL);
    }
    staff.clear();
//    assert(staff.empty());
    totalStaff = 0;
    staff_data->closeFile();
    return true;
}
/**
 * Function that loads items data
 * @return Boolean value indicating load success / failure
 */
bool Store::loadItemsData() {
    items_data = new FileMngr("items_data.bin", READ_WRITE_FILE);
    if(items_data->file_des == -1) return false;
    while (items_data->acquireRLock() == -1) { ; }
    // File format: ItemID,ItemName,ItemStock,ItemPrice,ItemExpiry(yyyy-mm-dd)
    ssize_t bytes = 0;
    int total_bytes = -1;
    unsigned int BUF_SIZE = 128;
    char buf[BUF_SIZE], ch;
    std::string line = "";
    memset(buf, '\0', sizeof(buf));
    while(true) {
        bytes = read(items_data->file_des, &ch, 1);
        if(bytes == -1) {
            if(errno == EINTR) continue;
            else return false;
        }
        else if(bytes == 0) {
            if(total_bytes == -1) return true;
            else {
                // Create structure and break
                line += buf;
                std::istringstream iss(line);
                std::string token;
                std::vector<std::string> tokens;
                while(getline(iss, token, ',')) {
                    tokens.push_back(token);
                }
//                std::cout << "Tokens: " << tokens.size() << std::endl;
                if(tokens.size() > 0) {
                    tokens[4] = tokens[4].substr(0, tokens[4].find_last_not_of('\n'));
                    Item *temp = new Item(tokens[0], tokens[1], stoi(tokens[2]), stof(tokens[3]), tokens[4]);
                    items.push_back(temp);
//                    std::cout << temp->getName() << " " << temp->getAddress() << " " << temp->getGender() << std::endl;
                    totalItems++;
                }
            }
        }
        else {
            total_bytes += bytes;
            if(total_bytes >= BUF_SIZE - 2) {
                line += buf;
                total_bytes = 0;
                memset(buf, '\0', BUF_SIZE);
                buf[total_bytes] = ch;
            }
            else buf[total_bytes] = ch;
            if(ch == '\n') {
                // Create structure
                line += buf;
                std::istringstream iss(line);
                std::string token;
                std::vector<std::string> tokens;
                while(getline(iss, token, ',')) {
                    tokens.push_back(token);
                }
//                std::cout << "Tokens: " << tokens.size() << std::endl;
                line = ""; total_bytes = -1;
                memset(buf, '\0', BUF_SIZE);
                if(tokens.size() > 0) {
                    tokens[4] = tokens[4].substr(0, tokens[4].find_last_not_of('\n'));
                    Item *temp = new Item(tokens[0], tokens[1], stoi(tokens[2]), stof(tokens[3]), tokens[4]);
                    items.push_back(temp);
//                    std::cout << temp->getName() << " " << temp->getAddress() << " " << temp->getGender() << std::endl;
                    totalItems++;
                }
            }
        }
//        std::cout << "Total bytes: " << total_bytes << " Buf: " << buf << std::endl;
    }
    return true;
}
/**
 * Function that unloads items data
 * @return unload success / failure
 */
bool Store::unloadItemsData() {
    while (items_data->acquireWLock() == -1) { ; }  
        
    if (lseek(items_data->file_des, 0, SEEK_SET) == -1) {
        std::cout << "ERROR lseek(): " << strerror(errno) << "(" << errno << ")\n";
    }
    
    for(unsigned int i = 0; i < totalItems; i++) {
        Item* item = items[i];
        std::string item_str = item->to_string();
        item_str += '\n';
        if (write(items_data->file_des, item_str.c_str(), sizeof(char) * item_str.size()) == -1) {
            std::cout << "ERROR write(): " << strerror(errno) << "(" << errno << ")\n";
        }
        if (item != NULL) {
            delete item;
            item = NULL;
        }
//        assert(staff[i] == NULL);
    }
    items.clear();
//    assert(staff.empty());
    totalItems = 0;
    items_data->closeFile();
    return true;
}
/**
 * Function that loads bill data
 * @return Boolean value indicating load success / failure
 */
bool Store::loadBillData() {
    bill_data = new FileMngr("bill_data.bin", READ_WRITE_FILE);
    if(bill_data->file_des == -1) return false;
    while (bill_data->acquireRLock() == -1) { ; }
    // File format: BillID,ItemID,ItemQty,ItemID,ItemQty,...,Total
    ssize_t bytes = 0;
    int total_bytes = -1;
    unsigned int BUF_SIZE = 128;
    char buf[BUF_SIZE], ch;
    std::string line = "";
    memset(buf, '\0', sizeof(buf));
    while(true) {
        bytes = read(bill_data->file_des, &ch, 1);
        if(bytes == -1) {
            if(errno == EINTR) continue;
            else return false;
        }
        else if(bytes == 0) {
            if(total_bytes == -1) return true;
            else {
                // Create structure and break
                line += buf;
                std::istringstream iss(line);
                std::string token;
                std::vector<std::string> tokens;
                while(getline(iss, token, ',')) {
                    tokens.push_back(token);
                }
//                std::cout << "Tokens: " << tokens.size() << std::endl;
                if(tokens.size() > 0) {
//                    tokens[4] = tokens[4].substr(0, tokens[4].find_last_not_of('\n'));
                    unsigned int items_no = stoi(tokens[2]);
                    std::string *item_ids = new std::string[items_no];
                    unsigned int *qty = new unsigned int[items_no];
                    for(unsigned int k = 0, j = 0; k < 2 * items_no; j++, k += 2) {
                        item_ids[j] = tokens[3 + k];
                        qty[j] = stoi(tokens[3 + k + 1]);
                    }
                    Bill *temp = new Bill(stol(tokens[0]), tokens[1], items_no, stof(tokens[3 + 2 * items_no]));
                    temp->item_id_list = item_ids;
                    temp->item_qty = qty;
                    
                    bills.push_back(temp);
//                    std::cout << temp->getName() << " " << temp->getAddress() << " " << temp->getGender() << std::endl;
                    totalBills++;
                }
            }
        }
        else {
            total_bytes += bytes;
            if(total_bytes >= BUF_SIZE - 2) {
                line += buf;
                total_bytes = 0;
                memset(buf, '\0', BUF_SIZE);
                buf[total_bytes] = ch;
            }
            else buf[total_bytes] = ch;
            if(ch == '\n') {
                // Create structure
                line += buf;
                std::istringstream iss(line);
                std::string token;
                std::vector<std::string> tokens;
                while(getline(iss, token, ',')) {
                    tokens.push_back(token);
                }
//                std::cout << "Tokens: " << tokens.size() << std::endl;
                line = ""; total_bytes = -1;
                memset(buf, '\0', BUF_SIZE);
//                std::cout << "Tokens: " << tokens.size() << std::endl;
                if(tokens.size() > 0) {
//                    tokens[4] = tokens[4].substr(0, tokens[4].find_last_not_of('\n'));
                    unsigned int items_no = stoi(tokens[2]);
                    std::string *item_ids = new std::string[items_no];
                    unsigned int *qty = new unsigned int[items_no];
                    for(unsigned int k = 0, j = 0; k < 2 * items_no; j++, k += 2) {
                        item_ids[j] = tokens[3 + k];
                        qty[j] = stoi(tokens[3 + k + 1]);
                    }
                    Bill *temp = new Bill(stol(tokens[0]), tokens[1], items_no, stof(tokens[3 + 2 * items_no]));
                    temp->item_id_list = item_ids;
                    temp->item_qty = qty;
                    
                    bills.push_back(temp);
//                    std::cout << temp->getName() << " " << temp->getAddress() << " " << temp->getGender() << std::endl;
                    totalBills++;
                }
            }
        }
//        std::cout << "Total bytes: " << total_bytes << " Buf: " << buf << std::endl;
    }
    return true;
}
/**
 * Function that unloads bill data
 * @return unload success / failure
 */
bool Store::unloadBillData() {
    while (bill_data->acquireWLock() == -1) { ; }  
    
    if (lseek(bill_data->file_des, 0, SEEK_SET) == -1) {
        std::cout << "ERROR lseek(): " << strerror(errno) << "(" << errno << ")\n";
    }
    
    for(unsigned int i = 0; i < totalBills; i++) {
        Bill* b = bills[i];
        std::string bill_str = b->to_string();
        bill_str += '\n';
        if (write(bill_data->file_des, bill_str.c_str(), sizeof(char) * bill_str.size()) == -1) {
            std::cout << "ERROR write(): " << strerror(errno) << "(" << errno << ")\n";
        }
        
        if (b != NULL) {
            delete b;
            b = NULL;
        }
//        assert(staff[i] == NULL);
    }
    bills.clear();
//    assert(staff.empty());
    totalBills = 0;
    bill_data->closeFile();
    return true;
}