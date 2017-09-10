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
            linestream >> date::parse("%Y-%m-%dT%T", tp);
            linestream >> X >> Y >> Z;
            data.Values.push_back(X);
            data.Values.push_back(Y);
            data.Values.push_back(Z);
            data.X.push_back(std::chrono::duration<double>(tp.time_since_epoch()).count() );
            //data.X.push_back(decodeTimeFromEpoch(time));
            if(file.eof())
                break;
            std::getline(file,line);
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

    inline double decodeTimeFromEpoch(const std::string& time)
    {
        struct tm t;
        time_t t_of_day;
        t.tm_year=(1000*(time[0] & 0x0F)) + (100*(time[1] & 0x0F)) + (10*(time[2] & 0x0F)) + ((time[3] & 0x0F)) -1900;
        t.tm_mon=(10*(time[5] & 0x0F)) + ((time[6] & 0x0F));
        t.tm_mday=(10*(time[8] & 0x0F)) + ((time[9] & 0x0F));
        t.tm_hour=(10*(time[11] & 0x0F)) + ((time[12] & 0x0F));
        t.tm_min=(10*(time[14] & 0x0F)) + ((time[15] & 0x0F));
        t.tm_sec=(10*(time[17] & 0x0F)) + ((time[18] & 0x0F));
        double ms=(100*(time[20] & 0x0F)) + (10*(time[21] & 0x0F)) + ((time[22] & 0x0F));
        t_of_day = mktime(&t);
        return (double)t_of_day+((double)ms*(double)0.001);
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
