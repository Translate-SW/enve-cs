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

#include "namefixer.h"

#include "Properties/property.h"

QString NameFixer::stringScrapEndDigits(const QString &string) {
    const QRegExp endNumbers(QStringLiteral("[0-9]+$"));
    const int endNumbersIndex = endNumbers.indexIn(string);
    QString trimmedName;
    if(endNumbersIndex >= 0) {
        return string.mid(0, endNumbersIndex);
    } else {
        return string;
    }
}

QString NameFixer::makeNameUnique(const QString &name,
                                  const NamesGetter &namesGetter) {
    const QString fixedBaseName = Property::prp_sFixName(name);
    const QString trimmedName = stringScrapEndDigits(fixedBaseName).trimmed();
    const QString fixedName = Property::prp_sFixName(trimmedName);
    const QStringList usedList = namesGetter(fixedName);
    if(!usedList.contains(fixedBaseName)) return fixedBaseName;
    for(int i = 0;; i++) {
        const QString suffix = " " + QString::number(i);
        const QString testName = fixedName + suffix;
        const bool taken = usedList.contains(testName);
        if(!taken) return testName;
    }
}
