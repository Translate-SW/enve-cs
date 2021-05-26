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

#ifndef SMARTSmartVectorPath_H
#define SMARTSmartVectorPath_H
#include <QPainterPath>
#include <QLinearGradient>
#include "pathbox.h"
#include "Animators/SmartPath/smartpathcollection.h"

class NodePoint;
class ContainerBox;
class PathAnimator;

enum class CanvasMode : short;

class SmartVectorPathEdge;

class CORE_EXPORT SmartVectorPath : public PathBox {
    e_OBJECT
    e_DECLARE_TYPE(SmartVectorPath)
protected:
    SmartVectorPath();
public:
    void setupCanvasMenu(PropertyMenu * const menu);

    SkPath getRelativePath(const qreal relFrame) const;

    bool differenceInEditPathBetweenFrames(const int frame1,
                                           const int frame2) const;

    void saveSVG(SvgExporter& exp, DomEleTask* const task) const;

    void applyCurrentTransform();

    void loadSkPath(const SkPath& path);

    SmartPathCollection *getPathAnimator();

    QList<qsptr<SmartVectorPath>> breakPathsApart_k();
protected:
    void getMotionBlurProperties(QList<Property*> &list) const;
    qsptr<SmartPathCollection> mPathAnimator;
};

#endif // SMARTSmartVectorPath_H
