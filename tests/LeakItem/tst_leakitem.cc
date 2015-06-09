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

#include <QString>
#include <QList>
#include <QtTest>

#include "leakdescription.h"
#include "stackitem.h"
#include "leakitem.h"

#include "tst_leakdescription.h"
#include "tst_stackitem.h"

typedef struct {
    QString data;
    LeakDescriptionTestData description;
    QList<StackItemTestData> stack;
} LeakItemTestData;

Q_DECLARE_METATYPE(LeakItemTestData)
Q_DECLARE_METATYPE(QList<StackItemTestData>)

class LeakItemTest : public QObject
{
    Q_OBJECT

public:
    LeakItemTest();

private Q_SLOTS:
    void testCase1_data();
    void testCase1();
};

LeakItemTest::LeakItemTest() {}

void LeakItemTest::testCase1_data()
{
    QTest::addColumn<QString>("data");
    QTest::addColumn<LeakDescriptionTestData>("description");
    QTest::addColumn<QList<StackItemTestData>>("stack");

    QList<LeakItemTestData> dataList = {
        {.data
         = "Direct leak of 1644 byte(s) in 156 object(s) allocated from:\n"
           "    #0 0x7f037c2ec74f in malloc "
           "(/usr/lib/x86_64-linux-gnu/libasan.so.1+0x5474f)\n"
           "    #1 0x7f037b7334da "
           "(/usr/lib/x86_64-linux-gnu/libgtk-3.so.0+0x2f34da)\n"
           "    #2 0x7f037c026e8e in init_tab_accels "
           "/home/lebedevri/darktable/src/gui/preferences.c:510\n"
           "    #3 0x7f037c02fa91 in dt_gui_preferences_show "
           "/home/lebedevri/darktable/src/gui/preferences.c:257\n"
           "    #4 0x7f03525aa67d\n"
           "    #5 0x7f0379b58503 "
           "(/usr/lib/x86_64-linux-gnu/libgobject-2.0.so.0+0x10503)\n"
           "    #6 0x7f036e35d827 in ffi_call "
           "(/usr/lib/x86_64-linux-gnu/libffi.so.6+0x5827)",
         .description
         = {.data
            = "Direct leak of 1644 byte(s) in 156 object(s) allocated from:",
            .directLeak = true,
            .leakSize = 1644ul,
            .leakCount = 156ul},
         .stack
         = {{.data = "#0 0x7f037c2ec74f in malloc "
                     "(/usr/lib/x86_64-linux-gnu/libasan.so.1+0x5474f)",
             .num = 0ul,
             .pointer = quintptr(0x7f037c2ec74f),
             .function = "malloc",
             .sourcefile = "",
             .sourcefileline = 0ul,
             .object = "/usr/lib/x86_64-linux-gnu/libasan.so.1",
             .objectoffset = quintptr(0x5474f)},
            {.data = "#1 0x7f037b7334da "
                     "(/usr/lib/x86_64-linux-gnu/libgtk-3.so.0+0x2f34da)",
             .num = 1ul,
             .pointer = quintptr(0x7f037b7334da),
             .function = "",
             .sourcefile = "",
             .sourcefileline = 0ul,
             .object = "/usr/lib/x86_64-linux-gnu/libgtk-3.so.0",
             .objectoffset = quintptr(0x2f34da)},
            {.data = "#2 0x7f037c026e8e in init_tab_accels "
                     "/home/lebedevri/darktable/src/gui/preferences.c:510",
             .num = 2ul,
             .pointer = quintptr(0x7f037c026e8e),
             .function = "init_tab_accels",
             .sourcefile = "/home/lebedevri/darktable/src/gui/preferences.c",
             .sourcefileline = 510ul,
             .object = "",
             .objectoffset = quintptr(NULL)},
            {.data = "#3 0x7f037c02fa91 in dt_gui_preferences_show "
                     "/home/lebedevri/darktable/src/gui/preferences.c:257",
             .num = 3ul,
             .pointer = quintptr(0x7f037c02fa91),
             .function = "dt_gui_preferences_show",
             .sourcefile = "/home/lebedevri/darktable/src/gui/preferences.c",
             .sourcefileline = 257ul,
             .object = "",
             .objectoffset = quintptr(NULL)},
            {.data = "#4 0x7f03525aa67d",
             .num = 4ul,
             .pointer = quintptr(0x7f03525aa67d),
             .function = "",
             .sourcefile = "",
             .sourcefileline = 0ul,
             .object = "",
             .objectoffset = quintptr(NULL)},
            {.data = "#5 0x7f0379b58503 "
                     "(/usr/lib/x86_64-linux-gnu/libgobject-2.0.so.0+0x10503)",
             .num = 5ul,
             .pointer = quintptr(0x7f0379b58503),
             .function = "",
             .sourcefile = "",
             .sourcefileline = 0ul,
             .object = "/usr/lib/x86_64-linux-gnu/libgobject-2.0.so.0",
             .objectoffset = quintptr(0x10503)},
            {.data = "#6 0x7f036e35d827 in ffi_call "
                     "(/usr/lib/x86_64-linux-gnu/libffi.so.6+0x5827)",
             .num = 6ul,
             .pointer = quintptr(0x7f036e35d827),
             .function = "ffi_call",
             .sourcefile = "",
             .sourcefileline = 0ul,
             .object = "/usr/lib/x86_64-linux-gnu/libffi.so.6",
             .objectoffset = quintptr(0x5827)}}}};

    int i = 0;
    for (const auto &d : dataList) {
        QTest::newRow(QString::number(i).toStdString().c_str())
            << d.data << d.description << d.stack;
        i++;
    }
}

void LeakItemTest::testCase1()
{
    QFETCH(QString, data);
    QFETCH(LeakDescriptionTestData, description);
    QFETCH(QList<StackItemTestData>, stack);

    LeakItem *li = new LeakItem(data);
    LeakDescription ld = li->getLeakDescription();

    QVERIFY(description.data == ld.getString());
    QVERIFY(description.directLeak == ld.getLeakType());
    QVERIFY(description.leakSize == ld.getLeakSize());
    QVERIFY(description.leakCount == ld.getLeakCount());

    QVERIFY(stack.size() == li->getAllocationStack().size());

    const auto stackSize = stack.size();
    for (auto i = 0; i < stackSize; ++i) {
        auto entryLocal = stack.at(i);
        auto entryParsed = li->getAllocationStack().at(i);

        QVERIFY(entryLocal.data == entryParsed.getString());
        QVERIFY(entryLocal.num == entryParsed.getStackItemNum());
        QVERIFY(entryLocal.pointer == entryParsed.getPointer());
        QVERIFY(entryLocal.function == entryParsed.getFunction());
        QVERIFY(entryLocal.sourcefile == entryParsed.getSourceFile());
        QVERIFY(entryLocal.sourcefileline == entryParsed.getSourceFileLine());
        QVERIFY(entryLocal.object == entryParsed.getObject());
        QVERIFY(entryLocal.objectoffset == entryParsed.getObjectOffset());
    }

    delete li;
}

QTEST_APPLESS_MAIN(LeakItemTest)

#include "tst_leakitem.moc"
