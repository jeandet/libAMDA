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

class AMDA_RESTPrivate;

class AMDA_REST
{
public:
    AMDA_REST(AMDA_REST const&) = delete;
    AMDA_REST(AMDA_REST&&) = delete;
    AMDA_REST& operator=(AMDA_REST const&) = delete;
    AMDA_REST& operator=(AMDA_REST &&) = delete;

    static Data get(double tstart, double tstop, const std::string& parameterID);
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
