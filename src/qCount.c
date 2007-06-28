/***************************************************************************
 * qDecoder - Web Application Interface for C/C++    http://www.qDecoder.org
 *
 * Copyright (C) 2007 Seung-young Kim.
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 **************************************************************************/

/**
 * @file qCount.c Counter File Handling API
 *
 * Read/Write/Update counter file like below.
 *
 * @code
 *   ---- number.dat ----
 *   74
 *   --------------------
 * @endcode
 */

#include "qDecoder.h"
#include "qInternal.h"

/**
 * Read counter(integer) from file with advisory file locking.
 *
 * @param filename file path
 *
 * @return	counter value readed from file. in case of failure, returns 0.
 *
 * @note
 * @code
 *   int count;
 *   count = qCountRead("number.dat");
 * @endcode
 */
int qCountRead(char *filename) {
	FILE *fp;
	int  counter;

	if ((fp = qfopen(filename, "r")) == NULL) return 0;
	fscanf(fp, "%d", &counter);
	qfclose(fp);
	return counter;
}

/**
 * Save counter(integer) to file with advisory file locking.
 *
 * @param filename	file path
 * @param number	counter integer value
 *
 * @return	in case of success, returns Q_TRUE. otherwise Q_FALSE.
 *
 * @note
 * @code
 *   qCountSave("number.dat", 75);
 * @endcode
 */
Q_BOOL qCountSave(char *filename, int number) {
	FILE *fp;

	if ((fp = qfopen(filename, "w")) == NULL) return Q_FALSE;
	fprintf(fp, "%d\n", number);
	qfclose(fp);

	return Q_TRUE;
}

/**
 * Increases(or decrease) the counter value as much as specified number
 * with advisory file locking.
 *
 * @param filename	file path
 * @param number	how much increase or decrease
 *
 * @return	updated counter value. in case of failure, returns 0.
 *
 * @note
 * @code
 *   int count;
 *   count = qCountUpdate("number.dat", -3);
 * @endcode
 */
int qCountUpdate(char *filename, int number) {
	FILE *fp;
	int counter = 0;

	if ((fp = qfopen(filename, "r+")) != NULL) {
		fscanf(fp, "%d", &counter);
		fseek(fp, 0, SEEK_SET);
	} else if ((fp = fopen(filename, "w")) == NULL) return 0;
	counter += number;
	fprintf(fp, "%d\n", counter);
	qfclose(fp);
	return counter;
}
