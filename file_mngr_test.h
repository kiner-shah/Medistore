/* 
 * File:   file_mngr_test.h
 * Author: Kiner Shah
 *
 * Created on 30 June, 2018, 9:13 PM
 */

#ifndef FILE_MNGR_TEST_H
#define	FILE_MNGR_TEST_H

#include <iostream>
#include <cstring>
#include <string>
typedef enum FileOpenModesTest {
    READ_FILE = 0,
    WRITE_FILE = 1
} file_open_modes_test;

class FileMngrTest {
    private:
        struct flock lock; // file lock structure
    public:
        int file_des;   // file descriptor
        char file_name[1024];    // file name
        FileMngrTest(std::string fname, int mode) {
            memset(file_name, '\0', sizeof(1024));
            strcpy(file_name, fname.c_str());
            std::cout << "FM: " << file_name << std::endl;
            if((file_des = openFile(file_name, (file_open_modes_test) mode)) == -1) {
                std::cerr << "ERROR: FileMngrTest(): open file " << file_name << " failed\n";
            }
        }
        ~FileMngrTest() {
            if(closeFile() == false) {
                std::cerr << "ERROR: ~FileMngrTest(): close file " << file_name << " failed\n";
            }
        }
        int openFile(char* fname, file_open_modes_test mode);
        bool closeFile();
        int acquireRLock();
        int acquireWLock();
};


#endif	/* FILE_MNGR_TEST_H */

