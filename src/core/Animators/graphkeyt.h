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

#ifndef GRAPHKEYT_H
#define GRAPHKEYT_H
#include "basedkeyt.h"
#include "graphkey.h"

template <typename T>
class GraphKeyT : public BasedKeyT<GraphKey, T> {
    e_OBJECT
protected:
    using BasedKeyT<GraphKey, T>::BasedKeyT;
};

#endif // GRAPHKEYT_H
