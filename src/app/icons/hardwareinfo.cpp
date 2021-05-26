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

#include "hardwareinfo.h"

#include <QThread>

#include "exceptions.h"

#if defined(Q_OS_WIN)
    #include "windowsincludes.h"
#elif defined(Q_OS_MACOS)
    #include <sys/types.h>
    #include <sys/sysctl.h>
#endif

int HardwareInfo::mCpuThreads = -1;

intKB HardwareInfo::mRamKB(0);

GpuVendor HardwareInfo::mGpuVendor = GpuVendor::unrecognized;

intKB getTotalRamBytes() {
#if defined(Q_OS_WIN)
    MEMORYSTATUSEX statex;
    statex.dwLength = sizeof (statex);
    GlobalMemoryStatusEx(&statex);
    const longB totalBytes(statex.ullTotalPhys);
    return intKB(totalBytes);
#elif defined(Q_OS_LINUX)
    FILE * const meminfo = fopen("/proc/meminfo", "r");
    if(meminfo) {
        char line[256];

        while(fgets(line, sizeof(line), meminfo)) {
            intKB memTotal(0);
            if(sscanf(line, "MemTotal: %d kB", &memTotal.fValue) == 1) {
                fclose(meminfo);
                return memTotal;
            }
        }
        fclose(meminfo);
        RuntimeThrow("'MemTotal' missing from /proc/meminfo");
    }
    RuntimeThrow("Failed to open /proc/meminfo");
#elif defined(Q_OS_MACOS)
    int mib [] = { CTL_HW, HW_MEMSIZE };
    int64_t bytes = 0;
    size_t length = sizeof(bytes);
    const int ret = sysctl(mib, 2, &bytes, &length, NULL, 0);
    if(ret) RuntimeThrow("Failed to retrieve memory using sysctl");
    return intKB(longB(bytes));
#endif
}

#include "Private/Tasks/offscreenqgl33c.h"

GpuVendor gpuVendor() {
    OffscreenQGL33c gl;
    gl.initialize();
    gl.makeCurrent();
    const QString vendor(reinterpret_cast<const char*>(gl.glGetString(GL_VENDOR)));
    const QString renderer(reinterpret_cast<const char*>(gl.glGetString(GL_RENDERER)));
    const QString version(reinterpret_cast<const char*>(gl.glGetString(GL_VERSION)));
    gl.doneCurrent();
    const auto checkVendor = [&vendor, &renderer, &version](const QString& str) {
        return vendor.contains(str, Qt::CaseInsensitive) ||
               renderer.contains(str, Qt::CaseInsensitive) ||
               version.contains(str, Qt::CaseInsensitive);
    };

    if(checkVendor("nvidia") || checkVendor("nouveau")) return GpuVendor::nvidia;
    if(checkVendor("intel")) return GpuVendor::intel;
    if(checkVendor("amd") || checkVendor("ati") ||
       checkVendor("advanced micro devices")) {
        return GpuVendor::amd;
    }
    return GpuVendor::unrecognized;
}

void HardwareInfo::sUpdateInfo() {
    mCpuThreads = QThread::idealThreadCount();
    mRamKB = getTotalRamBytes();
    mGpuVendor = gpuVendor();
}
