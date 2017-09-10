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

class AMDA_RESTPrivate
{
public:
    AMDA_RESTPrivate()=default;
    Data get(double tstart, double tstop)
    {
        std::cout << "DL file" << std::endl;
        auto t1 = std::chrono::high_resolution_clock::now();
        auto r = cpr::Get(cpr::Url{"http://amdatest.irap.omp.eu/CU2016/data/WSRESULT/c1_b_gse-1357088772-1357515972.txt"});
        auto t2 = std::chrono::high_resolution_clock::now();
        auto file = r.text;
        auto fstr = std::stringstream(file);
        std::cout << "Done, Decoding" << std::endl;
        auto data = AMDAReader::reads(fstr);
        auto t3 = std::chrono::high_resolution_clock::now();
        auto dlduration = std::chrono::duration_cast<std::chrono::microseconds>(t2-t1).count();
        auto decodeduration = std::chrono::duration_cast<std::chrono::microseconds>(t3-t2).count();
        std::cout << "DL took " << dlduration/1000 << "ms   Decode took " << decodeduration/1000 << "ms" << std::endl;
        std::cout << "Vector size:" << data.X.size()/1000 << "Kpoints" << std::endl;
        std::cout << "Decode efficiency " << data.X.size()/(decodeduration/1000) << "Kpoints/s" << std::endl;

        return data;
    }
};

AMDA_REST::AMDA_REST()
    :impl(spimpl::make_impl<AMDA_RESTPrivate>())
{
}

Data AMDA_REST::get(double tstart, double tstop)
{
    return self().impl->get(tstart, tstop);
}
