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

#include <cstddef>

#include <QString>
#include <QtTest>
#include <QList>

#include "../../leakitem.h"

class LeakItemTest : public QObject
{
    Q_OBJECT

public:
    LeakItemTest();

private Q_SLOTS:
    void testCase1();
    void testCase1_data();
};

LeakItemTest::LeakItemTest() {}

void LeakItemTest::testCase1()
{
    QFETCH(QString, data);
    QFETCH(bool, directLeak);
    QFETCH(ulong, leakSize);
    QFETCH(ulong, leakCount);

    LeakItem *li = new LeakItem(data);

    QVERIFY(directLeak == li->getLeakType());
    QVERIFY(leakSize == li->getLeakSize());
    QVERIFY(leakCount == li->getLeakCount());

    delete li;
}

void LeakItemTest::testCase1_data()
{
    QTest::addColumn<QString>("data");
    QTest::addColumn<bool>("directLeak");
    QTest::addColumn<std::size_t>("leakSize");
    QTest::addColumn<std::size_t>("leakCount");

    QTest::newRow("0")
        << "Indirect leak of 7856832 byte(s) in 12 object(s) allocated from:"
        << false << 7856832ul << 12ul;
    QTest::newRow("1")
        << "Direct leak of 273600 byte(s) in 43 object(s) allocated from:"
        << true << 273600ul << 43ul;
    QTest::newRow("2")
        << "Indirect leak of 654354 byte(s) in 1 object(s) allocated from:"
        << false << 654354ul << 1ul;
    QTest::newRow("3")
        << "Direct leak of 8978765 byte(s) in 1 object(s) allocated from:"
        << true << 8978765ul << 1ul;
    QTest::newRow("4")
        << "Indirect leak of 1 byte(s) in 12 object(s) allocated from:" << false
        << 1ul << 12ul;
    QTest::newRow("5")
        << "Direct leak of 1 byte(s) in 43 object(s) allocated from:" << true
        << 1ul << 43ul;
    QTest::newRow("6")
        << "Indirect leak of 1 byte(s) in 1 object(s) allocated from:" << false
        << 1ul << 1ul;
    QTest::newRow("7")
        << "Direct leak of 1 byte(s) in 1 object(s) allocated from:" << true
        << 1ul << 1ul;
}

QTEST_APPLESS_MAIN(LeakItemTest)

#include "tst_leakitemtest.moc"
