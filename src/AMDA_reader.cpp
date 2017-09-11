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
#include <AMDA_reader.h>
#include <fstream>
#include <iostream>
#include <time.h>
#include <sstream>
#include <chrono>
#include <date.h>
#define likely(x)      __builtin_expect(!!(x), 1)
#define unlikely(x)    __builtin_expect(!!(x), 0)
class AMDAReaderPrivate
{
public:
    AMDAReaderPrivate()=default;

    Data reads(std::istream& file)
    {
        std::unordered_map<std::string,std::string> metadata;
        Data data;
        std::string line;
        do
        {
            std::getline(file,line);
            if(line[0]=='#')
            {
                parse_metadata(metadata,line);
            }
        }while(!file.eof() && line[0]=='#');

        auto data_columns = metadata["DATA_COLUMNS"];
        data.NDims = std::count(data_columns.begin(), data_columns.end(), ',')-1;
        data.metadata = std::move(metadata);
        std::string time;
        double X,Y,Z;
        while(1)
        {
            std::stringstream linestream(line);
            std::chrono::system_clock::time_point tp;
            linestream >> date::parse("%Y-%m-%dT%T", tp); //slow
            linestream >> X >> Y >> Z;
            data.Values.push_back(X);
            data.Values.push_back(Y);
            data.Values.push_back(Z);
            data.X.push_back(std::chrono::duration<double>(tp.time_since_epoch()).count() );
            if(unlikely(file.eof()))//I don't like this...
                break;
            std::getline(file,line);//slow
        }
        return data;
    }

    Data readf(const std::string& fname)
    {
        std::ifstream file(fname);
        if(file.is_open())
        {
            return reads(file);
        }
        return Data();
    }

private:
    inline void strip(std::string& str)
    {
        auto end_pos = std::remove(str.begin(), str.end(), ' ');
        str.erase(end_pos, str.end());
    }

    void parse_metadata(std::unordered_map<std::string,std::string>& metadata, const std::string& line)
    {
        auto pos = line.find(':');
        if(std::string::npos != pos)
        {
            auto key = line.substr(1,pos);
            auto value = line.substr(pos+1);
            strip(key);
            strip(value);
            if(value.size()>0)
                metadata[key] = value;
        }
    }
};

AMDAReader::AMDAReader()
    :impl(spimpl::make_impl<AMDAReaderPrivate>())
{
}

Data AMDAReader::readf(const std::string& fname)
{
    return self().impl->readf(fname);
}

Data AMDAReader::reads(std::istream& file)
{
    return self().impl->reads(file);
}
