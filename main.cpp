/* 
 * File:   main.cpp
 * Author: Kiner Shah
 *
 * Created on 3 November, 2017, 9:00 PM
 */
/*
 * Expected functionalities:
 * 1. Authentication of Staff and Customer.
 * 2. Generation of Bill
 * 3. Storing of transactions and history.
 * 4. Data analysis by staff.
 */
#include "includes.h"
using namespace std;

/* Global variables */


/* Function to clear console window */
void clear_console() {
    #ifdef _WIN32
        system("cls");
    #else
        system("tput reset");               // https://askubuntu.com/a/25079
    #endif    
}
/* Function to display spaces for centering message row wise 
 * @param row_center    the number of times newline have to be printed
 */
void display_in_center_row(int row_center) {
    for(int i = 0; i < row_center - 2; i++) cout << endl;
}
/* Function to display spaces for centering message column wise 
 * @param no_of_spaces  the number of times spaces have to be printed
 */
void display_in_center_column(int no_of_spaces) {
    for(int i = 0; i < no_of_spaces; i++) cout << " ";
}
/* Function to return the arrow key pressed */
string get_arrow_key_pressed() {
    string key_pressed = "DEFAULT";
    /* Up key: \033[A   Down key: \033[B    Right key: \033[C   Left key: \033[D */
    if(linux_getch(0) == '\033') {
        char ignore = linux_getch(0);
        switch(linux_getch(0)) {
            case 'A':   key_pressed = "UP"; break;
            case 'B':   key_pressed = "DOWN"; break;
            case 'C':   key_pressed = "RIGHT"; break;
            case 'D':   key_pressed = "LEFT"; break;
            default:    key_pressed = "DEFAULT"; break;
        }
    }
    return key_pressed;
}
/* Function to display menu 
 * @param ops               current option value
 * @param menu_options      list of strings indicating the available options
 * @param menu_list_size    list size of the above list
 * @param row_center        the number of times newline have to be printed
 * @param column_center     the number of times spaces have to be printed
 */
void display_menu(int ops, string menu_options[], int menu_list_size, int spaces, int row_center, int column_center) {
    /* Displaying initial menu to the user */
    display_in_center_row(row_center - 1);
    int no_of_spaces = column_center - 11;
    display_in_center_column(no_of_spaces); cout << "\033[1mSelect an option below\033[0m" << endl;
    no_of_spaces = column_center - spaces;
    for(int i = 0; i < menu_list_size; i++) {
        display_in_center_column(no_of_spaces); 
        if(i == ops - 1) cout << "\033[7m";
        else cout << "\033[0m";
        cout << menu_options[i] << "\033[0m" << endl;
    }
}
/* Function to change the option flags to toggle the selected item
 * @param ops           current option value
 * @param max_index     maximum index value in the option list
 * @param up_down       flag to indicate up / down action. 1 means up and 0 means down.
 */
void change_option_flags_menu(int &ops, int max_index, int up_down) {
    if(up_down == 1) {
        if(ops == 1) { /* Already at the first option, can't do anything */ }
        else ops--;
    }
    else if(up_down == 0) {
        if(ops == max_index) { /* Already at the last option, can't do anything */ }
        else ops++;
    }
}
/* Function to set up the flags and variables when customer selects an option 
 * @param menu_options     the index specifying the option in the option list
 * @param menu_list        the options labels
 * @param row_center       the row center of the console window
 * @param column_center    the column center of the console window
 */
