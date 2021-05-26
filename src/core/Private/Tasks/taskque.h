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

#ifndef TASKQUE_H
#define TASKQUE_H
#include "Tasks/updatable.h"

class CORE_EXPORT TaskQue {
    friend class TaskQueHandler;
public:
    explicit TaskQue();
    TaskQue(const TaskQue&) = delete;
    TaskQue& operator=(const TaskQue&) = delete;

    ~TaskQue();
protected:
    int countQued() const;
    bool allDone() const;
    void addTask(const stdsptr<eTask>& task);

    stdsptr<eTask> takeQuedForCpuProcessing();
    stdsptr<eTask> takeQuedForGpuProcessing();
private:
    QList<stdsptr<eTask>> mGpuOnly;
    QList<stdsptr<eTask>> mGpuPreffered;
    QList<stdsptr<eTask>> mCpuPreffered;
    QList<stdsptr<eTask>> mCpuOnly;
};
#endif // TASKQUE_H
