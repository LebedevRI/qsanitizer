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
#include "tst_stackitemparserxml.h"
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

    for (const auto &d : StackItemParserXmlTestDataList) {
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
