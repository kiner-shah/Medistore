/* 
 * File:   main.cpp
 * Author: Kiner Shah
 *
 * Created on 3 November, 2017, 9:00 PM
 */
/*
 * Expected functionalities:
 * 1. Authentication of Staff.  --> done
 * 2. Showing item list (modify / check stock)  --> done
 * 2. Generation of Bill
 * 3. Storing of transactions and history.
 */
#include "includes.h"
using namespace std;

/* Global variables */
bool staff_session_start = false;
int row_center;
int column_center;
Staff *staff_instance = NULL;
const unsigned int item_list_display_size = 10;
/* Function to clear console window */
void clear_console() {
    system("tput reset");               // https://askubuntu.com/a/25079   
}
/** 
 * Function to display spaces for centering message row wise 
 * @param row_center    the number of times newline have to be printed
 */
void display_in_center_row(int row_center) {
    for(int i = 0; i < row_center - 2; i++) cout << endl;
}
/** 
 * Function to display spaces for centering message column wise 
 * @param no_of_spaces  the number of times spaces have to be printed
 */
void display_in_center_column(int no_of_spaces) {
    for(int i = 0; i < no_of_spaces; i++) cout << " ";
}
/** 
 * Function to return the arrow key pressed
 * @return  string indicating the arrow key pressed
 */
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
/** 
 * Function to display menu 
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
/** 
 * Function to change the option flags to toggle the selected item
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
void destroy_objs_and_shutdown() {
    static Store *store_obj = Store::get_instance_of_store();
    cout << "destroy_objs_and_shutdown(): Deleting...\n";
    delete store_obj;
    store_obj = NULL;
    if(store_obj != NULL) { cout << "ERROR: destroy_objs_and_shutdown(): store_obj not NULL after deletion\n"; exit(1); }
    exit(0);
}
/** 
 * Function to set up the flags and variables when customer selects an option 
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
/**
 * @param   a   item to be printed
 */
void printItem(Item* a, bool display_stock_with_color = false) {
    std::cout << setw(11) << 
            a->item_id << setw(20) << 
            a->item_name << setw(11) << 
            a->item_price;
    if (display_stock_with_color) {
        if (staff_instance->check_item_stock(a->item_id))
            std::cout << "\033[1;32m" << setw(11) << a->item_stock << "\033[0m";
        else
            std::cout << "\033[1;31m" << setw(11) << a->item_stock << "\033[0m";
    }
    else
        std::cout << setw(11) << a->item_stock;
    char buf[100] = "NIL";
    if(a->item_expiry.tm_year != 0)
        strftime(buf, sizeof(buf), "%Y-%m-%d", &a->item_expiry);
    std::cout << setw(15) << buf << std::endl;
}
/**
 * @return  item_id to be modified
 */
