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

#include "intanimator.h"

IntAnimator::IntAnimator(const QString& name) : QrealAnimator(name) {
    setNumberDecimals(0);
}

IntAnimator::IntAnimator(const int iniVal,
                         const int minVal,
                         const int maxVal,
                         const int prefferdStep,
                         const QString &name) :
    QrealAnimator(iniVal, minVal, maxVal, prefferdStep, name) {
     setNumberDecimals(0);
}

int IntAnimator::getCurrentIntValue() const {
    return qRound(getCurrentBaseValue());
}

int IntAnimator::getBaseIntValue(const qreal relFrame) const {
    return qRound(getBaseValue(relFrame));
}

int IntAnimator::getEffectiveIntValue() const {
    return qRound(getEffectiveValue());
}

int IntAnimator::getEffectiveIntValue(const qreal relFrame) const {
    return qRound(getEffectiveValue(relFrame));
}

void IntAnimator::setCurrentIntValue(const int value) {
    setCurrentBaseValue(value);
}

void IntAnimator::setIntValueRange(const int minVal,
                                   const int maxVal) {
    setValueRange(minVal, maxVal);
}
