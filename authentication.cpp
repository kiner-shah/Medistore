/* 
 * File:   authentication.cpp
 * Author: Kiner Shah
 *
 * Created on 17 December, 2017, 1:02 PM
 */

#include "authentication.h"
//#define __AUTH_DEBUG__
extern void display_in_center_row(int row_center);
extern void clear_console();
extern int row_center;
extern int column_center;
/*
bool authenticate_customer() {
    
//      1. Get customer credentials
//      2. Compute hash
//      3. Match computed hash and the hash in the storage
//      4. If matched, return true, else return false
    struct winsize win;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &win);         // Input-Output Control (ioctl): TIOCGWINSZ (Terminal I/O Control Get Window Size)
    int row_center = win.ws_row / 2;
    int column_center = win.ws_col / 2;
    int no_of_spaces = column_center - 20;
    display_in_center_row(row_center);
    for(int i = 0; i < no_of_spaces; i++) std::cout<<" ";
    std::string name, password;
    std::cout << "Enter your name: "; std::cin >> name;
    std::cin.ignore();
    for(int i = 0; i < no_of_spaces; i++) std::cout<<" ";
    std::cout << "Enter your password: "; 
    while(1) {
        char c;
        if((c = linux_getch(0)) == '\n') break;
        if(c == 0x08) {  // Backspace
            if(password.length() > 0) {
                printf("\b \b");
                password.pop_back();
                continue;
            }
        }
        else {
            password += c; c = '\\'; // Overwriting char as well
            printf("*");
        }
    }
#ifdef __AUTH_DEBUG__
    std::cout << password << std::endl;
#endif    
    std::string pass_hash = compute_hash(password);
    password = "#$%^&*m*m1L0x0x0x"; // Overwriting password to junk
#ifdef __AUTH_DEBUG__    
    std::cout << std::endl << pass_hash << std::endl;
#endif    
    return true;
}
*/
/*
 * Function that authenticates a particular staff member of the store
 * @return  the position of staff member in vector if successful, else -1
 */
int authenticate_staff() {
    /*
     * 1. Get staff credentials
     * 2. Compute hash
     * 3. Match computed hash and the hash in the storage
     * 4. If matched, return true, else return false
     */
    clear_console();
    int no_of_spaces = column_center - 10;
    display_in_center_row(row_center);
    for(int i = 0; i < no_of_spaces; i++) std::cout<<" ";
    std::cout << "\033[0;32mStaff Login\n\033[0m";
    for(int i = 0; i < no_of_spaces; i++) std::cout<<" ";
    std::string name, password;
    std::cout << "Enter your name: "; std::cin >> name;
    std::cin.ignore();
    for(int i = 0; i < no_of_spaces; i++) std::cout<<" ";
    std::cout << "Enter your password: ";
    while(1) {
        char c;
        if((c = linux_getch(0)) == '\n') break;
        if(c == 127 || c == 8) {
            if(password.length() > 0) {
                std::cout << "\b \b";
                password.pop_back();
            }
        }
        else if(c != '\t') {
            password += c; c = '\\'; // Overwriting char as well
            std::cout << "*";
        }
    }
#ifdef __AUTH_DEBUG__
    std::cout << password << std::endl;
#endif  
    std::string pass_hash = compute_hash(password);
    password = "#$%^&*m*m1L0x0x0x"; // Overwriting password to junk
#ifdef __AUTH_DEBUG__    
    std::cout << std::endl << pass_hash << std::endl;
#endif
    static Store* store_instance = Store::get_instance_of_store();
    std::vector<Staff*> staff = store_instance->getStaff();
    if(staff.empty()) return false;
    size_t staff_sz = staff.size();
    bool found = false;
    unsigned int pos = 0;
    for(unsigned int i = 0; i < staff_sz; i++) {
        std::string sname = staff[i]->getName();
        std::string spass = staff[i]->getPasswordHash();
        if(sname == name && spass == pass_hash) {
            pos = i;
            found = true;
            break;
        }
    }
    if(found) return pos;
    else return -1;
}
/*
 * Function to compute SHA-512 hash of the string
 * @param pass  the string to be hashed
 * @return      the hash string
 */
std::string compute_hash(std::string string_to_be_hashed) {
    // Call SHA512
    return computeSHA512(string_to_be_hashed);
}