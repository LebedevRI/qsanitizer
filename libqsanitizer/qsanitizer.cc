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
#include <QFile>
#include <QTextStream>
#include <QString>
#include <QStringList>

#include "qsanitizer.h"
#include "leaklist.h"

QSanitizer::QSanitizer() {}

QSanitizer::QSanitizer(const QString &logFile)
{
    QFile file(logFile);
    if (!file.open(QIODevice::ReadOnly)) {
        return;
    }

    QTextStream in(&file);
    QString longstring(in.readAll());
    QStringList strings = longstring.split("\n\n");

    this->leaks = LeakList(strings);

    file.close();
}

const LeakList &QSanitizer::getLeaks() const { return this->leaks; }
