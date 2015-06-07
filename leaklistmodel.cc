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

#include "leaklistmodel.h"

LeakListModel::LeakListModel(QObject *parent) : QAbstractListModel(parent) {}

LeakListModel::LeakListModel(const QStringList &strings, QObject *parent)
    : QAbstractListModel(parent), LeakList(strings)
{
}

int LeakListModel::rowCount(const QModelIndex &parent) const
{
    return LeakList.count();
}

QVariant LeakListModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (index.row() >= LeakList.size())
        return QVariant();

    if (role == Qt::DisplayRole)
        return LeakList.at(index.row());
    else
        return QVariant();
}

QVariant LeakListModel::headerData(int section, Qt::Orientation orientation,
                                   int role) const
{
    if (role != Qt::DisplayRole)
        return QVariant();

    if (orientation == Qt::Horizontal)
        return QString("Column %1").arg(section);
    else
        return QString("Row %1").arg(section);
}

Qt::ItemFlags LeakListModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::ItemIsEnabled;

    return QAbstractItemModel::flags(index) | Qt::ItemIsEditable;
}

bool LeakListModel::setData(const QModelIndex &index, const QVariant &value,
                            int role)
{
    if (index.isValid() && role == Qt::EditRole) {

        LeakList.replace(index.row(), value.toString());
        emit dataChanged(index, index);
        return true;
    }

    return false;
}

bool LeakListModel::insertRows(int position, int rows,
                               const QModelIndex &parent)
{
    beginInsertRows(QModelIndex(), position, position + rows - 1);

    for (int row = 0; row < rows; ++row) {
        LeakList.insert(position, "");
    }

    endInsertRows();
    return true;
}

bool LeakListModel::removeRows(int position, int rows,
                               const QModelIndex &parent)
{
    beginRemoveRows(QModelIndex(), position, position + rows - 1);

    for (int row = 0; row < rows; ++row) {
        LeakList.removeAt(position);
    }

    endRemoveRows();
    return true;
}
