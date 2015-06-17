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
#include <QXmlStreamReader>

#include "stackitemparserxml.h"

QString StackItemParserXml::readNextText(QXmlStreamReader *xml) const
{
    xml->readNext();
    return xml->text().toString();
}

StackItemParserXml::StackItemParserXml(const QString &string)
    : string(QString("")), num(0ul), pointer(quintptr(0x0)),
      function(QString("")), sourcefile(QString("")), sourcefileline(0ul),
      object(QString("")), objectoffset(quintptr(0x0))
{
    QXmlStreamReader *xml = new QXmlStreamReader(string);

    if (xml->readNextStartElement() && xml->name() == "frame") {
        while (xml->readNextStartElement()) {
            bool ok;

            if (xml->name() == "n")
                this->num = readNextText(xml).toULong();
            else if (xml->name() == "p")
                this->pointer = readNextText(xml).toULongLong(&ok, 16);
            else if (xml->name() == "m")
                this->object = readNextText(xml);
            else if (xml->name() == "o")
                this->objectoffset = readNextText(xml).toULongLong(&ok, 16);
            else if (xml->name() == "f")
                this->function = readNextText(xml);
            else if (xml->name() == "s")
                this->sourcefile = readNextText(xml);
            else if (xml->name() == "l")
                this->sourcefileline = readNextText(xml).toULong();

            xml->skipCurrentElement();
        }
    }

    // readNextStartElement() leaves the stream in
    // an invalid state at the end. A single readNext()
    // will advance us to EndDocument.
    if (xml->tokenType() == QXmlStreamReader::Invalid)
        xml->readNext();

    if (xml->hasError()) {
        xml->raiseError();
    }

    delete xml;
}

StackItemParserXml::~StackItemParserXml() {}

const QString &StackItemParserXml::getString() const { return this->string; }

std::size_t StackItemParserXml::getStackItemNum() const { return this->num; }

quintptr StackItemParserXml::getPointer() const { return this->pointer; }

const QString &StackItemParserXml::getFunction() const
{
    return this->function;
}

const QString &StackItemParserXml::getSourceFile() const
{
    return this->sourcefile;
}

std::size_t StackItemParserXml::getSourceFileLine() const
{
    return this->sourcefileline;
}

const QString &StackItemParserXml::getObject() const { return this->object; }

quintptr StackItemParserXml::getObjectOffset() const
{
    return this->objectoffset;
}
