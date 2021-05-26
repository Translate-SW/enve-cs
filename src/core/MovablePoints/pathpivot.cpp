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

#include "pathpivot.h"
#include "canvas.h"
#include "pointhelpers.h"
#include "Animators/transformanimator.h"

PathPivot::PathPivot(const Canvas * const parent) :
    NonAnimatedMovablePoint(parent->getTransformAnimator(),
                            TYPE_PIVOT_POINT),
    mCanvas(parent) {
    setRadius(7);
}

void PathPivot::drawSk(SkCanvas * const canvas,
                       const CanvasMode mode,
                       const float invScale,
                       const bool keyOnCurrent,
                       const bool ctrlPressed) {
    Q_UNUSED(keyOnCurrent)
    Q_UNUSED(ctrlPressed)
    const SkPoint absPos = toSkPoint(getAbsolutePos());
    if(isVisible(mode)) {
        const SkColor fillCol = isSelected() ?
                    SkColorSetRGB(0, 255, 0) :
                    SkColorSetRGB(125, 255, 125);
        const SkPoint absPos = toSkPoint(getAbsolutePos());
        drawOnAbsPosSk(canvas, absPos, invScale, fillCol);
    }

    canvas->save();
    canvas->translate(absPos.x(), absPos.y());
    SkPaint paint;
    paint.setStyle(SkPaint::kStroke_Style);
    paint.setColor(SK_ColorBLACK);
    const float scaledHalfRadius = toSkScalar(getRadius()*0.5)*invScale;
    canvas->drawLine(-scaledHalfRadius, 0, scaledHalfRadius, 0, paint);
    canvas->drawLine(0, -scaledHalfRadius, 0, scaledHalfRadius, paint);
    canvas->restore();
}

void PathPivot::drawTransforming(SkCanvas * const canvas,
                                 const CanvasMode mode,
                                 const float invScale,
                                 const float interval) {
    drawSk(canvas, mode, invScale, false, false);
    SkPaint paint;
    paint.setStyle(SkPaint::kStroke_Style);
    paint.setColor(SK_ColorBLACK);
    const float intervals[2] = {interval, interval};
    paint.setPathEffect(SkDashPathEffect::Make(intervals, 2, 0));
    paint.setAntiAlias(true);
    canvas->drawLine(toSkPoint(getAbsolutePos()),
                     toSkPoint(mMousePos), paint);
    paint.setPathEffect(nullptr);
}

bool PathPivot::isVisible(const CanvasMode mode) const {
    if(mCanvas->getPivotLocal()) return false;
    if(mode == CanvasMode::pointTransform) return !mCanvas->isPointSelectionEmpty();
    else if(mode == CanvasMode::boxTransform) return !mCanvas->isBoxSelectionEmpty();
    return false;
}
