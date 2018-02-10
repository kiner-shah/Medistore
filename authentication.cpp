/* 
 * File:   authentication.cpp
 * Author: Kiner Shah
 *
 * Created on 17 December, 2017, 1:02 PM
 */

#include "authentication.h"
//#define __AUTH_DEBUG__
extern void display_in_center_row(int row_center);
bool authenticate_customer() {
    /*
     * 1. Get customer credentials
     * 2. Compute hash
     * 3. Match computed hash and the hash in the storage
     * 4. If matched, return true, else return false
     */
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

bool authenticate_staff() {
    /*
     * 1. Get staff credentials
     * 2. Compute hash
     * 3. Match computed hash and the hash in the storage
     * 4. If matched, return true, else return false
     */
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
        if(c == '\b') {
            if(password.length() > 0) {
                //std::cout << "\b \b";
                password.pop_back();
            }
        }
        else {
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
    return true;
}

std::string compute_hash(std::string pass) {
    // Call SHA512
    return computeSHA512(pass);
}