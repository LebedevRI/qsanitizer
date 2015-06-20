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

#include <QAbstractTableModel>
#include <QString>
#include <QCheckBox>
#include <QDebug>

#include "ignoredobjectstablemodel.h"

IgnoredObjectsTableModel::IgnoredObjectsTableModel(QObject *parent)
    : QAbstractTableModel(parent)
{
}

void IgnoredObjectsTableModel::SetObjectsMap(const QMap<QString, int> &objects)
{
    this->beginResetModel();
    this->objects = objects;
    this->endResetModel();
}

int IgnoredObjectsTableModel::rowCount(const QModelIndex & /*parent*/) const
{
    return this->objects.size();
}

int IgnoredObjectsTableModel::columnCount(const QModelIndex & /*parent*/) const
{
    return 3;
}

QVariant IgnoredObjectsTableModel::data(const QModelIndex &index,
                                        int role) const
{
    auto row = index.row();
    auto col = index.column();

    switch (role) {
    case Qt::DisplayRole:
        if (col == 0)
            return QString("");

        if (col == 1) {
            return QString(this->objects.keys().at(row));
        }

        return this->objects.values().at(row);
        break;
    case Qt::CheckStateRole:

        if (col == 0) {
            if (this->ignoredObjects.contains(this->objects.keys().at(row)))
                return Qt::Checked;
            else
                return Qt::Unchecked;
        }
    }

    return QVariant();
}

bool IgnoredObjectsTableModel::setData(const QModelIndex &index,
                                       const QVariant &value, int role)
{
    auto col = index.column();
    if (col != 0)
        return true;

    if (role == Qt::CheckStateRole) {
        auto row = index.row();
        auto ignored = value.toBool();

        auto object = this->objects.keys().at(row);

        if (ignored)
            this->ignoredObjects.insert(object);
        else
            this->ignoredObjects.remove(object);

        QModelIndex topLeft = index;
        QModelIndex bottomRight = index;
        emit dataChanged(topLeft, bottomRight);

        return true;
    }

    return true;
}

Qt::ItemFlags IgnoredObjectsTableModel::flags(const QModelIndex &index) const
{
    auto col = index.column();

    auto flags = QAbstractTableModel::flags(index);

    if (col == 0) {
        flags |= Qt::ItemIsUserCheckable;
    }

    return flags;
}
