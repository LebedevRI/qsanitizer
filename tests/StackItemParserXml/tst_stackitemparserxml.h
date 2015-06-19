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

#ifndef TST_STACKITEMPARSERXML
#define TST_STACKITEMPARSERXML

#include "tst_stackitem.h"

QList<StackItemTestData> StackItemParserXmlTestDataList
    = {{.data = "<frame><n>14</n></frame>", .num = 14ul},
       {.data = "<frame><p>0x7fd041ffb018</p></frame>",
        .pointer = quintptr(0x7fd041ffb018)},
       {.data = "<frame><m>/usr/local/bin/../lib/darktable/"
                "libdarktable.so</m></frame>",
        .object = "/usr/local/bin/../lib/darktable/libdarktable.so"},
       {.data = "<frame><o>0x12b018</o></frame>",
        .objectoffset = quintptr(0x12b018)},
       {.data = "<frame><f>dt_legacy_presets_create</f></frame>",
        .function = "dt_legacy_presets_create"},
       {.data = "<frame><s>/home/lebedevri/darktable/src/gui/"
                "legacy_presets.h</s></frame>",
        .sourcefile = "/home/lebedevri/darktable/src/gui/legacy_presets.h"},
       {.data = "<frame><l>1126</l></frame>", .sourcefileline = 1126ul},
       {.data = "<frame><n>14</n><p>0x7fd041ffb018</p><m>/usr/local/bin/../"
                "lib/darktable/libdarktable.so</m><o>0x12b018</"
                "o><f>dt_legacy_presets_create</f><q>0x0</q><s>/home/"
                "lebedevri/darktable/src/gui/legacy_presets.h</s><l>1126</"
                "l><c>0</c><F>in "
                "dt_legacy_presets_create</F><S>/home/lebedevri/darktable/"
                "src/gui/legacy_presets.h:1126</S><L>/home/lebedevri/"
                "darktable/src/gui/legacy_presets.h:1126</"
                "L><M>(libdarktable.so+0x00000012b018)</M></frame>",
        .num = 14ul,
        .pointer = quintptr(0x7fd041ffb018),
        .object = "/usr/local/bin/../lib/darktable/libdarktable.so",
        .objectoffset = quintptr(0x12b018),
        .function = "dt_legacy_presets_create",
        .sourcefile = "/home/lebedevri/darktable/src/gui/legacy_presets.h",
        .sourcefileline = 1126ul}};

#endif // TST_STACKITEMPARSERXML
