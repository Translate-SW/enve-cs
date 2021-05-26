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

#ifndef ANIMATIONBOX_H
#define ANIMATIONBOX_H

#include "Animators/intanimator.h"
#include "Timeline/fixedlenanimationrect.h"
#include "boundingbox.h"
#include "imagebox.h"

class AnimationFrameHandler;
class IntFrameRemapping;

class CORE_EXPORT AnimationBox : public BoundingBox {
    e_OBJECT
protected:
    AnimationBox(const QString& name, const eBoxType type);
public:
    virtual void changeSourceFile() = 0;
    void animationDataChanged();
    virtual void setStretch(const qreal stretch) {
        mStretch = stretch;
        prp_afterWholeInfluenceRangeChanged();
        updateAnimationRange();
    }

    void anim_setAbsFrame(const int frame);

    FrameRange prp_getIdenticalRelRange(const int relFrame) const;

    void setupCanvasMenu(PropertyMenu * const menu);
    void setupRenderData(const qreal relFrame,
                         BoxRenderData * const data,
                         Canvas * const scene);
    stdsptr<BoxRenderData> createRenderData();
    bool shouldScheduleUpdate();
    void saveSVG(SvgExporter& exp, DomEleTask* const task) const;

    FixedLenAnimationRect *getAnimationDurationRect() const;
    void updateAnimationRange();

    void afterUpdate();
    void beforeAddingScheduler();
    int getAnimationFrameForRelFrame(const qreal relFrame);

    void enableFrameRemappingAction();
    void disableFrameRemappingAction();

    qreal getStretch() const { return mStretch; }

    void reload();
protected:
    void setAnimationFramesHandler(const qsptr<AnimationFrameHandler>& src);
private:
    void createPaintObject(const int firstAbsFrame,
                           const int lastAbsFrame,
                           const int increment);

    qreal mStretch = 1;
    qsptr<AnimationFrameHandler> mSrcFramesCache;
    qsptr<IntFrameRemapping> mFrameRemapping;
};

#endif // ANIMATIONBOX_H
