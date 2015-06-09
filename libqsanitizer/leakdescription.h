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

#ifndef LEAKDESCRIPTION_H
#define LEAKDESCRIPTION_H

#include <QtGlobal>
#include <QString>

class LeakDescription
{
public:
    LeakDescription();
    LeakDescription(const QString &string);
    ~LeakDescription();

    bool getLeakType() const;
    std::size_t getLeakSize() const;
    std::size_t getLeakCount() const;

private:
    bool directLeak;       // true - Direct leak; false - Indirect leak
    std::size_t leakSize;  // bytes leaked
    std::size_t leakCount; // objects leaked
};

#endif // LEAKDESCRIPTION_H
