#!/bin/bash
#
#  Copyright (C) 2022, w212 research. <contact@w212research.com>
#
#  This program is free software; you can redistribute it and/or modify it
#  under the terms of version 2 of the GNU General Public License as
#  published by the Free Software Foundation.
#
#  This program is distributed in the hope that it will be useful,
#  but WITHOUT ANY WARRANTY; without even the implied warranty of
#  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#  GNU General Public License for more details.
#
#  You should have received a copy of the GNU General Public License along
#  with this program; if not, write to the Free Software Foundation, Inc.,
#  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
#

if [ $(id -u) != 0 ]; then
    echo "error: this program must be run as root."
    exit -1
fi

pacman -S git gtkmm3 gtk3 glade gimp texlive-most python3 python-pillow node npm doxygen cmake cloc gtksourceviewmm
npm install badgen

git submodule init
git submodule update