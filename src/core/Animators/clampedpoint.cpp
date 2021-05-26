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

#include "clampedpoint.h"

ClampedPoint::ClampedPoint(const qreal x, const qreal y) :
    mX(x), mY(y) {}

void ClampedPoint::read(QIODevice * const target) {
    target->read(reinterpret_cast<char*>(&mX), sizeof(qreal));
    target->read(reinterpret_cast<char*>(&mY), sizeof(qreal));
}

void ClampedPoint::saveXValue() {
    mX.saveValue();
}

void ClampedPoint::restoreSavedXValue() {
    mX.restoreSavedValue();
}

void ClampedPoint::saveYValue() {
    mY.saveValue();
}

void ClampedPoint::restoreSavedYValue() {
    mY.restoreSavedValue();
}

void ClampedPoint::saveValue() {
    mX.saveValue();
    mY.saveValue();
}

void ClampedPoint::restoreSavedValue() {
    mX.restoreSavedValue();
    mY.restoreSavedValue();
}

QPointF ClampedPoint::getRawSavedValue() const {
    return {mX.getRawSavedValue(), mY.getRawSavedValue()};
}

QPointF ClampedPoint::getRawValue() const {
    return {mX.getRawValue(), mY.getRawValue()};
}

qreal ClampedPoint::getRawSavedXValue() const {
    return mX.getRawSavedValue();
}

qreal ClampedPoint::getRawXValue() const {
    return mX.getRawValue();
}

qreal ClampedPoint::getRawSavedYValue() const {
    return mY.getRawSavedValue();
}

qreal ClampedPoint::getRawYValue() const {
    return mY.getRawValue();
}

QPointF ClampedPoint::getClampedSavedValue(const QPointF &relTo) const {
    const qreal xFracDiv = mX.getRawSavedValue() - relTo.x();
    qreal xFrac;
    if(isZero6Dec(xFracDiv)) xFrac = 1;
    else xFrac = (mX.getClampedSavedValue() - relTo.x())/xFracDiv;

    qreal yFracDiv = mY.getRawSavedValue() - relTo.y();
    qreal yFrac;
    if(isZero6Dec(yFracDiv)) yFrac = 1;
    else yFrac = (mY.getClampedSavedValue() - relTo.y())/yFracDiv;

    const qreal minFrac = qMin(xFrac, yFrac);
    const QPointF rawVals{mX.getRawSavedValue(), mY.getRawSavedValue()};
    return relTo + minFrac*(rawVals - relTo);
}

QPointF ClampedPoint::getClampedValue(const QPointF &relTo) const {
    const qreal xFracDiv = mX.getRawValue() - relTo.x();
    qreal xFrac;
    if(isZero6Dec(xFracDiv)) xFrac = 1;
    else xFrac = (mX.getClampedValue() - relTo.x())/xFracDiv;

    qreal yFracDiv = mY.getRawValue() - relTo.y();
    qreal yFrac;
    if(isZero6Dec(yFracDiv)) yFrac = 1;
    else yFrac = (mY.getClampedValue() - relTo.y())/yFracDiv;

    const qreal minFrac = qMin(xFrac, yFrac);
    const QPointF rawVals{mX.getRawValue(), mY.getRawValue()};
    return relTo + minFrac*(rawVals - relTo);
}

void ClampedPoint::setXValue(const qreal value) {
    mX.setValue(value);
}

void ClampedPoint::setYValue(const qreal value) {
    mY.setValue(value);
}

void ClampedPoint::setValue(const QPointF &value) {
    mX.setValue(value.x());
    mY.setValue(value.y());
}

void ClampedPoint::clampValue() {
    mX.clampValue();
    mY.clampValue();
}

void ClampedPoint::setXRange(const qreal min, const qreal max) {
    mX.setRange(min, max);
}

void ClampedPoint::setYRange(const qreal min, const qreal max) {
    mY.setRange(min, max);
}

void ClampedPoint::setXMax(const qreal max) {
    mX.setMax(max);
}

void ClampedPoint::setXMin(const qreal min) {
    mX.setMin(min);
}

void ClampedPoint::setYMax(const qreal max) {
    mY.setMax(max);
}

void ClampedPoint::setYMin(const qreal min) {
    mY.setMin(min);
}
