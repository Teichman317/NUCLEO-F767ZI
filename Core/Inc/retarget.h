/*
 * retarget.h
 *
 *  Created on: Jun 17, 2025
 *      Author: dteichman
 */

#ifndef __RETARGET_H__
#define __RETARGET_H__

#include <stdio.h>

int _write(int file, char *ptr, int len);
extern int kbdIndex;

#endif /* __RETARGET_H__ */
