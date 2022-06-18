#ifndef DATAHANDLER_H
#define DATAHANDLER_H


class DataKeeper
{
public:
    DataKeeper();
    ~DataKeeper();

    DataKeeper(const DataKeeper& dataKeeper);

    DataKeeper& operator=(const DataKeeper& dataKeeper);

    bool isEmpty()
    {
        return ((m_dayLight == 0) &&
                (m_nightLight == 0) &&
                (m_coldWater == 0) &&
                (m_coldWater2 == 0) &&
                (m_hotWater == 0) &&
                (m_gaz == 0));
    }

    void setDayLight(const int& dayLight) { m_dayLight = dayLight; }
    int dayLight() const { return m_dayLight; }

    void setNightLight(const int& nightLight) { m_nightLight = nightLight; }
    int nightLight() const { return m_nightLight; }

    void setColdWater(const int& coldWater) { m_coldWater = coldWater; }
    int coldWater() const { return m_coldWater; }

    void setColdWater2(const int& coldWater2) { m_coldWater2 = coldWater2; }
    int coldWater2() const { return m_coldWater2; }

    void setHotWater(const int& hotWater) { m_hotWater = hotWater; }
    int hotWater() const { return m_hotWater; }

    void setGaz(const int& gaz) { m_gaz = gaz; }
    int gaz() const { return m_gaz; }

    void clear();

private:
    int m_dayLight;
    int m_nightLight;
    int m_coldWater;
    int m_coldWater2;
    int m_hotWater;
    int m_gaz;

};

#endif // DATAHANDLER_H
