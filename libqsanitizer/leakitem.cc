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
#include <QStringList>
#include <QSet>

#include "leakitem.h"
#include "stackitem.h"

LeakItem::LeakItem(const QString &string)
{
    QStringList substrings = string.split("\n");

    description = LeakDescription(substrings.first());
    substrings.removeFirst();

    for (const auto &d : substrings) {
        this->allocationStack.append(StackItem(d));
    }
}

QString LeakItem::getString() const
{
    QString Leak = this->description.getString() + "\n";

    for (const auto &s : this->allocationStack) {
        Leak.append("\t" + s.getString() + "\n");
    }

    return Leak;
}

const LeakDescription &LeakItem::getLeakDescription() const
{
    return this->description;
}

const QList<StackItem> &LeakItem::getAllocationStack() const
{
    return this->allocationStack;
}

QSet<QString> LeakItem::getObjectsSet() const
{
    QSet<QString> objects;

    for (const auto &f : this->allocationStack) {
        objects.insert(f.getObject());
    }

    return objects;
}
