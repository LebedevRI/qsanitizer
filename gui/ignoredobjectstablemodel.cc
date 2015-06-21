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

void IgnoredObjectsTableModel::setModel(const QMap<QString, int> &objects)
{
    this->beginResetModel();

    this->model.clear();

    auto i = objects.constBegin();
    while (i != objects.constEnd()) {
        this->model.append(
            {.object = i.key(), .occurences = i.value(), .ignored = false});
        ++i;
    }

    this->endResetModel();
}

int IgnoredObjectsTableModel::rowCount(const QModelIndex & /*parent*/) const
{
    return this->model.size();
}

int IgnoredObjectsTableModel::columnCount(const QModelIndex & /*parent*/) const
{
    return 3;
}

QVariant IgnoredObjectsTableModel::data(const QModelIndex &index,
                                        int role) const
{
    auto col = index.column();
    auto row = index.row();

    switch (role) {
    case Qt::DisplayRole:
        if (col == 0) {
            return QVariant();
        } else if (col == 1) {
            return this->model[row].object;
        } else if (col == 2) {
            return model[row].occurences;
        }
        break;
    case Qt::CheckStateRole:
        if (col == 0) {
            if (model[row].ignored) {
                return Qt::Checked;
            } else {
                return Qt::Unchecked;
            }
        }
        break;
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

        this->model[row].ignored = ignored;

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
