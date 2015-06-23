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

#include <QList>
#include <QMap>
#include <QStringList>

#include "leaklist.h"
#include "leakitem.h"

LeakList::LeakList() {}

LeakList::LeakList(const QStringList &strings)
{
    for (const auto &s : strings) {
        if (s.startsWith("Direct leak of")
            || s.startsWith("Indirect leak of")) {
            this->append(LeakItem(s));
        }
    }
}

QMap<QString, int> LeakList::getObjectsMap() const
{
    QMap<QString, int> objects;

    for (const auto &f : *this) {
        auto set = f.getObjectsSet();

        for (const auto &object : set) {
            objects[object]++;
        }
    }

    return objects;
}
