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
#include <QStringList>

#include "leakitem.h"

LeakItem::LeakItem(const QString &string)
{
    QStringList substrings = string.split(" ");

    if (substrings.at(0) == QString("Direct"))
        this->directLeak = true;
    else if (substrings.at(0) == QString("Indirect"))
        this->directLeak = false;

    this->leakSize = substrings.at(3).toULong();
    this->leakCount = substrings.at(6).toULong();
}

bool LeakItem::getLeakType() { return this->directLeak; }

std::size_t LeakItem::getLeakSize() { return this->leakSize; }

std::size_t LeakItem::getLeakCount() { return this->leakCount; }
