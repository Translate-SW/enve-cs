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

#ifndef ESOUND_H
#define ESOUND_H
#include "Animators/eboxorsound.h"
#include "Animators/qrealanimator.h"
struct Samples;
class SoundReaderForMerger;

class CORE_EXPORT eSound : public eBoxOrSound {
    e_OBJECT
    e_DECLARE_TYPE(eSound)
protected:
    eSound();
public:
    virtual qreal durationSeconds() const = 0;
    virtual QrealSnapshot getVolumeSnap() const = 0;
    virtual stdsptr<Samples> getSamplesForSecond(const int relSecondId) = 0;
    virtual SoundReaderForMerger * getSecondReader(const int relSecondId) = 0;
    virtual qreal getStretch() const = 0;
    virtual qsptr<eSound> createLink() = 0;

    int durationSecondsCeil() const
    { return qCeil(durationSeconds()); }
    iValueRange absSecondToRelSeconds(const int absSecond);
    int getSampleShift() const;
    SampleRange relSampleRange() const;
    SampleRange absSampleRange() const;
protected:
    qreal getCanvasFPS() const;
private:
    iValueRange absSecondToRelSecondsAbsStretch(const int absSecond);
};

#endif // ESOUND_H
