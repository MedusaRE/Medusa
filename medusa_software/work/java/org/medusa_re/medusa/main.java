/*
 *  Copyright (C) 2022, w212 research. <contact@w212research.com>
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

package org.medusa_re.medusa;

import java.util.Scanner;

public class main {
	public static void main(String[] args) {
		System.out.printf("Is this thing on? 0x%08x\n", 0x41424344);

		long total = 1;

		for (long i = 1; i < 0x1000000; i++) {
			if ((i % total) == 0) {
				total += i;
				System.out.printf("%x %x\n", i, total);
			}
		}

		System.out.printf("total=0x%x\n", total);

		Scanner s = new Scanner(System.in);
		long n = s.nextLong();

		System.out.printf("lol=0x%x (%d)\n", n, n);
	}
}
