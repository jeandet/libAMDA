/*------------------------------------------------------------------------------
--  This file is a part of the AMDA library
--  Copyright (C) 2017, Plasma Physics Laboratory - CNRS
--
--  This program is free software; you can redistribute it and/or modify
--  it under the terms of the GNU General Public License as published by
--  the Free Software Foundation; either version 2 of the License, or
--  (at your option) any later version.
--
--  This program is distributed in the hope that it will be useful,
--  but WITHOUT ANY WARRANTY; without even the implied warranty of
--  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
--  GNU General Public License for more details.
--
--  You should have received a copy of the GNU General Public License
--  along with this program; if not, write to the Free Software
--  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
-------------------------------------------------------------------------------*/
/*--                  Author : Alexis Jeandet
--                     Mail : alexis.jeandet@member.fsf.org
----------------------------------------------------------------------------*/
#include "gtest/gtest.h"
#include "AMDA_Rest.h"
#include <vector>
#include <date.h>
#include <sstream>


namespace {
class SimpleREST : public ::testing::Test
{
protected:
    SimpleREST() {
        // You can do set-up work for each test here.
    }

    virtual ~SimpleREST() {
        // You can do clean-up work that doesn't throw exceptions here.
    }

    // If the constructor and destructor are not enough for setting up
    // and cleaning up each test, you can define the following methods:

    virtual void SetUp() {
        // Code here will be called immediately after the constructor (right
        // before each test).
    }

    virtual void TearDown() {
        // Code here will be called immediately after each test (right
        // before the destructor).
    }
};
};

TEST_F(SimpleREST, vector)
{
    std::istringstream sstart{ "2013-04-18 18:24:42.770911"};
    std::istringstream sstop{"2013-04-19 19:24:42.770911" };
    std::chrono::system_clock::time_point start;
    std::chrono::system_clock::time_point stop;
    sstart >> date::parse("%Y-%m-%d %T", start);
    sstop >> date::parse("%Y-%m-%d %T", stop);
    auto data = AMDA_REST::get(
        std::chrono::duration<double>(start.time_since_epoch()).count(),
        std::chrono::duration<double>(stop.time_since_epoch()).count(),
        "c1_b_gse"
        );
}



int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

