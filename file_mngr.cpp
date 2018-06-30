/* 
 * File:   filelocking.h
 * Author: Kiner Shah
 *
 * Created on 30 June, 2018, 8:03 PM
 */

#include "file_mngr.h"
#include <sys/file.h>
#include <sys/unistd.h>
/**
 * @param fname     name of the file to be opened
 * @param mode      mode in which file has to be opened
 * @return  file descriptor
 */
int FileMngr::openFile(char* fname, file_open_modes mode) {
    if(mode == READ_FILE) 
        return open(fname, O_RDONLY);
    else if(mode == WRITE_FILE)
        return open(fname, O_WRONLY);
    return -1;
}
/**
 * @return  close file success / failure
 */
bool FileMngr::closeFile() {
    if(close(file_des) < 0) return false;
    return true;
}
/**
 * @return  read lock success / failure
 */
int FileMngr::acquireRLock() {
    lock.l_len = 0;
    lock.l_start = 0;
    lock.l_whence = SEEK_SET;
    lock.l_type = F_RDLCK;
    struct flock temp_lock = lock;
    fcntl(file_des, F_GETLK, &temp_lock);
    if(temp_lock.l_type == F_WRLCK) {
        return -1;
    }
    else {
        int ret_val = fcntl(file_des, F_SETLK, &lock);
        if(ret_val == -1) std::cerr << __FUNCTION__ << ": Failed here errno = " << errno << " fd = " << file_des << std::endl;
        return ret_val;
    }
}
/**
 * @return  write lock success / failure
 */
int FileMngr::acquireWLock() {
    lock.l_len = 0;
    lock.l_start = 0;
    lock.l_whence = SEEK_SET;
    lock.l_type = F_WRLCK;
    struct flock temp_lock = lock;
    fcntl(file_des, F_GETLK, &temp_lock);
    if(temp_lock.l_type == F_RDLCK || temp_lock.l_type == F_WRLCK)
        return -1;
    else {
        int ret_val = fcntl(file_des, F_SETLK, &lock);
        if(ret_val == -1) std::cerr << __FUNCTION__ << ": Failed here errno = " << errno << " fd = " << file_des << std::endl;
        return ret_val;
    }
}
