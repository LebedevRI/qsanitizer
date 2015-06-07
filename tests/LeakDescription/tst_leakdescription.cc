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

#include "leakdescription.h"
#include "tst_leakdescription.h"

class LeakDescriptionTest : public QObject
{
    Q_OBJECT

public:
    LeakDescriptionTest();

private Q_SLOTS:
    void testCase1_data();
    void testCase1();
};

LeakDescriptionTest::LeakDescriptionTest() {}

void LeakDescriptionTest::testCase1_data()
{
    QTest::addColumn<QString>("data");
    QTest::addColumn<bool>("directLeak");
    QTest::addColumn<std::size_t>("leakSize");
    QTest::addColumn<std::size_t>("leakCount");

    static const auto maxnum = std::numeric_limits<std::size_t>::max();

    QList<LeakDescriptionTestData> dataList = {
        {.data
         = QString(
               "Indirect leak of %1 byte(s) in %2 object(s) allocated from:")
               .arg(maxnum)
               .arg(maxnum),
         .directLeak = false,
         .leakSize = maxnum,
         .leakCount = maxnum},
        {.data
         = QString("Direct leak of %1 byte(s) in %2 object(s) allocated from:")
               .arg(maxnum)
               .arg(maxnum),
         .directLeak = true,
         .leakSize = maxnum,
         .leakCount = maxnum},
        {.data
         = "Indirect leak of 7856832 byte(s) in 12 object(s) allocated from:",
         .directLeak = false,
         .leakSize = 7856832ul,
         .leakCount = 12ul},
        {.data
         = "Direct leak of 273600 byte(s) in 43 object(s) allocated from:",
         .directLeak = true,
         .leakSize = 273600ul,
         .leakCount = 43ul},
        {.data
         = "Indirect leak of 654354 byte(s) in 1 object(s) allocated from:",
         .directLeak = false,
         .leakSize = 654354ul,
         .leakCount = 1ul},
        {.data
         = "Direct leak of 8978765 byte(s) in 1 object(s) allocated from:",
         .directLeak = true,
         .leakSize = 8978765ul,
         .leakCount = 1ul},
        {.data = "Indirect leak of 1 byte(s) in 12 object(s) allocated from:",
         .directLeak = false,
         .leakSize = 1ul,
         .leakCount = 12ul},
        {.data = "Direct leak of 1 byte(s) in 43 object(s) allocated from:",
         .directLeak = true,
         .leakSize = 1ul,
         .leakCount = 43ul},
        {.data = "Indirect leak of 1 byte(s) in 1 object(s) allocated from:",
         .directLeak = false,
         .leakSize = 1ul,
         .leakCount = 1ul},
        {.data = "Direct leak of 1 byte(s) in 1 object(s) allocated from:",
         .directLeak = true,
         .leakSize = 1ul,
         .leakCount = 1ul}};

    for (const auto &d : dataList) {
        QTest::newRow(d.data.toStdString().c_str())
            << d.data << d.directLeak << d.leakSize << d.leakCount;
    }
}

void LeakDescriptionTest::testCase1()
{
    QFETCH(QString, data);
    QFETCH(bool, directLeak);
    QFETCH(std::size_t, leakSize);
    QFETCH(std::size_t, leakCount);

    LeakDescription *li = new LeakDescription(data);

    QVERIFY(directLeak == li->getLeakType());
    QVERIFY(leakSize == li->getLeakSize());
    QVERIFY(leakCount == li->getLeakCount());

    delete li;
}

QTEST_APPLESS_MAIN(LeakDescriptionTest)

#include "tst_leakdescription.moc"
