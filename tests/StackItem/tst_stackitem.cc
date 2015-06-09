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

#include <QtGlobal>
#include <QString>
#include <QtTest>

#include "stackitem.h"
#include "tst_stackitem.h"

class StackItemTest : public QObject
{
    Q_OBJECT

public:
    StackItemTest();

private Q_SLOTS:
    void testCase1_data();
    void testCase1();
};

StackItemTest::StackItemTest() {}

void StackItemTest::testCase1_data()
{
    QTest::addColumn<QString>("data");

    QTest::addColumn<std::size_t>("num");
    QTest::addColumn<quintptr>("pointer");
    QTest::addColumn<QString>("function");
    QTest::addColumn<QString>("sourcefile");
    QTest::addColumn<std::size_t>("sourcefileline");
    QTest::addColumn<QString>("object");
    QTest::addColumn<quintptr>("objectoffset");

    QList<StackItemTestData> dataList
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
            .objectoffset = quintptr(0x38e2c)}};

    for (const auto &d : dataList) {
        QTest::newRow(d.data.toStdString().c_str())
            << d.data << d.num << d.pointer << d.function << d.sourcefile
            << d.sourcefileline << d.object << d.objectoffset;
    }
}

void StackItemTest::testCase1()
{
    QFETCH(QString, data);
    QFETCH(std::size_t, num);
    QFETCH(quintptr, pointer);
    QFETCH(QString, function);
    QFETCH(QString, sourcefile);
    QFETCH(std::size_t, sourcefileline);
    QFETCH(QString, object);
    QFETCH(quintptr, objectoffset);

    StackItem *si = new StackItem(data);

    QVERIFY(data == si->getString());
    QVERIFY(num == si->getStackItemNum());
    QVERIFY(pointer == si->getPointer());
    QVERIFY(function == si->getFunction());
    QVERIFY(sourcefile == si->getSourceFile());
    QVERIFY(sourcefileline == si->getSourceFileLine());
    QVERIFY(object == si->getObject());
    QVERIFY(objectoffset == si->getObjectOffset());

    delete si;
}

QTEST_APPLESS_MAIN(StackItemTest)

#include "tst_stackitem.moc"
