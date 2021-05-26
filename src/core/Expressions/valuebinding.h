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

#ifndef VALUEBINDING_H
#define VALUEBINDING_H

#include "propertybindingbase.h"

class CORE_EXPORT ValueBinding : public PropertyBindingBase {
    ValueBinding(const Property* const context);
public:
    static qsptr<ValueBinding> sCreate(const Property* const context);

    QJSValue getJSValue(QJSEngine& e);
    QJSValue getJSValue(QJSEngine& e, const qreal relFrame);

    FrameRange identicalRelRange(const int absFrame);
    FrameRange nextNonUnaryIdenticalRelRange(const int absFrame);
    QString path() const { return "$value"; }
};

#endif // VALUEBINDING_H
