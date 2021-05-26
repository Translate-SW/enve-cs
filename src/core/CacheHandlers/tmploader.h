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

#ifndef TMPLOADER_H
#define TMPLOADER_H
#include "Tasks/updatable.h"
#include <QTemporaryFile>
#include "hddcachablecont.h"

class CORE_EXPORT TmpLoader : public eHddTask {
public:
    TmpLoader(const qsptr<QTemporaryFile> &file,
              HddCachableCont * const target);

    virtual void read(eReadStream& src) = 0;
    void process();
    void beforeProcessing(const Hardware);
private:
    qsptr<QTemporaryFile> mTmpFile;
    const stdptr<HddCachableCont> mTarget;
};

#endif // TMPLOADER_H
