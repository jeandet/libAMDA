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
#include <utility>
#include <memory>
#include <date.h>
#include <sstream>
#include <random>


namespace {
class RandomAMDA : public ::testing::TestWithParam<int>
{
protected:
    RandomAMDA() {
        // You can do set-up work for each test here.
    }

    virtual ~RandomAMDA() {
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

const std::vector<int> testInputs(100);


TEST_P(RandomAMDA, randomGet)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, 24*365*2);
    std::istringstream sstart{ "2012-01-01 18:24:42.770911"};
    std::chrono::system_clock::time_point start;
    std::chrono::system_clock::time_point stop;
    sstart >> date::parse("%Y-%m-%d %T", start);
    start += std::chrono::hours(dis(gen));
    stop = start + std::chrono::hours(5*24);
    using namespace date;
    std::cout << start << " " << stop << std::endl;
    //auto data_ref = AMDA_REST::get(start, stop, "c1_b_gse");
}


INSTANTIATE_TEST_CASE_P(random,RandomAMDA,::testing::ValuesIn(testInputs));


int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

