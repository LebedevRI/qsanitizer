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

#ifndef STACKITEM_H
#define STACKITEM_H

#include <QtGlobal>
#include <QString>

class StackItem
{
public:
    StackItem(const QString &string);
    ~StackItem();

    const QString &getString() const;
    std::size_t getStackItemNum() const;
    quintptr getPointer() const;
    const QString &getFunction() const;
    const QString &getSourceFile() const;
    std::size_t getSourceFileLine() const;
    const QString &getObject() const;
    quintptr getObjectOffset() const;

private:
    QString string;
    std::size_t num;
    quintptr pointer;
    QString function;
    QString sourcefile;
    std::size_t sourcefileline;
    QString object;
    quintptr objectoffset; // if symbol was not symbolised into
                           // sourcefile,sourcefileline
};

#endif // STACKITEM_H
