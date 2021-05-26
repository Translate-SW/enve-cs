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

#ifndef SCENECHOOSER_H
#define SCENECHOOSER_H
#include <QMenu>
class Canvas;
class Document;

class SceneChooser : public QMenu {
    Q_OBJECT
public:
    SceneChooser(Document &document, const bool active,
                 QWidget * const parent = nullptr);

    void setCurrentScene(Canvas * const scene);
    Canvas* getCurrentScene() const { return mCurrentScene; }
signals:
    void currentChanged(Canvas*);
private:
    void addScene(Canvas * const scene);
    void removeScene(Canvas * const scene);

    void setCurrentScene(Canvas * const scene, QAction * const act);

    Document& mDocument;
    Canvas * mCurrentScene = nullptr;
    std::map<Canvas*, QAction*> mSceneToAct;
};

#endif // SCENECHOOSER_H
