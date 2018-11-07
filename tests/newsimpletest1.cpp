/* 
 * File:   newsimpletest1.cpp
 * Author: Kiner Shah
 *
 * Created on 22 Sep, 2018, 6:45:03 PM
 */

#include <stdlib.h>
#include <iostream>
#include <unistd.h>

/*
 * Simple C++ Test Suite
 */
static int gl_arr[101];
static int disp_size = 10;
void fillArray() {
    for(int i = 0; i < 101; i++)
        gl_arr[i] = i;
}
void printConsole(bool prev = false, bool next = true, int disp_sc_no = 0, char c = 'n') {
    sleep(3);
    for(int i = disp_sc_no; i < disp_sc_no + disp_size; i++)
        std::cout << gl_arr[i] << std::endl;
    //std::cout << "Enter n for Next, p for Previous: ";
//    char c;
//    std::cin >> c;
    if(c == 'p' && prev) {
        if(disp_sc_no - disp_size == 0)
            printConsole(false, true, disp_sc_no - disp_size, c);
        else if(disp_sc_no - disp_size < 0)
            std::cout << "%TEST_FAILED% time=0 testname=printConsole (newsimpletest1) message=screen index out of bounds" << std::endl;
        else
            printConsole(true, true, disp_sc_no - disp_size, c);
    }
    else if(c == 'n' && next) {
        if(disp_sc_no + disp_size == 100)
            printConsole(true, false, disp_sc_no + disp_size, c);
        else if(disp_sc_no + disp_size > 100)
            std::cout << "%TEST_FAILED% time=0 testname=printConsole (newsimpletest1) message=screen index out of bounds" << std::endl;
        else
            printConsole(true, true, disp_sc_no + disp_size, c);
    }
    else if(c == 'n') {
        c = 'p';
        printConsole(true, false, disp_sc_no - disp_size, c);
    }
}

int main(int argc, char** argv) {
    fillArray();
    std::cout << "%SUITE_STARTING% newsimpletest1" << std::endl;
    std::cout << "%SUITE_STARTED%" << std::endl;

    std::cout << "%TEST_STARTED% test1 (newsimpletest1)" << std::endl;
    printConsole();
    std::cout << "%TEST_FINISHED% time=0 test1 (newsimpletest1)" << std::endl;

    std::cout << "%SUITE_FINISHED% time=0" << std::endl;

    return (EXIT_SUCCESS);
}

