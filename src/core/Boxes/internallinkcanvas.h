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

#ifndef INTERNALLINKCANVAS_H
#define INTERNALLINKCANVAS_H
#include "internallinkgroupbox.h"
#include "Properties/boolproperty.h"
#include "Boxes/frameremapping.h"

class CORE_EXPORT InternalLinkCanvas : public InternalLinkGroupBox {
    e_OBJECT
protected:
    InternalLinkCanvas(ContainerBox * const linkTarget,
                       const bool innerLink);
public:
    void setupRenderData(const qreal relFrame,
                         BoxRenderData * const data,
                         Canvas * const scene);

    qsptr<BoundingBox> createLink(const bool inner);

    stdsptr<BoxRenderData> createRenderData();

    bool relPointInsidePath(const QPointF &relPos) const;
    void anim_setAbsFrame(const int frame);
    void setupCanvasMenu(PropertyMenu * const menu);

    void enableFrameRemappingAction();
    void disableFrameRemappingAction();

    bool clipToCanvas();
private:
    qsptr<BoolProperty> mClipToCanvas =
            enve::make_shared<BoolProperty>("clip");
    qsptr<QrealFrameRemapping> mFrameRemapping =
            enve::make_shared<QrealFrameRemapping>();
};

#endif // INTERNALLINKCANVAS_H
