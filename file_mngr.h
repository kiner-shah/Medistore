/* 
 * File:   filelocking.h
 * Author: Kiner Shah
 *
 * Created on 30 June, 2018, 8:03 PM
 */

#ifndef FILEMNGR_H
#define	FILEMNGR_H
#include <iostream>
#include <cstring>
typedef enum FileOpenModes {
    READ_FILE = 0,
    WRITE_FILE = 1
} file_open_modes;

class FileMngr {
    private:
        struct flock lock; // file lock structure
    public:
        int file_des;   // file descriptor
        char file_name[1024];    // file name
        FileMngr(std::string fname, int mode) {
            memset(file_name, '\0', sizeof(file_name));
            strcpy(file_name, fname.c_str());
            if((file_des = openFile(file_name, (file_open_modes) mode)) == -1) {
                std::cerr << "ERROR: FileMngr(): open file " << file_name << " failed\n";
            }
        }
        ~FileMngr() {
            if(closeFile() == false) {
                std::cerr << "ERROR: ~FileMngr(): close file " << file_name << " failed\n";
            }
        }
        int openFile(char* fname, file_open_modes mode);
        bool closeFile();
        int acquireRLock();
        int acquireWLock();
};

#endif	/* FILEMNGR_H */

