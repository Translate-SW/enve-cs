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

#include "internallinkbox.h"
#include "GUI/edialogs.h"
#include "canvas.h"
#include "Timeline/durationrectangle.h"
#include "Animators/transformanimator.h"
#include "skia/skiahelpers.h"
#include "videobox.h"
#include "Sound/evideosound.h"

InternalLinkBox::InternalLinkBox(BoundingBox * const linkTarget,
                                 const bool innerLink) :
    InternalLinkBoxBase<BoundingBox>("Link", eBoxType::internalLink, innerLink) {
    ca_prependChild(mTransformAnimator.data(), mBoxTarget);
    connect(mBoxTarget.data(), &BoxTargetProperty::targetSet,
            this, &InternalLinkBox::setLinkTarget);
    mBoxTarget->setTarget(linkTarget);
}

void InternalLinkBox::setLinkTarget(BoundingBox * const linkTarget) {
    mSound.reset();
    auto& conn = assignLinkTarget(linkTarget);
    mBoxTarget->setTargetAction(linkTarget);
    if(const auto vidBox = enve_cast<VideoBox*>(linkTarget)) {
        mSound = vidBox->sound()->createLink();
        conn << connect(this, &eBoxOrSound::parentChanged,
                        mSound.get(), &eBoxOrSound::setParentGroup);
        mSound->setParentGroup(getParentGroup());
    }
    planUpdate(UpdateReason::userChange);
}

void InternalLinkBox::setupRenderData(const qreal relFrame,
                                      BoxRenderData * const data,
                                      Canvas* const scene) {
    const auto linkTarget = getLinkTarget();
    if(linkTarget) linkTarget->setupRenderData(relFrame, data, scene);
    BoundingBox::setupRenderData(relFrame, data, scene);
}