void menu_selection(int &menu_options, string menu_list[], int menu_list_size, int spaces, int row_center, int column_center) {
    while(1) {
        string key_pressed = get_arrow_key_pressed();
        if(key_pressed == "UP") {
            change_option_flags_menu(menu_options, menu_list_size, 1);
            clear_console();
            display_menu(menu_options, menu_list, menu_list_size, spaces, row_center - 1, column_center);
//            cout << initial_menu_option1 << " " << initial_menu_option2 << " " << initial_menu_option3 << endl;
        }
        else if(key_pressed == "DOWN") {
            change_option_flags_menu(menu_options, menu_list_size, 0);
            clear_console();
            display_menu(menu_options, menu_list, menu_list_size, spaces, row_center - 1, column_center);
//            cout << initial_menu_option1 << " " << initial_menu_option2 << " " << initial_menu_option3 << endl;
        }
        else if(key_pressed == "DEFAULT") { break; }
    }
}
/* Main function */
int main() {
    /* Aligning the starting message to be exactly in the center of console window */
    struct winsize win;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &win);         // Input-Output Control (ioctl): TIOCGWINSZ (Terminal I/O Control Get Window Size)
    int row_center = win.ws_row / 2;
    int column_center = win.ws_col / 2;
    int no_of_spaces = column_center - 8;           // strlen(Welcome to Medistore) = 17. 17 / 2 = 8.
    display_in_center_row(row_center);
    for(int i = 0; i < no_of_spaces; i++) cout<<" ";
    cout << "\033[1;32mWelcome to Medistore\033[0m";
    no_of_spaces = column_center - 12;
    cout<<endl;
    for(int i = 0; i < no_of_spaces + 1; i++) cout<<" ";
    cout << "\033[1;33m[Press Enter to Continue]\033[0m";
    cin.ignore();
    clear_console();
    
    /* Starting Store by getting its instance */
    static Store store_object = Store::get_instance_of_store();
    int initial_menu_options = 1;
    int customer_menu_options = 1;
    int staff_menu_options = 1;
    string initial_menu_list[3] = {" Customer ", " Staff    ", " Exit     "};
    string customer_menu_list[4] = {" Purchase items    ", " View balance      ", " View transactions "," Back              "}; 
//    cout << initial_menu_option1 << " " << initial_menu_option2 << " " << initial_menu_option3 << endl;
    while(1) {
        display_menu(initial_menu_options, initial_menu_list, 3, 5, row_center - 1, column_center);
        menu_selection(initial_menu_options, initial_menu_list, 3, 5, row_center, column_center);
        int mode_selected_initial_menu = initial_menu_options;
        /* User selected Customer */
        if(mode_selected_initial_menu == 1) {
            clear_console();
            /*-------------------------------------------------------------------------------------*/
            /*################################## LOGIN LOGIC ######################################*/
            int count_customer_login_attempts = 0;
            while(!authenticate_customer()) { 
                count_customer_login_attempts++; 
                if(count_customer_login_attempts >= 3) break;
                cout << "\n\033[1;31mCredentials didn't match, try again!\033[0m" << endl;
            }
            if(count_customer_login_attempts >= 3) {
                cout << "\n\033[1;31mSorry, you don't seem to have valid credentials try login after sometime\033[0m" << endl;
                sleep(5);
                exit(0);
            }
            else {
                cout << "\n\033[1;32mSuccessfully logged in..Opening menu\033[0m" << endl;
                sleep(3);
                clear_console();
            /*-------------------------------------------------------------------------------------*/
                display_menu(customer_menu_options, customer_menu_list, 4, 9, row_center - 1, column_center);
                menu_selection(customer_menu_options, customer_menu_list, 4, 9, row_center, column_center);
                int mode_selected_customer_menu = customer_menu_options;
                if(mode_selected_customer_menu == 1) {

                }
                else if(mode_selected_customer_menu == 2) {

                }
                else if(mode_selected_customer_menu == 3) {

                }
                else if(mode_selected_customer_menu == 4) {
                    clear_console();
                }
            }
        }
        /* User selected Staff */
        else if(mode_selected_initial_menu == 2) {
    //        display_menu(staff_menu_options, 10, row_center - 1, column_center);
        }
        /* User selected Exit */
        else if(mode_selected_initial_menu == 3) {
            exit(0);
        }
    }
    return 0;
}