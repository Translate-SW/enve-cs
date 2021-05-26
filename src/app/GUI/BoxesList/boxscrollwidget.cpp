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

#include "boxscrollwidget.h"
#include "GUI/BoxesList/OptimalScrollArea/scrollarea.h"
#include "Boxes/boundingbox.h"
#include "boxscroller.h"
#include "GUI/canvaswindow.h"
#include "GUI/mainwindow.h"
#include "Private/document.h"

BoxScrollWidget::BoxScrollWidget(Document &document,
                                 ScrollArea * const parent) :
    ScrollWidget(new BoxScroller(this), parent) {
    const auto visPartWidget = visiblePartWidget();
    mCoreAbs = document.SWT_createAbstraction(
                visPartWidget->getUpdateFuncs(),
                visPartWidget->getId());
}

BoxScrollWidget::~BoxScrollWidget() {
    if(mCoreAbs) mCoreAbs->removeAlongWithAllChildren_k();
}

BoxScroller *BoxScrollWidget::getBoxScroller() {
    const auto visPartWidget = visiblePartWidget();
    return static_cast<BoxScroller*>(visPartWidget);
}

void BoxScrollWidget::setCurrentScene(Canvas * const scene) {
    getBoxScroller()->setCurrentScene(scene);
}

void BoxScrollWidget::setSiblingKeysView(KeysView * const keysView) {
    getBoxScroller()->setKeysView(keysView);
}

TimelineHighlightWidget *BoxScrollWidget::requestHighlighter() {
    return getBoxScroller()->requestHighlighter();
}
