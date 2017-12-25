/* 
 * File:   authentication.h
 * Author: Kiner Shah
 *
 * Created on 17 December, 2017, 1:02 PM
 */

#ifndef AUTHENTICATION_H
#define	AUTHENTICATION_H

#include "customer.h"
#include "staff.h"
#include "linux_getch.h"
#include "sha512.h"
#include <iostream>
#include <string>
#include <unistd.h>

bool authenticate_customer();
bool authenticate_staff();
std::string compute_hash(std::string);

#endif	/* AUTHENTICATION_H */