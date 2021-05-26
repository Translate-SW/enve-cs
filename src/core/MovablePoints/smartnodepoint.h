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

#ifndef SMARTNODEPOINT_H
#define SMARTNODEPOINT_H
#include "MovablePoints/nonanimatedmovablepoint.h"
#include "nodepointvalues.h"
#include "segment.h"
#include "Animators/SmartPath/smartpath.h"
#include "Properties/property.h"
class UndoRedoStack;
class SkCanvas;
class SmartCtrlPoint;
class SmartPathAnimator;

enum class CanvasMode : short;
enum class CtrlsMode : short;

class CORE_EXPORT SmartNodePoint : public NonAnimatedMovablePoint {
    e_OBJECT
    friend class NormalSegment;
protected:
    SmartNodePoint(PathPointsHandler * const handler,
                   SmartPathAnimator * const parentAnimator);
public:
    void startTransform();
    void finishTransform();
    void cancelTransform();

    void saveTransformPivotAbsPos(const QPointF &absPivot);
    void rotateRelativeToSavedPivot(const qreal rot);
    void scaleRelativeToSavedPivot(const qreal sx, const qreal sy);

    void setRelativePos(const QPointF &relPos);

    void remove();

    void canvasContextMenu(PointTypeMenu * const menu);

    bool isVisible(const CanvasMode mode) const;

    void drawSk(SkCanvas * const canvas,
                const CanvasMode mode,
                const float invScale,
                const bool keyOnCurrent,
                const bool ctrlPressed);
    void setTransform(BasicTransformAnimator * const trans);
    MovablePoint *getPointAtAbsPos(const QPointF &absPos,
                                   const CanvasMode mode,
                                   const qreal invScale);
    void updateRadius();

    void updateCtrlsRadius();

    int moveToClosestSegment(const QPointF &absPos);
    SmartNodePoint *actionAddPointRelPos(const QPointF &relPos);
    SmartNodePoint* actionAddPointAbsPos(const QPointF &absPos);
    bool actionConnectToNormalPoint(SmartNodePoint * const other);
    void actionDisconnectFromNormalPoint(SmartNodePoint * const other);
    void actionMergeWithNormalPoint(SmartNodePoint * const other);
    void actionPromoteToNormal();
    void actionDemoteToDissolved(const bool approx);
    void actionRemove(const bool approx);

    //void moveByRel(const QPointF &relTranslation);

    QPointF getC0AbsPos() const;
    QPointF getC0Value() const;
    SmartCtrlPoint *getC0Pt();

    QPointF getC2AbsPos();
    QPointF getC2Value() const;
    SmartCtrlPoint *getC2Pt();

    SmartNodePoint *getNextPoint();
    SmartNodePoint *getPreviousPoint();

    bool isEndPoint() const;

    void setSeparateNodePoint(const bool separateNodePoint);
    bool isSeparateNodePoint();

    void setCtrlsMode(const CtrlsMode mode);
    void moveC2ToAbsPos(const QPointF &c2);
    void moveC0ToAbsPos(const QPointF &c0);
    void moveC2ToRelPos(const QPointF &c2);
    void moveC0ToRelPos(const QPointF &c0);

    SmartPathAnimator *getTargetAnimator() const;
    SmartPath *getTargetPath() const {
        return currentPath();
    }

    void setC0Enabled(const bool enabled);
    void setC2Enabled(const bool enabled);
    void resetC0();
    void resetC2();

    void setNodeId(const int idT);

    int getNodeId() const;

    NodePointValues getPointValues() const;

    bool isPrevNormalSelected() const;
    bool isNextNormalSelected() const;

    bool isNeighbourNormalSelected() const;
    //void moveByAbs(const QPointF &absTrans);

    SmartNodePoint *getConnectedSeparateNodePoint();

    NormalSegment getNextNormalSegment() {
        return mNextNormalSegment;
    }

    qreal getT() const {
        Q_ASSERT(mNode_d);
        return mNode_d->t();
    }

    QPointF getC0() const {
        Q_ASSERT(mNode_d);
        return mNode_d->c0();
    }

    QPointF getP1() const {
        Q_ASSERT(mNode_d);
        return mNode_d->p1();
    }

    QPointF getC2() const {
        Q_ASSERT(mNode_d);
        return mNode_d->c2();
    }

    bool getC0Enabled() const {
        if(!mPrevNormalPoint) return false;
        Q_ASSERT(mNode_d);
        return mNode_d->getC0Enabled();
    }

    bool getC2Enabled() const {
        if(!mNextNormalPoint) return false;
        Q_ASSERT(mNode_d);
        return mNode_d->getC2Enabled();
    }

    CtrlsMode getCtrlsMode() const {
        Q_ASSERT(mNode_d);
        return mNode_d->getCtrlsMode();
    }

    NodeType getType() const {
        Q_ASSERT(mNode_d);
        return mNode_d->getType();
    }

    void c0Moved(const QPointF& c0);

    void c2Moved(const QPointF& c2);

    void setNode(const Node * const node) {
        mNode_d = node;
        updateFromNodeData();
    }

    void updateFromNodeData();
    void updateFromNodeDataPosOnly();

    void afterNextNodeC0P1Changed() {
        mNextNormalSegment.afterChanged();
    }

    bool hasNextPoint() const;
    bool hasPrevPoint() const;
    bool hasNextNormalPoint() const;
    bool hasPrevNormalPoint() const;

    bool isNormal() const {
        return getType() == NodeType::normal;
    }

    bool isDissolved() const {
        return getType() == NodeType::dissolved;
    }

    const Node* getTargetNode() const {
        return mNode_d;
    }

    void clear() {
        mNode_d = nullptr;
        setPrevPoint(nullptr);
        setNextPoint(nullptr);
        setPrevNormalPoint(nullptr);
        setNextNormalPoint(nullptr);
    }

    PathPointsHandler * getHandler();
protected:
    void setNextPoint(SmartNodePoint * const nextPoint);
    void setPrevPoint(SmartNodePoint * const prevPoint);

    void setNextNormalPoint(SmartNodePoint * const nextPoint);
    void setPrevNormalPoint(SmartNodePoint * const prevPoint);
private:
    SmartPath* currentPath() const;
    void updateCtrlPtPos(SmartCtrlPoint * const pointToUpdate);

    bool mSeparateNodePoint = false;
    const Node * mNode_d = nullptr;

    const stdptr<PathPointsHandler> mHandler_k;
    const qptr<SmartPathAnimator> mParentAnimator;
    NormalSegment mNextNormalSegment;

    stdsptr<SmartCtrlPoint> mC0Pt;
    stdsptr<SmartCtrlPoint> mC2Pt;

    SmartNodePoint* mPrevNormalPoint = nullptr;
    SmartNodePoint* mNextNormalPoint = nullptr;

    SmartNodePoint* mPrevPoint = nullptr;
    SmartNodePoint* mNextPoint = nullptr;
};

#endif // SMARTNODEPOINT_H
