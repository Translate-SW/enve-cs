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

#ifndef SAMPLES_H
#define SAMPLES_H
#include "smartPointers/stdselfref.h"
#include "smartPointers/ememory.h"
#include "framerange.h"
extern "C" {
    #include <libavutil/samplefmt.h>
    #include <libavutil/channel_layout.h>
}

class eWriteStream;
class eReadStream;

struct CORE_EXPORT Samples : public StdSelfRef {
    e_OBJECT
protected:
    Samples(uchar ** const data,
            const SampleRange& range,
            const int sampleRate,
            const AVSampleFormat format,
            const uint64_t channelLayout) :
        fFormat(format),
        fPlanar(av_sample_fmt_is_planar(format)),
        fSampleRate(sampleRate),
        fSampleSize(uint(av_get_bytes_per_sample(format))),
        fChannelLayout(channelLayout),
        fNChannels(av_get_channel_layout_nb_channels(channelLayout)),
        fSampleRange(range), fData(data) {
    }

    Samples(const SampleRange& range,
            const int sampleRate,
            const AVSampleFormat format,
            const uint64_t channelLayout) :
        fFormat(format),
        fPlanar(av_sample_fmt_is_planar(format)),
        fSampleRate(sampleRate),
        fSampleSize(uint(av_get_bytes_per_sample(format))),
        fChannelLayout(channelLayout),
        fNChannels(av_get_channel_layout_nb_channels(channelLayout)),
        fSampleRange(range) {
        const auto bytes = static_cast<ulong>(fSampleRange.span())*fSampleSize;
        if(fPlanar) {
            fData = new uchar*[fNChannels];
            for(uint i = 0; i < fNChannels; i++) {
                fData[i] = new uchar[bytes];
            }
        } else {
            fData = new uchar*[1];
            const auto totBytes = bytes * fNChannels;
            fData[0] = new uchar[totBytes];
        }
    }

    Samples(const Samples * const src) :
        Samples(nullptr, src->fSampleRange, src->fSampleRate,
                src->fFormat, src->fChannelLayout) {
        const auto bytes = static_cast<ulong>(fSampleRange.span())*fSampleSize;
        if(fPlanar) {
            fData = new uchar*[fNChannels];
            for(uint i = 0; i < fNChannels; i++) {
                fData[i] = new uchar[bytes];
                memcpy(fData[i], src->fData[i], bytes);
            }
        } else {
            fData = new uchar*[1];
            const auto totBytes = bytes * fNChannels;
            fData[0] = new uchar[totBytes];
            memcpy(fData[0], src->fData[0], totBytes);
        }
    }

    Samples(const stdsptr<Samples>& src) : Samples(src.get()) {}
public:
    ~Samples() {
        if(fPlanar) {
            for(uint i = 0; i < fNChannels; i++)
                delete[] fData[i];
        } else {
            delete[] fData[0];
        }
        delete[] fData;
    }

    void zeroAll() {
        const uint nSamples = uint(fSampleRange.span());
        if(fFormat == AV_SAMPLE_FMT_U8) {
            const uchar val = 127;
            uint iMax = nSamples*fNChannels;
            for(uint i = 0; i < iMax; i++) {
                fData[0][i] = val;
            }
        } else if(fFormat == AV_SAMPLE_FMT_U8P) {
            const uchar val = 127;
            for(uint i = 0; i < nSamples; i++) {
                for(uint j = 0; j < fNChannels; j++) {
                    fData[j][i] = val;
                }
            }
        } else {
            const auto bytes = static_cast<ulong>(nSamples)*fSampleSize;
            if(fPlanar) {
                for(uint i = 0; i < fNChannels; i++)
                    memset(fData[i], 0, bytes);
            } else {
                memset(fData[0], 0, bytes * fNChannels);
            }
        }
    }

    const AVSampleFormat fFormat;
    const bool fPlanar;
    const int fSampleRate;
    const uint fSampleSize;
    const uint64_t fChannelLayout;
    const uint fNChannels;
    const SampleRange fSampleRange;
    uchar ** fData;

    stdsptr<Samples> mid(const SampleRange& range) const {
        if(!range.isValid()) RuntimeThrow("Invalid range");
        if(range.fMin < fSampleRange.fMin ||
           range.fMax > fSampleRange.fMax)
            RuntimeThrow("Range outside bounds");
        const uint displ =  uint(range.fMin - fSampleRange.fMin) * fSampleSize;
        uchar **data = nullptr;
        const auto bytes = static_cast<ulong>(range.span())*fSampleSize;
        if(fPlanar) {
           data = new uchar*[fNChannels];
            for(uint i = 0; i < fNChannels; i++) {
                data[i] = new uchar[bytes];
                memcpy(data[i], fData[i] + displ, bytes);
            }
        } else {
            data = new uchar*[1];
            const auto totBytes = bytes * fNChannels;
            data[0] = new uchar[totBytes];
            memcpy(data[0], fData[0] + displ * fNChannels, totBytes);
        }

        return enve::make_shared<Samples>(data, range, fSampleRate,
                                          fFormat, fChannelLayout);
    }

    void write(eWriteStream& dst) const;

    static stdsptr<Samples> sRead(eReadStream& src);
};

#endif // SAMPLES_H
