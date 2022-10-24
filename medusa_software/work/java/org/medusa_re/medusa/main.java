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

import static org.medusa_re.medusa.MedusaStyleJava.*;
import org.medusa_re.medusa.Stuff;
import java.util.Scanner;

public class main {
	public static void msj_test_2() {
		printf("--------------------------------------------------------------------------------\n");
		printf("Hello, world!\n");

		String env_name = "HOME";

		printf("getenv(%s) = %s\n", env_name, getenv(env_name));
	}

	public static void main(String[] args) {
		MedusaStyleJava m = new MedusaStyleJava();

		printf("is this thing on? %d %d %s\n", 0, 1, "Hello, world!");

		printf("%f\n", time());
		printf("%s %s %s\n", getenv("USER"), getenv("PATH"), getenv("SHELL"));

		test_msj(m);

		msj_test_2();

		exit(69);
	}
}
