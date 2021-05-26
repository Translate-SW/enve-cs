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

#ifndef INTANIMATOR_H
#define INTANIMATOR_H
#include "qrealanimator.h"

class CORE_EXPORT IntAnimator : public QrealAnimator {
    e_OBJECT
protected:
    IntAnimator(const QString& name);
    IntAnimator(const int iniVal,
                const int minVal,
                const int maxVal,
                const int prefferdStep,
                const QString& name);
public:
    int getCurrentIntValue() const;
    void setCurrentIntValue(const int value);
    void setIntValueRange(const int minVal, const int maxVal);

    int getBaseIntValue(const qreal relFrame) const;
    int getEffectiveIntValue() const;
    int getEffectiveIntValue(const qreal relFrame) const;

    static qsptr<IntAnimator> sCreateSeed() {
        const auto result = enve::make_shared<IntAnimator>("seed");
        result->setIntValueRange(0, 9999);
        result->setCurrentIntValue(qrand() % 9999);
        return result;
    }
};

#endif // INTANIMATOR_H
