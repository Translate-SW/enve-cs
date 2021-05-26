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

#include "propertybindingbase.h"

PropertyBindingBase::PropertyBindingBase(const Property* const context) :
    mContext(context) {}

bool PropertyBindingBase::setAbsFrame(const int absFrame) {
    if(mContext) {
        const qreal oldRelFrame = mRelFrame;
        mRelFrame = mContext->prp_absFrameToRelFrameF(absFrame);
        const auto idRange = identicalRelRange(absFrame);
        if(idRange.inRange(oldRelFrame)) return false;
        emit currentValueChanged();
        return true;
    }
    return false;
}
