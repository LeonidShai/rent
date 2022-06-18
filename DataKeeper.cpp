#include "DataKeeper.h"

DataKeeper::DataKeeper():
    m_dayLight(0),
    m_nightLight(0),
    m_coldWater(0),
    m_coldWater2(0),
    m_hotWater(0),
    m_gaz(0)
{

}

DataKeeper::~DataKeeper()
{

}

DataKeeper::DataKeeper(const DataKeeper &dataKeeper)
{
    m_dayLight = dataKeeper.m_dayLight;
    m_nightLight = dataKeeper.m_nightLight;
    m_coldWater = dataKeeper.m_coldWater;
    m_coldWater2 = dataKeeper.m_coldWater2;
    m_hotWater = dataKeeper.m_hotWater;
    m_gaz = dataKeeper.m_gaz;
}

DataKeeper &DataKeeper::operator=(const DataKeeper &dataKeeper)
{
    if (this != &dataKeeper)
    {
        m_dayLight = dataKeeper.m_dayLight;
        m_nightLight = dataKeeper.m_nightLight;
        m_coldWater = dataKeeper.m_coldWater;
        m_coldWater2 = dataKeeper.m_coldWater2;
        m_hotWater = dataKeeper.m_hotWater;
        m_gaz = dataKeeper.m_gaz;
    }
    return *this;
}

void DataKeeper::clear()
{
    m_dayLight = 0;
    m_nightLight = 0;
    m_coldWater = 0;
    m_coldWater2 = 0;
    m_hotWater = 0;
    m_gaz = 0;
}
