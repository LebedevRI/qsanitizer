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
    this->string = string.trimmed();

    QStringList substrings = this->string.split(" ");

    QString strnum = substrings.first();
    this->num = strnum.remove(0, 1).toULong();
    substrings.removeFirst();

    bool ok;

    this->pointer = substrings.first().toULongLong(&ok, 16);
    substrings.removeFirst();

    if (substrings.isEmpty())
        return;

    QString last = substrings.last();
    if (last.at(0) == '(' && last.at(last.length() - 1) == ')') {
        // got object name + offset
        QString object = last;
        object.remove(0, 1);
        object.remove(object.length() - 1, 1);

        QStringList objectparts = object.split("+");
        this->object = objectparts.at(0);
        this->objectoffset = objectparts.at(1).toULongLong(&ok, 16);
    } else {
        // got source filename and line number!
        QStringList srcfileinfo = last.split(":");
        this->sourcefile = srcfileinfo.at(0);
        this->sourcefileline = srcfileinfo.at(1).toULong();
    }
    substrings.removeLast();

    if (substrings.empty())
        return;

    substrings.removeFirst();

    this->function = substrings.join(" ");
}

StackItem::~StackItem() {}

const QString &StackItem::getString() const { return this->string; }

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
