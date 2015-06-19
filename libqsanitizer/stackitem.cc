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
#include "stackitemparserxml.h"
#include "stackitemparserdefault.h"

StackItem::StackItem(const QString &string)
{
    QString str = string.trimmed();

    AbstractStackItem StackItemParser;

    if (str.at(0) == '<' && str.at(str.length() - 1) == '>') {
        StackItemParser = StackItemParserXml(str);
    } else {
        StackItemParser = StackItemParserDefault(str);
    }

    this->string = StackItemParser.getString();
    this->num = StackItemParser.getStackItemNum();
    this->pointer = StackItemParser.getPointer();
    this->function = StackItemParser.getFunction();
    this->sourcefile = StackItemParser.getSourceFile();
    this->sourcefileline = StackItemParser.getSourceFileLine();
    this->object = StackItemParser.getObject();
    this->objectoffset = StackItemParser.getObjectOffset();
}

StackItem::~StackItem() {}
