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

#ifndef ACTION_H
#define ACTION_H

#include "core_global.h"

#include <QObject>
#include <functional>
#include <QAction>

class CORE_EXPORT Action : public QObject {
    Q_OBJECT
public:
    explicit Action(const std::function<bool()>& canExecuteFunc,
                    const std::function<void()>& executeFunc,
                    const std::function<QString()>& textFunc,
                    QObject *parent = nullptr);
    explicit Action(const std::function<bool()>& canExecuteFunc,
                    const std::function<void()>& executeFunc,
                    const QString& textVal,
                    QObject *parent = nullptr);

    const std::function<bool()> canExecute;
    const std::function<void()> execute;
    const std::function<QString()> text;

    void connect(QAction* const action);

    void operator()() const { if(canExecute()) execute(); }

    void raiseCanExecuteChanged()
    { emit canExecuteChanged(canExecute()); }
    void raiseTextChanged()
    { emit textChanged(text()); }
signals:
    void canExecuteChanged(bool can);
    void textChanged(const QString& text);
};

class CORE_EXPORT UndoableAction : public Action {
public:
    explicit UndoableAction(const std::function<bool()>& canExecuteFunc,
                            const std::function<void()>& executeFunc,
                            const std::function<QString()>& textFunc,
                            const std::function<void(const QString&)>& pushNameFunc,
                            QObject *parent = nullptr);
    explicit UndoableAction(const std::function<bool()>& canExecuteFunc,
                            const std::function<void()>& executeFunc,
                            const QString& textVal,
                            const std::function<void(const QString&)>& pushNameFunc,
                            QObject *parent = nullptr);
};

#endif // ACTION_H
