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

#include "leaklistsortfilterproxymodel.h"
#include "leaklist.h"
#include "leakitem.h"

LeakListSortFilterProxyModel::LeakListSortFilterProxyModel(QObject *parent)
    : QSortFilterProxyModel(parent)
{
}

void LeakListSortFilterProxyModel::setLeakList(LeakList *leakList)
{
    this->beginResetModel();
    this->leakList = leakList;
    this->endResetModel();
}

void LeakListSortFilterProxyModel::setIgnoredObjects(QSet<QString> *objects)
{
    this->beginResetModel();
    this->ignoredObjects = objects;
    this->endResetModel();
}

bool LeakListSortFilterProxyModel::filterAcceptsRow(
    int sourceRow, const QModelIndex &sourceParent) const
{
    if (this->ignoredObjects->isEmpty())
        return true;

    auto item = this->leakList->at(sourceRow);
    auto objects = item.getObjectsSet();

    for (const auto &object : objects) {
        if (this->ignoredObjects->contains(object))
            return false;
    }

    return true;
}
