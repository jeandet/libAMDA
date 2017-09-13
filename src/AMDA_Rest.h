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
#ifndef AMDA_REST_H
#define AMDA_REST_H

#include <spimpl.h>
#include <data.h>
#include <string>
#include <chrono>

class AMDA_RESTPrivate;

class AMDA_REST
{
public:
    AMDA_REST(AMDA_REST const&) = delete;
    AMDA_REST(AMDA_REST&&) = delete;
    AMDA_REST& operator=(AMDA_REST const&) = delete;
    AMDA_REST& operator=(AMDA_REST &&) = delete;

    static Data get(double tstart, double tstop, const std::string& parameterID);
    static Data get(const std::chrono::system_clock::time_point& tstart, const std::chrono::system_clock::time_point& tstop, const std::string& parameterID)
        {
            return AMDA_REST::get(
                                    std::chrono::duration<double>(tstart.time_since_epoch()).count(),
                                    std::chrono::duration<double>(tstop.time_since_epoch()).count(),
                                    parameterID
                                   );
        }
private:
    AMDA_REST();
    static AMDA_REST& self()
    {
        static AMDA_REST dl;
        return dl;
    }
    spimpl::impl_ptr<AMDA_RESTPrivate> impl;
};

#endif
