/*************************************************************************\
*                  Copyright (C) Michael Kerrisk, 2010.                   *
*                                                                         *
* This program is free software. You may use, modify, and redistribute it *
* under the terms of the GNU Affero General Public License as published   *
* by the Free Software Foundation, either version 3 or (at your option)   *
* any later version. This program is distributed without any warranty.    *
* See the file COPYING.agpl-v3 for details.                               *
\*************************************************************************/

/* Supplementary program for Chapter 48 */

#include <sys/types.h>
#include <sys/shm.h>
#include "tlpi_hdr.h"

int
main(int argc, char *argv[])
{
    int j;

    if (argc > 1 && strcmp(argv[1], "--help") == 0)
        usageErr("%s [shmid...]\n", argv[0]);

    for (j = 1; j < argc; j++)
        if (shmctl(getInt(argv[j], 0, "shmid"), IPC_RMID, NULL) == -1)
            errExit("shmctl %s", argv[j]);

    exit(EXIT_SUCCESS);
}
