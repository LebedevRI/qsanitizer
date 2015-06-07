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

#include <QtGlobal>
#include <QString>
#include <QStringList>

#include "stackitem.h"

StackItem::StackItem(const QString &string)
    : num(0), pointer(quintptr(NULL)), function(""), sourcefile(""),
      sourcefileline(0), object(""), objectoffset(quintptr(NULL))
{
    QStringList substrings = string.trimmed().split(" ");

    int i = 0;

    QString strnum = substrings.at(i);
    this->num = strnum.remove(0, 1).toULong();

    i++;

    bool ok;
    this->pointer = substrings.at(i).toULongLong(&ok, 16);

    if (substrings.size() < 3)
        return;

    i++;

    if (substrings.size() < 4)
        goto later;

    i++;

    this->function = substrings.at(i);

    i++;

later:

    if (substrings.at(i).at(0) == '('
        && substrings.at(i).at(substrings.at(i).length() - 1) == ')') {
        // got object name + offset
        QString object = substrings.at(i);
        object.remove(0, 1);
        object.remove(object.length() - 1, 1);

        QStringList objectparts = object.split("+");
        this->object = objectparts.at(0);
        this->objectoffset = objectparts.at(1).toULongLong(&ok, 16);
    } else {
        // got source filename and line number!
        QStringList srcfileinfo = substrings.at(i).split(":");
        this->sourcefile = srcfileinfo.at(0);
        this->sourcefileline = srcfileinfo.at(1).toULong();
    }

    if (substrings.size() < 6)
        return;
}

StackItem::~StackItem() {}

std::size_t StackItem::getStackItemNum() const { return this->num; }

quintptr StackItem::getPointer() const { return this->pointer; }

const QString &StackItem::getFunction() const { return this->function; }

const QString &StackItem::getSourceFile() const { return this->sourcefile; }

std::size_t StackItem::getSourceFileLine() const
{
    return this->sourcefileline;
}

const QString &StackItem::getObject() const { return this->object; }

quintptr StackItem::getObjectOffset() const { return this->objectoffset; }
