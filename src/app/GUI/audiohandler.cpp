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

#include "audiohandler.h"
#include "Sound/soundcomposition.h"

#include <iostream>

AudioHandler* AudioHandler::sInstance = nullptr;

AudioHandler::AudioHandler() {
    Q_ASSERT(!sInstance);
    sInstance = this;
}

const int BufferSize = 32768;

QAudioFormat::SampleType toQtAudioFormat(const AVSampleFormat avFormat) {
    if(avFormat == AV_SAMPLE_FMT_S32) {
        return QAudioFormat::SignedInt;
    } else if(avFormat == AV_SAMPLE_FMT_FLT) {
        return QAudioFormat::Float;
    } else RuntimeThrow("Unsupported sample format " +
                        av_get_sample_fmt_name(avFormat));
}

AVSampleFormat toAVAudioFormat(const QAudioFormat::SampleType qFormat) {
    if(qFormat == QAudioFormat::SignedInt) {
        return AV_SAMPLE_FMT_S32;
    } else if(qFormat == QAudioFormat::Float) {
        return AV_SAMPLE_FMT_FLT;
    } else RuntimeThrow("Unsupported sample format " +
                        QString::number(qFormat));
}

void AudioHandler::initializeAudio(eSoundSettingsData& soundSettings) {
    if(mAudioOutput) delete mAudioOutput;

    mAudioBuffer = QByteArray(BufferSize, 0);

    mAudioDevice = QAudioDeviceInfo::defaultOutputDevice();
    mAudioFormat.setSampleRate(soundSettings.fSampleRate);
    mAudioFormat.setChannelCount(soundSettings.channelCount());
    mAudioFormat.setSampleSize(8*soundSettings.bytesPerSample());
    mAudioFormat.setCodec("audio/pcm");
    mAudioFormat.setByteOrder(QAudioFormat::LittleEndian);
    mAudioFormat.setSampleType(toQtAudioFormat(soundSettings.fSampleFormat));

    QAudioDeviceInfo info(mAudioDevice);
    if(!info.isFormatSupported(mAudioFormat)) {
        const auto oldFormat = mAudioFormat;
        mAudioFormat = info.nearestFormat(mAudioFormat);
        std::cout << "Using:" << std::endl <<
                     "    Sample rate: " << mAudioFormat.sampleRate() << std::endl <<
                     "    Channel count: " << mAudioFormat.channelCount() << std::endl <<
                     "    Sample size: " << mAudioFormat.sampleSize() << std::endl <<
                     "    Codec: " << mAudioFormat.codec().toStdString() << std::endl <<
                     "    Sample Type: " << mAudioFormat.sampleType() << std::endl <<
                     "    Byte order: " << mAudioFormat.byteOrder() << std::endl;
        soundSettings.fSampleRate = mAudioFormat.sampleRate();
        soundSettings.fSampleFormat = toAVAudioFormat(mAudioFormat.sampleType());
    }

    mAudioOutput = new QAudioOutput(mAudioDevice, mAudioFormat, this);
    mAudioOutput->setNotifyInterval(128);
}

void AudioHandler::startAudio() {
    mAudioIOOutput = mAudioOutput->start();
}

void AudioHandler::pauseAudio() {
    mAudioOutput->suspend();
}

void AudioHandler::resumeAudio() {
    mAudioOutput->resume();
}

void AudioHandler::stopAudio() {
    //mAudioOutput->suspend();
    //mCurrentSoundComposition->stop();
    mAudioIOOutput = nullptr;
    mAudioOutput->stop();
    mAudioOutput->reset();
}

void AudioHandler::setVolume(const int value) {
    if(mAudioOutput) mAudioOutput->setVolume(qreal(value)/100);
}
