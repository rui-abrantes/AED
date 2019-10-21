/******************************************************************************
 *
 * File Name: filesys.h
 *	      (c) 2019 AED
 * Author:    Luis Miguel SIlveira & AED Team
 * Revision:  15 Oct 2019
 *
 * NAME
 *     filesys.h - implementation library for easy_iNode filesystem
 *
 * SYNOPSIS
 *     #include <stdio.h>
 *     #include <stdlib.h>
 *
 * DESCRIPTION
 *
 *
 * DIAGNOSTICS
 *
 *****************************************************************************/


#ifndef _FILESYS_H
#define _FILESYS_H

#include <stdio.h>
#include <stdlib.h>


int filesysInit(int);
int filesysLoadFile(char, int*);
int filesysDeleteFile(char);
int filesysClear();
int filesysFree();
int filesysPrint();

#endif
