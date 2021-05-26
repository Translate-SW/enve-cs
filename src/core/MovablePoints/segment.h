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

#ifndef SEGMENT_H
#define SEGMENT_H

class SmartNodePoint;
class SmartCtrlPoint;
class PathPointsHandler;

#include "smartPointers/stdpointer.h"
#include "Segments/qcubicsegment2d.h"
#include "pointhelpers.h"

class CORE_EXPORT Segment {
public:

};

class CORE_EXPORT NormalSegment {
public:
    bool operator==(const NormalSegment& other) const;

    bool operator!=(const NormalSegment& other) const {
        return !this->operator==(other);
    }

    struct PointOnSegment {
        qreal fT;
        QPointF fPos;
    };
    struct SubSegment {
        SmartNodePoint* fFirstPt;
        SmartNodePoint* fLastPt;
        const NormalSegment* fParentSeg;

        bool isValid() const {
            return fFirstPt && fLastPt && fParentSeg;
        }

        qreal getMinT() const;
        qreal getMaxT() const;

        qreal getParentTAtThisT(const qreal thisT) const;
        QPointF getRelPosAtT(const qreal thisT) const;
    };
    NormalSegment();
    NormalSegment(SmartNodePoint * const firstNode,
                  SmartNodePoint * const lastNode);

    SmartNodePoint* divideAtAbsPos(const QPointF& absPos);
    SmartNodePoint *divideAtT(const qreal &t);

    QPointF getRelPosAtT(const qreal t) const;
    QPointF getAbsPosAtT(const qreal t) const;

    void makePassThroughAbs(const QPointF &absPos, const qreal t);
    void makePassThroughRel(const QPointF &relPos, const qreal t);

    void finishPassThroughTransform();
    void startPassThroughTransform();
    void cancelPassThroughTransform();

    void generateSkPath();

    void drawHoveredSk(SkCanvas * const canvas,
                       const float invScale);

    SmartNodePoint *getFirstNode() const;
    SmartNodePoint *getLastNode() const;

    QPointF getSlopeVector(const qreal t);

    bool isValid() const;
    bool isNormal() const;

    void reset() { clear(); }

    void clear();

    void disconnect() const;

    int nodesCount() const;

    int innerNodesCount() const {
        return mInnerDissolved.count();
    }

    SmartNodePoint* getNodeAt(const int id) const;

    SubSegment getClosestSubSegment(const QPointF& relPos,
                                    qreal& minDist) const {
        auto relSeg = getAsRelSegment();
        qreal closestT;
        minDist = relSeg.minDistanceTo(relPos, &closestT);
        return subSegmentAtT(closestT);
    }

    SubSegment getClosestSubSegmentForDummy(const QPointF& relPos,
                                            qreal& minDist) const;

    void afterChanged() const {
        updateDissolvedPos();
    }

    qCubicSegment2D getAsAbsSegment() const;
    qCubicSegment2D getAsRelSegment() const;

    void updateDissolved();

    qreal closestRelT(const QPointF& relPos) const {
        return getAsRelSegment().tValueForPointClosestTo(relPos);
    }

    qreal closestAbsT(const QPointF& absPos) const {
        return getAsAbsSegment().tValueForPointClosestTo(absPos);
    }
private:
    void updateDissolvedPos() const;
    SubSegment subSegmentAtT(const qreal t) const;

    SkPath mSkPath;
    stdptr<PathPointsHandler> mHandler_k;
    stdptr<SmartNodePoint> mFirstNode;
    stdptr<SmartCtrlPoint> mFirstNodeC2;
    QList<stdptr<SmartNodePoint>> mInnerDissolved;
    stdptr<SmartCtrlPoint> mLastNodeC0;
    stdptr<SmartNodePoint> mLastNode;
};

#endif // SEGMENT_H