string display_items_with_modify_privelege() {
    static Store* store_obj = Store::get_instance_of_store();
    vector<Item*> items = store_obj->getItems();
    unsigned int len_items = store_obj->getTotalItems();
    bool prev = false, next = true;
    unsigned int sc_no = 0;
    while (1) {
        clear_console();
        std::cout << setw(11) << 
            "ITEM ID" << setw(20) << 
            "ITEM NAME" << setw(11) << 
            "ITEM PRICE" << setw(11) << 
            "ITEM STOCK" << setw(15) << "ITEM EXP." << std::endl;
        for (unsigned int i = sc_no; i < min(sc_no + item_list_display_size, len_items); i++) {
            printItem(items[i]);
        }
        std::cout << "Enter [p] for previous, [n] for next, [m] to modify [q] to quit" << std::endl;
        char c = linux_getch(1);
        if (c == 'n' && next) {
            if(sc_no + item_list_display_size == len_items - 1) {
                sc_no += item_list_display_size;
                prev = true;
                next = false;
            }
            else if (sc_no + item_list_display_size > len_items - 1) {
                // Do nothing
            }
            else {
                sc_no += item_list_display_size;
                prev = true;
                next = true;
            }
        }
        else if (c == 'p' && prev) {
            if(sc_no - item_list_display_size == 0) {
                sc_no += item_list_display_size;
                prev = false;
                next = true;
            }
            else if(sc_no - item_list_display_size < 0) {
                // Do nothing
            }
            else {
                sc_no -= item_list_display_size;
                prev = true;
                next = true;
            }
        }
        else if (c == 'm')
            break;
        else if (c == 'q')
            return "QUIT_STRING_GO_BACK";
    }
    std::cout << "Enter item ID to modify: ";
    std::string item_id;
    std::cin >> item_id;
    return item_id;
}
void display_items_with_check_stock_privilege() {
    static Store* store_obj = Store::get_instance_of_store();
    vector<Item*> items = store_obj->getItems();
    unsigned int len_items = store_obj->getTotalItems();
    bool prev = false, next = true;
    unsigned int sc_no = 0;
    while (1) {
        clear_console();
        std::cout << setw(11) << 
            "ITEM ID" << setw(20) << 
            "ITEM NAME" << setw(11) << 
            "ITEM PRICE" << setw(11) << 
            "ITEM STOCK" << setw(15) << "ITEM EXP." << std::endl;
        for (unsigned int i = sc_no; i < min(sc_no + item_list_display_size, len_items); i++) {
            printItem(items[i], true);
        }
        std::cout << "Enter [p] for previous, [n] for next, [q] to quit" << std::endl;
        char c = linux_getch(1);
        if (c == 'n' && next) {
            if(sc_no + item_list_display_size == len_items - 1) {
                sc_no += item_list_display_size;
                prev = true;
                next = false;
            }
            else if (sc_no + item_list_display_size > len_items - 1) {
                // Do nothing
            }
            else {
                sc_no += item_list_display_size;
                prev = true;
                next = true;
            }
        }
        else if (c == 'p' && prev) {
            if(sc_no - item_list_display_size == 0) {
                sc_no += item_list_display_size;
                prev = false;
                next = true;
            }
            else if(sc_no - item_list_display_size < 0) {
                // Do nothing
            }
            else {
                sc_no -= item_list_display_size;
                prev = true;
                next = true;
            }
        }
        else if (c == 'q')
            return;
    }   
}
/* Main function */
int main() {
    /* Aligning the starting message to be exactly in the center of console window */
    clear_console();
    struct winsize win;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &win);         // Input-Output Control (ioctl): TIOCGWINSZ (Terminal I/O Control Get Window Size)
    row_center = win.ws_row / 2;
    column_center = win.ws_col / 2;
    int no_of_spaces = column_center - 8;           // strlen(Welcome to Medistore) = 17. 17 / 2 = 8.
    display_in_center_row(row_center);
    for(int i = 0; i < no_of_spaces; i++) cout << " ";
    cout << "\033[1;32mWelcome to Medistore\033[0m";
    no_of_spaces = column_center - 12;
    cout << endl;
    for(int i = 0; i < no_of_spaces + 1; i++) cout << " ";
    cout << "\033[1;33m[Press Enter to Continue]\033[0m";
    cin.ignore();
    clear_console();
    
    /* Starting Store by getting its instance */
    no_of_spaces = column_center - 5;
    for(int i = 0; i < no_of_spaces + 1; i++) cout << " ";
    cout << "Loading ...\n"; cout << endl; clear_console();
    static Store* store_object = Store::get_instance_of_store();
    int initial_menu_options = 1;
    int initial_menu_options_after_login = 1;
    int customer_menu_options = 1;
    int staff_menu_options = 1;
    string initial_menu_list[3] = {" Customer ", " Staff    ", " Exit     "};
    string initial_menu_list_after_login[3] = {" Customer ", " Staff    ", " Logout   "};
    string customer_menu_list[3] = {" Purchase items   ", " View transaction "," Back             "};
    string staff_menu_list[3] = {" Check items stock ", " Modify items      ", " Back              "};
