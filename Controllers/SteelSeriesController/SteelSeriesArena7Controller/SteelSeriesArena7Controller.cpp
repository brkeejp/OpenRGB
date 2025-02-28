/*---------------------------------------------------------*\
| SteelSeriesArena7Controller.cpp                           |
|                                                           |
|   Driver for SteelSeries Arena 7                          |
|                                                           |
|   Based on SteelSeriesApex3Controller.cpp                 |
|   Updated for Arena 7 by Berk Ege C.         28.02.2025   |
|                                                           |
|   This file is part of the OpenRGB project                |
|   SPDX-License-Identifier: GPL-2.0-only                   |
\*---------------------------------------------------------*/

#include <cstring>
#include "SteelSeriesArena7Controller.h"
#include "StringUtils.h"

SteelSeriesArena7Controller::SteelSeriesArena7Controller(hid_device* dev_handle, const char* path)
{
    dev         = dev_handle;
    location    = path;
}

SteelSeriesArena7Controller::~SteelSeriesArena7Controller()
{
    hid_close(dev);
}

std::string SteelSeriesArena7Controller::GetDeviceLocation()
{
    return("HID: " + location);
}

std::string SteelSeriesArena7Controller::GetSerialString()
{
    wchar_t serial_string[128];
    int ret = hid_get_serial_number_string(dev, serial_string, 128);

    if(ret != 0)
    {
        return("");
    }

    return(StringUtils::wstring_to_string(serial_string));
}

void SteelSeriesArena7Controller::SetColor(std::vector<RGBColor> colors, uint8_t mode, uint8_t brightness)
{
    unsigned char buffer[64] = { 0x06, 0xA1 }; // Header

    // Set RGB values, mode, speed, and brightness for each zone
    for (int i = 0; i < 4; i++) // 4 zones: Left Back, Left Base, Right Back, Right Base
    {
        buffer[2 + (i * 6)] = RGBGetRValue(colors[i]);
        buffer[3 + (i * 6)] = RGBGetGValue(colors[i]);
        buffer[4 + (i * 6)] = RGBGetBValue(colors[i]);
        buffer[5 + (i * 6)] = mode;
        buffer[6 + (i * 6)] = 0x03; // Default speed (adjust as needed)
        buffer[7 + (i * 6)] = brightness;
    }

    buffer[26] = 0x0F; // Unknown byte (possibly checksum or terminator)

    // Send the packet to the device
    hid_write(dev, buffer, 64);
}

void SteelSeriesArena7Controller::Save()
{
    // Implement save functionality if supported
}

uint8_t SteelSeriesArena7Controller::GetLedCount()
{
    return 4; // 4 zones: Left Back, Left Base, Right Back, Right Base
}

uint8_t SteelSeriesArena7Controller::GetMaxBrightness()
{
    return 0x0A; // Brightness range is 0x00 to 0x0A
}

bool SteelSeriesArena7Controller::SupportsRainbowWave()
{
    return true; // Arena 7 supports Rainbow Wave mode
}

bool SteelSeriesArena7Controller::SupportsSave()
{
    return false; // Arena 7 does not support saving modes
}