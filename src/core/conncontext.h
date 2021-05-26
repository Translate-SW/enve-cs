// enve - 2D animations software
// Copyright (C) 2016-2020 Maurycy Liebner

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

#ifndef CONNCONTEXT_H
#define CONNCONTEXT_H

#include "core_global.h"

#include <QObject>
#include <memory>

class CORE_EXPORT ConnContext {
public:
    ConnContext();
    ConnContext(ConnContext&) = delete;

    virtual ~ConnContext();

    ConnContext& operator<<(const QMetaObject::Connection& connection);

    void clear();
private:
    QList<QMetaObject::Connection> mConns;
};

#endif // CONNCONTEXT_H
