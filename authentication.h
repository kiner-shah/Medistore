/* 
 * File:   authentication.h
 * Author: Kiner Shah
 *
 * Created on 17 December, 2017, 1:02 PM
 */

#ifndef AUTHENTICATION_H
#define	AUTHENTICATION_H

#include "linux_getch.h"
#include "sha512.h"
#include "store.h"
#include <iostream>
#include <string>
#include <unistd.h>
#include <sys/ioctl.h>

//bool authenticate_customer();
int authenticate_staff();
std::string compute_hash(std::string);

#endif	/* AUTHENTICATION_H */