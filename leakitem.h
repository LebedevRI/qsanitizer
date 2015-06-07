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

#ifndef LEAKITEM_H
#define LEAKITEM_H

#include <QList>

#include "stackitem.h"

class LeakItem
{
public:
    LeakItem(const QString &string);
    bool getLeakType();
    ulong getLeakSize();
    ulong getLeakCount();

private:
    bool directLeak; // true - Direct leak; false - Indirect leak
    ulong leakSize;  // bytes leaked
    ulong leakCount; // objects leaked
    QList<StackItem *> leakAllocationStack;
};

#endif // LEAKITEM_H
