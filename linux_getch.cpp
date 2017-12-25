/* 
 * File:   linux_getch.cpp
 * Author: Kiner Shah
 *
 * Created on 11 November, 2017, 12:10 PM
 */

#include "linux_getch.h"
#include <termios.h>
#include <unistd.h>
#include <cstdio>

static struct termios old_settings, new_settings;

void initializeTerminalIOS(int echo_mode) {
    /* 
     * First, we get the old settings and initialize the new settings with it.
     * Then, we disable the buffer mode to avoid buffering of input.
     * Then, we set the echo mode according to the argument passed.
     * Then, we set the new settings.
     */
    tcgetattr(0, &old_settings);
    new_settings = old_settings;
    
//    new_settings.c_lflag &= ~ICANON;
//    new_settings.c_lflag &= echo_mode ? ECHO : ~ECHO;
    new_settings.c_lflag &= ~(ICANON | ECHO | ECHOE);
    tcsetattr(0, TCSANOW, &new_settings);
}

void resetTerminalIOS() {
    /* Reset the settings using old_settings */
    tcsetattr(0, TCSANOW, &old_settings);
}

char linux_getch(int echo) {
    /*
     * First, we initialize the Terminal IOS by calling initializeTermIOS().
     * Then, we call the getchar() method which will take one character from stdin.
     * Then, we reset the Terminal IOS settings by calling resetTermIOS().
     */
    char c;
    /*
     * echo = 1     For buffered mode
     * echo = 0     For non-buffered mode
     */
    initializeTerminalIOS(echo);
    c = getchar();
    resetTerminalIOS();
    return c;
}