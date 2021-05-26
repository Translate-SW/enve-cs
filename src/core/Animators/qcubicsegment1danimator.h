﻿// enve - 2D animations software
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

#ifndef QCUBICSEGMENT1DANIMATOR_H
#define QCUBICSEGMENT1DANIMATOR_H
#include "Animators/interpolationanimatort.h"
#include "Segments/qcubicsegment1d.h"
#include "../ReadWrite/basicreadwrite.h"
class qCubicSegment1DAnimator;

class CORE_EXPORT qCubicSegment1DAnimator : public InterpolationAnimatorT<qCubicSegment1D> {
    Q_OBJECT
    e_OBJECT
protected:
    qCubicSegment1DAnimator(const QString &name);

    void afterValueChanged() {
        emit currentValueChanged(mCurrentValue);
    }

    void prp_readPropertyXEV_impl(const QDomElement& ele, const XevImporter& imp);
    QDomElement prp_writePropertyXEV_impl(const XevExporter& exp) const;
signals:
    void currentValueChanged(qCubicSegment1D);
};

#endif // QCUBICSEGMENT1DANIMATOR_H
