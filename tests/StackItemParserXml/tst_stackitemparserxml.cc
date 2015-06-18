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
#include <QtTest>

#include "tst_stackitem.h"
#include "stackitemparserxml.h"

class StackItemParserXmlTest : public QObject
{
    Q_OBJECT

public:
    StackItemParserXmlTest();

private Q_SLOTS:
    void testCase1_data();
    void testCase1();
};

StackItemParserXmlTest::StackItemParserXmlTest() {}

void StackItemParserXmlTest::testCase1_data()
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

    for (const auto &d : dataList) {
        QTest::newRow(d.data.toStdString().c_str())
            << d.data << d.num << d.pointer << d.function << d.sourcefile
            << d.sourcefileline << d.object << d.objectoffset;
    }
}

void StackItemParserXmlTest::testCase1()
{
    QFETCH(QString, data);
    QFETCH(std::size_t, num);
    QFETCH(quintptr, pointer);
    QFETCH(QString, function);
    QFETCH(QString, sourcefile);
    QFETCH(std::size_t, sourcefileline);
    QFETCH(QString, object);
    QFETCH(quintptr, objectoffset);

    StackItemParserXml *si = new StackItemParserXml(data);

    QVERIFY(num == si->getStackItemNum());
    // qDebug() << pointer << si->getPointer();
    QVERIFY(pointer == si->getPointer());
    QVERIFY(function == si->getFunction());
    QVERIFY(sourcefile == si->getSourceFile());
    QVERIFY(sourcefileline == si->getSourceFileLine());
    QVERIFY(object == si->getObject());
    QVERIFY(objectoffset == si->getObjectOffset());

    delete si;
}

QTEST_APPLESS_MAIN(StackItemParserXmlTest)

#include "tst_stackitemparserxml.moc"