//    cout << initial_menu_option1 << " " << initial_menu_option2 << " " << initial_menu_option3 << endl;
    while(true) {
        int mode_selected_initial_menu;
        if(staff_session_start == false) {
            display_menu(initial_menu_options, initial_menu_list, 3, 5, row_center - 1, column_center);
            menu_selection(initial_menu_options, initial_menu_list, 3, 5, row_center, column_center);
            mode_selected_initial_menu = initial_menu_options;
        }
        else if(staff_session_start == true) {
            display_menu(initial_menu_options_after_login, initial_menu_list_after_login, 3, 5, row_center - 1, column_center);
            menu_selection(initial_menu_options_after_login, initial_menu_list_after_login, 3, 5, row_center, column_center);
            mode_selected_initial_menu = initial_menu_options_after_login;
        }
        /* User selected Customer */
        if(mode_selected_initial_menu == 1) {
            clear_console();
            /*-------------------------------------------------------------------------------------*/
            /*################################## LOGIN LOGIC ######################################*/
            if(staff_session_start == false) {
                int count_staff_login_attempts = 0;
                int staff_pos_vec = -1;
                while((staff_pos_vec = store_object->validate_staff()) == -1) {
                    count_staff_login_attempts++;
                    if(count_staff_login_attempts >= 3) break;
                    cout << "\n";
                    for(int i = 0; i < column_center - 18; i++) cout << " ";
                    cout << "\033[1;31mCredentials didn't match, try again!\033[0m" << endl;
                    sleep(1);
                }
                if(count_staff_login_attempts >= 3) {
                    cout << "\n";
                    for(int i = 0; i < column_center - 34; i++) cout << " ";
                    cout << "\033[1;31mSorry, you don't seem to have valid credentials try login after sometime\033[0m" << endl;
                    sleep(5);
                    exit(0);
                }
                cout << "\n";
                staff_instance = store_object->getStaff()[staff_pos_vec];
                for(int i = 0; i < column_center - 18; i++) cout << " ";
                cout << "\033[1;32mSuccessfully logged in..Opening menu\033[0m" << endl;
                staff_session_start = true;
                sleep(3);
                clear_console();
            }
//            /*-------------------------------------------------------------------------------------*/
            display_menu(customer_menu_options, customer_menu_list, 3, 9, row_center - 1, column_center);
            menu_selection(customer_menu_options, customer_menu_list, 3, 9, row_center, column_center);
            int mode_selected_customer_menu = customer_menu_options;
            if(mode_selected_customer_menu == 1) {
                // Show item list to the customer (in parts of say 10 products): item name, item id, item price
                // only if stock for that item is there.
                // Enter the item ID for the item to purchase, and the quantity
                // Take customer details: name, gender, age, doctor, prescription (y/n)
            }
            else if(mode_selected_customer_menu == 2) {
                
            }
            else if(mode_selected_customer_menu == 3) {
                clear_console();
            }
        }
        /* User selected Staff */
        else if(mode_selected_initial_menu == 2) {
    //        display_menu(staff_menu_options, 10, row_center - 1, column_center);
            clear_console();
            /*################################## LOGIN LOGIC ######################################*/
            // TODO: Add code here
            if(staff_session_start == false) {
                int count_staff_login_attempts = 0;
                int staff_pos_vec = -1;
                while((staff_pos_vec = store_object->validate_staff()) == -1) {
                    count_staff_login_attempts++;
                    if(count_staff_login_attempts >= 3) break;
                    cout << "\n";
                    for(int i = 0; i < column_center - 18; i++) cout << " ";
                    cout << "\033[1;31mCredentials didn't match, try again!\033[0m" << endl;
                    sleep(1);
                }
                if(count_staff_login_attempts >= 3) {
                    cout << "\n";
                    for(int i = 0; i < column_center - 34; i++) cout << " ";
                    cout << "\033[1;31mSorry, you don't seem to have valid credentials try login after sometime\033[0m" << endl;
                    sleep(5);
                    exit(0);
                }
                cout << "\n";
                staff_instance = store_object->getStaff()[staff_pos_vec];
                for(int i = 0; i < column_center - 18; i++) cout << " ";
                cout << "\033[1;32mSuccessfully logged in..Opening menu\033[0m" << endl;
                staff_session_start = true;
                sleep(3);
                clear_console();
            }
            /*################################ LOGIN LOGIC END ####################################*/
            display_menu(staff_menu_options, staff_menu_list, 3, 9, row_center - 1, column_center);
            menu_selection(staff_menu_options, staff_menu_list, 3, 9, row_center, column_center);
            int mode_selected_staff_menu = staff_menu_options;
            if(mode_selected_staff_menu == 1) {     // Check items stock
                display_items_with_check_stock_privilege();
                clear_console();
            }
            else if(mode_selected_staff_menu == 2) {
                string item_id = display_items_with_modify_privelege();
                if (item_id == "QUIT_STRING_GO_BACK") {
                    /* Do nothing */
                }
                else {
                    int choice = DEFAULT_MODE;
                    while(1) {
                        cout << "\n1. MODIFY NAME\n2. MODIFY PRICE\n3. MODIFY STOCK\n4. MODIFY EXPIRY\n5. BACK\nSelect your choice [1-5]:";
                        cin >> choice; cin.ignore();
                        if(!staff_instance->modify_item((ModifyModes) choice, item_id)) {
                            /* Do nothing */
                        }
                        else break;
                    }
                    if (choice != DEFAULT_MODE)
                        cin.ignore();
                    clear_console();
                }
            }
            else if(mode_selected_staff_menu == 3) {
                clear_console();
            }
        }
        /* User selected Exit */
        else if(!staff_session_start && mode_selected_initial_menu == 3) {
            destroy_objs_and_shutdown();
        }
        else if(staff_session_start && mode_selected_initial_menu == 3) {
            staff_session_start = false;
            clear_console();
        }
    }
    return 0;
}