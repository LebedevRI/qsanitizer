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

#include <QAbstractListModel>
#include <QList>
#include <QStringList>

#include "leaklistmodel.h"
#include "leakitem.h"

LeakListModel::LeakListModel(QObject *parent) : QAbstractListModel(parent) {}

void LeakListModel::setLeakList(LeakList *list)
{
    this->beginResetModel();
    this->leakList = list;
    this->endResetModel();
}

int LeakListModel::rowCount(const QModelIndex & /* parent */) const
{
    return leakList->count();
}

QVariant LeakListModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (index.row() >= leakList->size())
        return QVariant();

    if (role == Qt::DisplayRole)
        return leakList->at(index.row()).getString();
    else
        return QVariant();
}
