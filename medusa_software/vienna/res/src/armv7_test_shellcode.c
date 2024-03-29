/*
 *  Copyright (C) 2023, w212 research. <contact@w212research.com>
 *
 *  This program is free software; you can redistribute it and/or modify it
 *  under the terms of version 2 of the GNU General Public License as
 *  published by the Free Software Foundation.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License along
 *  with this program; if not, write to the Free Software Foundation, Inc.,
 *  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

typedef unsigned int uint32_t;

#define EXAMPLE()                                   \
	do {                                            \
		uint32_t *p		  = (uint32_t *)0x41414141; \
		uint32_t *p2_addr = &p[0x41];               \
                                                    \
		if (*p || *p2_addr) {                       \
			return;                                 \
		} else {                                    \
			*p += *p2_addr;                         \
		}                                           \
	} while (0)

#define EXAMPLE4X() \
	do {            \
		EXAMPLE();  \
		EXAMPLE();  \
		EXAMPLE();  \
		EXAMPLE();  \
	} while (0)

#define EXAMPLE4X4X() \
	do {              \
		EXAMPLE4X();  \
		EXAMPLE4X();  \
		EXAMPLE4X();  \
		EXAMPLE4X();  \
	} while (0)

#define EXAMPLE4X4X4X() \
	do {                \
		EXAMPLE4X4X();  \
		EXAMPLE4X4X();  \
		EXAMPLE4X4X();  \
		EXAMPLE4X4X();  \
	} while (0)

#define EXAMPLE4X4X4X4X() \
	do {                  \
		EXAMPLE4X4X4X();  \
		EXAMPLE4X4X4X();  \
		EXAMPLE4X4X4X();  \
		EXAMPLE4X4X4X();  \
	} while (0)

#define EXAMPLE4X4X4X4X4X() \
	do {                    \
		EXAMPLE4X4X4X4X();  \
		EXAMPLE4X4X4X4X();  \
		EXAMPLE4X4X4X4X();  \
		EXAMPLE4X4X4X4X();  \
	} while (0)

/*
 *  work in progress bullshit
 */
void entry() {
	EXAMPLE();
	void func2();
	func2();
}

void func2() {
	void (*ptr)(void) = (void (*)(void))0x41414141;
	ptr();
}