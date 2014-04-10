/******************************************************************************
* Copyright (c) 2014, Peter J. Gadomski (pete.gadomski@gmail.com)
*
* All rights reserved.
*
* Redistribution and use in source and binary forms, with or without
* modification, are permitted provided that the following
* conditions are met:
*
*     * Redistributions of source code must retain the above copyright
*       notice, this list of conditions and the following disclaimer.
*     * Redistributions in binary form must reproduce the above copyright
*       notice, this list of conditions and the following disclaimer in
*       the documentation and/or other materials provided
*       with the distribution.
*     * Neither the name of Hobu, Inc. or Flaxen Geo Consulting nor the
*       names of its contributors may be used to endorse or promote
*       products derived from this software without specific prior
*       written permission.
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
* "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
* LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
* FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
* COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
* INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
* BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS
* OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
* AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
* OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
* OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY
* OF SUCH DAMAGE.
****************************************************************************/

#ifndef INCLUDED_DRIVERS_SBET_READER_HPP
#define INCLUDED_DRIVERS_SBET_READER_HPP

#include <pdal/PointBuffer.hpp>
#include <pdal/Reader.hpp>
#include <pdal/ReaderIterator.hpp>


namespace pdal
{
namespace drivers
{
namespace sbet
{


typedef struct
{
    double time;
    double latitude;
    double longitude;
    double altitude;
    double x_velocity;
    double y_velocity;
    double z_velocity;
    double roll;
    double pitch;
    double platform_heading;
    double wander_angle;
    double x_body_accel;
    double y_body_accel;
    double z_body_accel;
    double x_body_ang_rate;
    double y_body_ang_rate;
    double z_body_ang_rate;
} Record;


class PDAL_DLL Reader : public pdal::Reader
{
public:
    SET_STAGE_NAME("drivers.sbet.reader", "SBET Reader")
    SET_STAGE_LINK("http://pdal.io/stages/drivers.sbet.reader.html")

    Reader(const Options&);
    ~Reader();

    virtual void initialize();
    static Options getDefaultOptions();
    static std::vector<Dimension> getDefaultDimensions();

    std::string getFileName() const;

    pdal::StageSequentialIterator* createSequentialIterator(PointBuffer&) const;

}; // class Reader


namespace iterators
{
namespace sequential
{


class PDAL_DLL Iterator : public pdal::ReaderSequentialIterator
{
public:
    Iterator(const pdal::drivers::sbet::Reader&, PointBuffer&);
    ~Iterator();

private:
    boost::uint64_t skipImpl(boost::uint64_t);
    boost::uint32_t readBufferImpl(PointBuffer&);
    bool atEndImpl() const;

    std::istream* m_istream;
    const boost::uint64_t m_numPoints;
    const Schema m_schema;
    PointBuffer m_buffer;
};

}
} // namespace iterators::sequential

}
}
} // namespace pdal::drivers::sbet


#endif // INCLUDED_DRIVERS_SBET_READER_HPP
