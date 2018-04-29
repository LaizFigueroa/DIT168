// Copyright (C) 2018 DIT168 - Group 13
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.
//
//  Created by Laiz Figueroa on 2018-04-28.

#ifndef imu_hpp
#define imu_hpp

#include <stdio.h>
#include "cluon/OD4Session.hpp"
#include "cluon/Envelope.hpp"
#include "messages.hpp" 

extern "C"{
#include <roboticscape.h>
}

/********************************************/
/** INTERNAL COMMUNICATIONS *****************/
/********************************************/

static const int IMU_CHANNEL    = 243;
static const int INTERNAL_CHANNEL    = 240;

class Imu {
private:
    std::shared_ptr<cluon::OD4Session>  imu;
    std::shared_ptr<cluon::OD4Session>  internal;

}

#endif /* imu_hpp */
