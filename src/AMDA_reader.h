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
#ifndef AMDA_READER_H
#define AMDA_READER_H

#include <spimpl.h>
#include <data.h>
#include <string>

class AMDAReaderPrivate;
class AMDAReader
{
public:
    AMDAReader(AMDAReader const&) = delete;
    AMDAReader(AMDAReader&&) = delete;
    AMDAReader& operator=(AMDAReader const&) = delete;
    AMDAReader& operator=(AMDAReader &&) = delete;

    static Data readf(const std::string& fname);
    static Data reads(std::istream& file);

private:
    AMDAReader();
    static AMDAReader& self()
    {
        static AMDAReader dl;
        return dl;
    }
    spimpl::impl_ptr<AMDAReaderPrivate> impl;
};

#endif
