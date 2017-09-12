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
#include <AMDA_Rest.h>
#include <cpr/cpr.h>
#include <AMDA_reader.h>
#include <sstream>
#include <iostream>
#include <chrono>
#include <date.h>
#include <math.h>

//"http://amdatest.irap.omp.eu/php/rest//getParameter.php?startTime=2013-01-02%2001:06:12&stopTime=2013-01-06%2023:46:12&parameterID=c1_b_gse&"
//http://amdatest.irap.omp.eu/php/rest//getParameter.php?startTime=2013-04-18 18:24:42.770911&stopTime=2013-04-19 18:24:42.770911&parameterID=c1_b_gse&
class AMDA_RESTPrivate
{
    inline void clean_url(std::string& str)
    {
        auto pos = str.begin();
        while(*pos != 'h' && pos!=str.end())pos++;
        str.erase(str.begin(),pos);
    }
public:
    AMDA_RESTPrivate()=default;
    Data get(double tstart, double tstop, const std::string& parameterID)
    {
        std::stringstream start;
        std::stringstream stop;
        std::chrono::seconds start_sec{static_cast<long long>(floor(tstart))};
        std::chrono::seconds stop_sec{static_cast<long long>(ceil(tstop))};
        std::chrono::system_clock::time_point start_tp{start_sec};
        std::chrono::system_clock::time_point stop_tp{stop_sec};
        using namespace date;
        start << start_tp;
        stop << stop_tp;
        auto r = cpr::Get(
            cpr::Url{"http://amdatest.irap.omp.eu/php/rest//getParameter.php"},
            cpr::Parameters{
                {"startTime", start.str()},
                {"stopTime",  stop.str()},
                {"parameterID", parameterID}
                });
        if(r.status_code == 200)
        {
            auto file = r.text;
            clean_url(file);
            r = cpr::Get(file);
            if(r.status_code == 200)
            {
                auto fstr = std::stringstream(r.text);
                return AMDAReader::reads(fstr);
            }
        }
        return Data();
    }
};

AMDA_REST::AMDA_REST()
    :impl(spimpl::make_impl<AMDA_RESTPrivate>())
{
}

Data AMDA_REST::get(double tstart, double tstop, const std::string& parameterID)
{
    return self().impl->get(tstart, tstop, parameterID);
}
