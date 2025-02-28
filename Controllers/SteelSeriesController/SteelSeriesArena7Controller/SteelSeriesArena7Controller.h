/*---------------------------------------------------------*\
| SteelSeriesArena7Controller.h                             |
|                                                           |
|   Driver for SteelSeries Arena 7                          |
|                                                           |
|   Based on SteelSeriesApex3Controller.h                   |
|   Updated for Arena 7 by Berk Ege C.         28.02.2025   |
|                                                           |
|   This file is part of the OpenRGB project                |
|   SPDX-License-Identifier: GPL-2.0-only                   |
\*---------------------------------------------------------*/

#pragma once

#include <string>
#include <hidapi.h>
#include "RGBController.h"
#include "SteelSeriesGeneric.h"

#define STEELSERIES_ARENA7_BRIGHTNESS_MIN    0x00
#define STEELSERIES_ARENA7_HID_TIMEOUT       100

class SteelSeriesArena7Controller
{
public:
    SteelSeriesArena7Controller(hid_device* dev_handle, const char* path);
    virtual ~SteelSeriesArena7Controller();

    std::string         GetDeviceLocation();
    std::string         GetSerialString();
    steelseries_type    GetDeviceType();

    void                SetColor(std::vector<RGBColor> colors, uint8_t mode, uint8_t brightness);
    void                Save();
    uint8_t             GetLedCount();
    uint8_t             GetMaxBrightness();
    bool                SupportsRainbowWave();
    bool                SupportsSave();

    hid_device*         dev;

private:
    std::string         location;
};
