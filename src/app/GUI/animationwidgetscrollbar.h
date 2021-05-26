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

#ifndef ANIMATiONWIDGETSCROLLBAR_H
#define ANIMATiONWIDGETSCROLLBAR_H

#include <QWidget>
#include "smartPointers/ememory.h"
#include "canvas.h"
class HddCachableCacheHandler;

class FrameScrollBar : public QWidget {
    Q_OBJECT
public:
    explicit FrameScrollBar(const int minSpan,
                            const int maxSpan,
                            const bool range,
                            const bool clamp,
                            QWidget *parent = nullptr);
    bool setFirstViewedFrame(const int firstFrame);
    void setFramesSpan(int newSpan);

    int getMaxFrame();
    int getMinFrame();

    FrameRange getViewedRange() const;
    int getFirstViewedFrame() const;
    int getLastViewedFrame() const;

    void setHandleColor(const QColor &col) {
        mHandleColor = col;
    }

    void setCurrentCanvas(Canvas * const canvas);

    void setDisplayedFrameRange(const FrameRange& range);
    void setViewedFrameRange(const FrameRange& range);
    void setCanvasFrameRange(const FrameRange& range);
protected:
    qreal posToFrame(int xPos);
    void paintEvent(QPaintEvent *);
    void wheelEvent(QWheelEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *);
signals:
    void triggeredFrameRangeChange(FrameRange);
    void frameRangeChange(FrameRange);
private:
    void emitChange();
    void emitTriggeredChange();

    bool mClamp;
    bool mDisplayTime = false;
    bool mRange;
    bool mPressed = false;

    int mSavedFirstFrame;

    int mFirstViewedFrame = 0;
    int mViewedFramesSpan = 50;

    int mDrawFrameInc = 20;

    FrameRange mFrameRange{0, 200};

    int mMinSpan;
    int mMaxSpan;
    int mSpanInc;

    FrameRange mCanvasRange{0, 200};

    qreal mFps;
    qreal mLastMousePressFrame;

    QColor mHandleColor = QColor(100, 100, 100);
    qptr<Canvas> mCurrentCanvas;
};

#endif // ANIMATiONWIDGETSCROLLBAR_H
