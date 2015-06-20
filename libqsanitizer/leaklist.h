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

#ifndef LEAKLIST_H
#define LEAKLIST_H

#include <QList>
#include <QMap>
#include <QStringList>

#include "leakitem.h"

class LeakList : public QList<LeakItem>
{
public:
    LeakList();
    LeakList(const QStringList &strings);
    ~LeakList();

    QMap<QString, int> getObjectsMap() const;
};

#endif // LEAKLIST_H
