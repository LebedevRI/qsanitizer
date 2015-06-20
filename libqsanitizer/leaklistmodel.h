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

#ifndef LEAKLISTMODEL_H
#define LEAKLISTMODEL_H

#include <QAbstractListModel>
#include <QList>

#include "leakitem.h"
#include "leaklist.h"

class LeakListModel : public QAbstractListModel
{
public:
    LeakListModel(QObject *parent = 0);
    LeakListModel(const LeakList &leaks, QObject *parent = 0);
    ~LeakListModel();

    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role) const;

private:
    LeakList leakList;
};

#endif // LEAKLISTMODEL_H
