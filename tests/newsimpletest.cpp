/* 
 * File:   newsimpletest.cpp
 * Author: Kiner Shah
 *
 * Created on 30 Jun, 2018, 12:28:49 PM
 */

#include <stdlib.h>
#include <iostream>
#include <sys/file.h>
#include <sys/unistd.h>
#include "file_mngr_test.h"
using namespace std;
/*
 * Simple C++ Test Suite
 */
int acquireRLock(int fd, struct flock &lock) {
    lock.l_len = 0;
    lock.l_start = 0;
    lock.l_whence = SEEK_SET;
    lock.l_type = F_RDLCK;
    struct flock temp_lock = lock;
    fcntl(fd, F_GETLK, &temp_lock);
    if(temp_lock.l_type == F_WRLCK) {
        return -1;
    }
    else {
        int ret_val = fcntl(fd, F_SETLK, &lock);
        if(ret_val == -1) cout << "Failed here errno = " << errno << " fd = " << fd << endl;
        return ret_val;
    }
}
int acquireWLock(int fd, struct flock &lock) {
    lock.l_len = 0;
    lock.l_start = 0;
    lock.l_whence = SEEK_SET;
    lock.l_type = F_WRLCK;
    struct flock temp_lock = lock;
    fcntl(fd, F_GETLK, &temp_lock);
    if(temp_lock.l_type == F_RDLCK || temp_lock.l_type == F_WRLCK)
        return -1;
    else
        return fcntl(fd, F_SETLK, &lock);
}
int FileOpenTest() {
    int fd = open("test_file.txt", O_RDWR);
    if(fd == -1) {
        cout << "%TEST_FAILED% time=0 testname=FileOPenTest (newsimpletest) message=file open failed" << endl;
    }
    return fd;
}
void FileReadLockTest(int fd) {
    struct flock lock;
    if(acquireRLock(fd, lock) < 0) {
        cout << "%TEST_FAILED% time=0 testname=FileReadLockTest (newsimpletest) message=file read lock acquire failed" << endl;
    }
}
void FileWriteLockTest(int fd) {
    struct flock lock;
    if(acquireWLock(fd, lock) < 0) {
        cout << "%TEST_FAILED% time=0 testname=FileWriteLockTest (newsimpletest) message=file write lock acquire failed" << endl;
    }
}
void FileWriteTest(int fd) {
    if(write(fd, (void*) "I am a ball", 13) <= 0) {
        cout << "%TEST_FAILED% time=0 testname=FileWriteTest (newsimpletest) message=file write failed" << endl;
    }
}
void FileCloseTest(int fd) {
    if(close(fd) < 0) {
        cout << "%TEST_FAILED% time=0 testname=FileCloseTest (newsimpletest) message=file close failed" << endl;
    }
}
void FileMngrTest1() {
    FileMngrTest *sample_file = new FileMngrTest("test_file.txt", READ_FILE);
    if(sample_file->file_des == -1) {
        cout << "%TEST_FAILED% time=0 testname=FileMngrTest1 (newsimpletest) message=file manager failed" << endl;
    }
}
int main(int argc, char** argv) {
    std::cout << "%SUITE_STARTING% newsimpletest" << std::endl;
    std::cout << "%SUITE_STARTED%" << std::endl;
    
    std::cout << "%TEST_STARTED% FileOpenTest (newsimpletest)" << std::endl;
    int fd = FileOpenTest();
    std::cout << "%TEST_FINISHED% time=0 FileOpenTest (newsimpletest)" << std::endl;

    std::cout << "%TEST_STARTED% FileReadLockTest (newsimpletest)\n" << std::endl;
    FileReadLockTest(fd);
    std::cout << "%TEST_FINISHED% time=0 FileReadLockTest (newsimpletest)" << std::endl;
   
    std::cout << "%TEST_STARTED% FileCloseTest (newsimpletest)\n" << std::endl;
    FileCloseTest(fd);
    std::cout << "%TEST_FINISHED% time=0 FileCloseTest (newsimpletest)" << std::endl;
    
    std::cout << "%TEST_STARTED% FileOpenTest (newsimpletest)" << std::endl;
    fd = FileOpenTest();
    std::cout << "%TEST_FINISHED% time=0 FileOpenTest (newsimpletest)" << std::endl;
    
    std::cout << "%TEST_STARTED% FileWriteLockTest (newsimpletest)\n" << std::endl;
    FileWriteLockTest(fd);
    std::cout << "%TEST_FINISHED% time=0 FileWriteLockTest (newsimpletest)" << std::endl;
    
    std::cout << "%TEST_STARTED% FileWriteTest (newsimpletest)\n" << std::endl;
    FileWriteTest(fd);
    std::cout << "%TEST_FINISHED% time=0 FileWriteTest (newsimpletest)" << std::endl;
    
    std::cout << "%TEST_STARTED% FileCloseTest (newsimpletest)\n" << std::endl;
    FileCloseTest(fd);
    std::cout << "%TEST_FINISHED% time=0 FileCloseTest (newsimpletest)" << std::endl;
    
    std::cout << "%TEST_STARTED% FileMngrTest1 (newsimpletest)\n" << std::endl;
    FileMngrTest1();
    std::cout << "%TEST_FINISHED% time=0 FileMngrTest1 (newsimpletest)" << std::endl;
    
    std::cout << "%SUITE_FINISHED% time=0" << std::endl;

    return (EXIT_SUCCESS);
}

