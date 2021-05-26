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

#include "nodepointvalues.h"


NodePointValues operator-(const NodePointValues &ppv1,
                          const NodePointValues &ppv2) {
    return {ppv1.fC0 - ppv2.fC0,
            ppv1.fP1 - ppv2.fP1,
            ppv1.fC2 - ppv2.fC2};
}

NodePointValues operator+(const NodePointValues &ppv1,
                          const NodePointValues &ppv2) {
    return {ppv1.fC0 + ppv2.fC0,
            ppv1.fP1 + ppv2.fP1,
            ppv1.fC2 + ppv2.fC2};
}

NodePointValues operator/(const NodePointValues &ppv,
                          const qreal val) {
    qreal invVal = 1/val;
    return {ppv.fC0 * invVal,
            ppv.fP1 * invVal,
            ppv.fC2 * invVal};
}

NodePointValues operator*(const qreal val,
                          const NodePointValues &ppv) {
    return ppv*val;
}

NodePointValues operator*(const NodePointValues &ppv,
                          const qreal val) {
    return {ppv.fC0 * val,
            ppv.fP1 * val,
            ppv.fC2 * val};
}
