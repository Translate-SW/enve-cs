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

#ifndef INTERPOLATIONKEYT_H
#define INTERPOLATIONKEYT_H
#include "graphkeyt.h"

template <typename T>
class InterpolationKeyT : public GraphKeyT<T> {
    e_OBJECT
protected:
    using GraphKeyT<T>::GraphKeyT;
public:
    qreal getValueForGraph() const {
        return this->mRelFrame;
    }

    void setValueForGraph(const qreal value) {
        Q_UNUSED(value)
    }
protected:
    void setRelFrame(const int frame) {
        if(frame == this->mRelFrame) return;
        const int dFrame = frame - this->mRelFrame;
        GraphKeyT<T>::setRelFrame(frame);
        this->setC0ValueVar(this->c0Clamped().getRawYValue() + dFrame);
        this->setC1ValueVar(this->c1Clamped().getRawYValue() + dFrame);
    }
};

#endif // INTERPOLATIONKEYT_H
