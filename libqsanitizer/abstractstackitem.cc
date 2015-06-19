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

#include "abstractstackitem.h"

AbstractStackItem::AbstractStackItem()
    : string(), num(0ul), pointer(quintptr(0x0)), function(QString("")),
      sourcefile(QString("")), sourcefileline(0ul), object(QString("")),
      objectoffset(quintptr(0x0))
{
}

AbstractStackItem::~AbstractStackItem() {}

const QString &AbstractStackItem::getString() const { return this->string; }

std::size_t AbstractStackItem::getStackItemNum() const { return this->num; }

quintptr AbstractStackItem::getPointer() const { return this->pointer; }

const QString &AbstractStackItem::getFunction() const { return this->function; }

const QString &AbstractStackItem::getSourceFile() const
{
    return this->sourcefile;
}

std::size_t AbstractStackItem::getSourceFileLine() const
{
    return this->sourcefileline;
}

const QString &AbstractStackItem::getObject() const { return this->object; }

quintptr AbstractStackItem::getObjectOffset() const
{
    return this->objectoffset;
}
