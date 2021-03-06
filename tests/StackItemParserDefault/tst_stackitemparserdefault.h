/*
 * QSanitizer - Qt5 ui for *Sanitizer output
 * Copyright (C) 2015  Roman Lebedev
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef TST_STACKITEMPARSERDEFAULT
#define TST_STACKITEMPARSERDEFAULT

#include "tst_stackitem.h"

static const QList<StackItemTestData> StackItemParserDefaultTestDataList
    = {{.data = "#14 0x7f037c02fa91 in dt_gui_preferences_show "
                "/home/lebedevri/darktable/src/gui/preferences.c:257",
        .num = 14ul,
        .pointer = quintptr(0x7f037c02fa91),
        .function = "dt_gui_preferences_show",
        .sourcefile = "/home/lebedevri/darktable/src/gui/preferences.c",
        .sourcefileline = 257ul,
        .object = "",
        .objectoffset = quintptr(NULL)},
       {.data = "#15 0x7f03525aa67d",
        .num = 15ul,
        .pointer = quintptr(0x7f03525aa67d),
        .function = "",
        .sourcefile = "",
        .sourcefileline = 0ul,
        .object = "",
        .objectoffset = quintptr(NULL)},
       {.data = "#5 0x7f037b724748 in gtk_tree_model_get "
                "(/usr/lib/x86_64-linux-gnu/libgtk-3.so.0+0x2e4748)",
        .num = 5ul,
        .pointer = quintptr(0x7f037b724748),
        .function = "gtk_tree_model_get",
        .sourcefile = "",
        .sourcefileline = 0ul,
        .object = "/usr/lib/x86_64-linux-gnu/libgtk-3.so.0",
        .objectoffset = quintptr(0x2e4748)},
       {.data = "#3 0x7f0379b80e2c "
                "(/usr/lib/x86_64-linux-gnu/libgobject-2.0.so.0+0x38e2c)",
        .num = 3ul,
        .pointer = quintptr(0x7f0379b80e2c),
        .function = "",
        .sourcefile = "",
        .sourcefileline = 0ul,
        .object = "/usr/lib/x86_64-linux-gnu/libgobject-2.0.so.0",
        .objectoffset = quintptr(0x38e2c)},
       {.data = "#2 0x7f035401220a in "
                "Oxygen::QtSettings::isAtomSupported(std::string const&) "
                "const "
                "(/usr/lib/x86_64-linux-gnu/gtk-3.0/3.0.0/theming-engines/"
                "liboxygen-gtk.so+0xaa20a)",
        .num = 2ul,
        .pointer = quintptr(0x7f035401220a),
        .function
        = "Oxygen::QtSettings::isAtomSupported(std::string const&) const",
        .sourcefile = "",
        .sourcefileline = 0ul,
        .object = "/usr/lib/x86_64-linux-gnu/gtk-3.0/3.0.0/theming-engines/"
                  "liboxygen-gtk.so",
        .objectoffset = quintptr(0xaa20a)}};

#endif // TST_STACKITEMPARSERDEFAULT
