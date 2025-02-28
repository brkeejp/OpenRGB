/*---------------------------------------------------------*\
| RGBController_SteelSeriesArena7.h                         |
|                                                           |
|   RGBController for SteelSeries Arena 7                   |
|                                                           |
|   Based on RGBController_SteelSeriesApex3.h               |
|   Updated for Arena 7 by Berk Ege C.         28.02.2025   |
|                                                           |
|   This file is part of the OpenRGB project                |
|   SPDX-License-Identifier: GPL-2.0-only                   |
\*---------------------------------------------------------*/

#pragma once

#include "RGBController.h"
#include "SteelSeriesArena7Controller.h"

enum class ARENA7_MODES
{
    DIRECT          = 0,
    RAINBOW_WAVE    = 1
};

class RGBController_SteelSeriesArena7 : public RGBController
{
public:
    RGBController_SteelSeriesArena7(SteelSeriesArena7Controller* controller_ptr);
    ~RGBController_SteelSeriesArena7();

    void        SetupZones();
    void        ResizeZone(int zone, int new_size);

    void        DeviceUpdateLEDs();
    void        UpdateZoneLEDs(int zone);
    void        UpdateSingleLED(int led);

    void        DeviceUpdateMode();
    void        DeviceSaveMode();

private:
    SteelSeriesArena7Controller*     controller;
};