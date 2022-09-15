/*
 *  Copyright (C) 2022, w212 research. <contact@w212research.com>
 *
 *  This program is free software; you can redistribute it and/or modify it
 *  under the terms of version 2 of the GNU General public static License as
 *  published by the Free Software Foundation.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General public static License for more details.
 *
 *  You should have received a copy of the GNU General public static License along
 *  with this program; if not, write to the Free Software Foundation, Inc.,
 *  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

package org.medusa_re.medusa;

import java.util.Map;

public class MedusaStyleJava {
	/*
	 *  Medusa Style Java
	 */

	public MedusaStyleJava() {
		return;
	}

	public static int printf(String format, Object... args) {
		System.out.printf(format, args);

		return 0;
	}

	public static double time() {
		return System.currentTimeMillis() / 1000.0;
	}

	public static Map<String, String> getenv() {
		return System.getenv();
	}

	public static String getenv(String name) {
		return System.getenv(name);
	}

	public static void exit(int code) {
		System.exit(code);
	}

	public static void test_msj(Object obj) {
		printf("yahtzee %h\n", obj);
	}
}
