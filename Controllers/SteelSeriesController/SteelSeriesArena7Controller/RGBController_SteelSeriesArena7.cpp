/*---------------------------------------------------------*\
| RGBController_SteelSeriesArena7.cpp                       |
|                                                           |
|   RGBController for SteelSeries Arena 7                   |
|                                                           |
|   Based on RGBController_SteelSeriesApex3.cpp             |
|   Updated for Arena 7 by Berk Ege C.         28.02.2025   |
|                                                           |
|   This file is part of the OpenRGB project                |
|   SPDX-License-Identifier: GPL-2.0-only                   |
\*---------------------------------------------------------*/

#include "RGBController_SteelSeriesArena7.h"

/**------------------------------------------------------------------*\
    @name SteelSeries Arena 7
    @category Speaker
    @type USB
    @save :x:
    @direct :white_check_mark:
    @effects :white_check_mark:
    @detectors DetectSteelSeriesArena7
    @comment
\*-------------------------------------------------------------------*/

RGBController_SteelSeriesArena7::RGBController_SteelSeriesArena7(SteelSeriesArena7Controller* controller_ptr)
{
    controller              = controller_ptr;

    name                    = "SteelSeries Arena 7 Device";
    vendor                  = "SteelSeries";
    type                    = DEVICE_TYPE_SPEAKER;
    description             = name;
    location                = controller->GetDeviceLocation();
    serial                  = controller->GetSerialString();

    // Add default modes
    mode Off;
    Off.name                = "Off";
    Off.value               = 0x00;
    Off.flags               = MODE_FLAG_HAS_BRIGHTNESS;
    Off.color_mode          = MODE_COLORS_NONE;
    Off.brightness_min      = STEELSERIES_ARENA7_BRIGHTNESS_MIN;
    Off.brightness_max      = controller->GetMaxBrightness();
    Off.brightness          = Off.brightness_max;
    Off.speed_min           = 0;
    Off.speed_max           = 0;
    Off.speed               = 0;
    Off.colors_min          = 0;
    Off.colors_max          = 0;
    Off.direction           = 0;
    modes.push_back(Off);

    mode Solid;
    Solid.name              = "Solid";
    Solid.value             = 0x01;
    Solid.flags             = MODE_FLAG_HAS_PER_LED_COLOR | MODE_FLAG_HAS_BRIGHTNESS;
    Solid.color_mode        = MODE_COLORS_PER_LED;
    Solid.brightness_min    = STEELSERIES_ARENA7_BRIGHTNESS_MIN;
    Solid.brightness_max    = controller->GetMaxBrightness();
    Solid.brightness        = Solid.brightness_max;
    Solid.speed_min         = 0;
    Solid.speed_max         = 0;
    Solid.speed             = 0;
    Solid.colors_min        = 1;
    Solid.colors_max        = 1;
    Solid.direction         = 0;
    modes.push_back(Solid);

    mode Breathe;
    Breathe.name            = "Breathe";
    Breathe.value           = 0x02;
    Breathe.flags           = MODE_FLAG_HAS_PER_LED_COLOR | MODE_FLAG_HAS_BRIGHTNESS | MODE_FLAG_HAS_SPEED;
    Breathe.color_mode      = MODE_COLORS_PER_LED;
    Breathe.brightness_min  = STEELSERIES_ARENA7_BRIGHTNESS_MIN;
    Breathe.brightness_max  = controller->GetMaxBrightness();
    Breathe.brightness      = Breathe.brightness_max;
    Breathe.speed_min       = 0x00;
    Breathe.speed_max       = 0x1F;
    Breathe.speed           = 0x0F;
    Breathe.colors_min      = 1;
    Breathe.colors_max      = 1;
    Breathe.direction       = 0;
    modes.push_back(Breathe);

    mode ColorShift;
    ColorShift.name         = "Color Shift";
    ColorShift.value        = 0x03;
    ColorShift.flags        = MODE_FLAG_HAS_BRIGHTNESS | MODE_FLAG_HAS_SPEED;
    ColorShift.color_mode   = MODE_COLORS_NONE;
    ColorShift.brightness_min = STEELSERIES_ARENA7_BRIGHTNESS_MIN;
    ColorShift.brightness_max = controller->GetMaxBrightness();
    ColorShift.brightness   = ColorShift.brightness_max;
    ColorShift.speed_min    = 0x00;
    ColorShift.speed_max    = 0x1F;
    ColorShift.speed        = 0x0F;
    ColorShift.colors_min   = 0;
    ColorShift.colors_max   = 0;
    ColorShift.direction    = 0;
    modes.push_back(ColorShift);

    mode AudioVisualizer;
    AudioVisualizer.name    = "Audio Visualizer";
    AudioVisualizer.value   = 0x04;
    AudioVisualizer.flags   = MODE_FLAG_HAS_BRIGHTNESS;
    AudioVisualizer.color_mode = MODE_COLORS_NONE;
    AudioVisualizer.brightness_min = STEELSERIES_ARENA7_BRIGHTNESS_MIN;
    AudioVisualizer.brightness_max = controller->GetMaxBrightness();
    AudioVisualizer.brightness = AudioVisualizer.brightness_max;
    AudioVisualizer.speed_min = 0;
    AudioVisualizer.speed_max = 0;
    AudioVisualizer.speed   = 0;
    AudioVisualizer.colors_min = 0;
    AudioVisualizer.colors_max = 0;
    AudioVisualizer.direction = 0;
    modes.push_back(AudioVisualizer);

    SetupZones();
}

RGBController_SteelSeriesArena7::~RGBController_SteelSeriesArena7()
{
    delete controller;
}

void RGBController_SteelSeriesArena7::SetupZones()
{
    /*---------------------------------------------------------*\
    | Arena 7 has 4 zones: Left Back, Left Base, Right Back, Right Base |
    \*---------------------------------------------------------*/
    const std::vector<std::string> zone_names = {
        "Left Back",
        "Left Base",
        "Right Back",
        "Right Base"
    };

    for (const auto& zone_name : zone_names)
    {
        zone new_zone;
        new_zone.name          = zone_name;
        new_zone.type          = ZONE_TYPE_SINGLE;
        new_zone.leds_min      = 1;
        new_zone.leds_max      = 1;
        new_zone.leds_count    = 1;
        new_zone.matrix_map    = NULL;
        new_zone.flags         = 0;
        new_zone.start_idx     = 0;
        zones.push_back(new_zone);

        led new_led;
        new_led.name = zone_name + " LED";
        leds.push_back(new_led);
    }

    SetupColors();
}

void RGBController_SteelSeriesArena7::ResizeZone(int /*zone*/, int /*new_size*/)
{
    /*---------------------------------------------------------*\
    | This device does not support resizing zones               |
    \*---------------------------------------------------------*/
}

void RGBController_SteelSeriesArena7::DeviceUpdateLEDs()
{
    controller->SetColor(colors, modes[active_mode].value, modes[active_mode].brightness);
}

void RGBController_SteelSeriesArena7::UpdateZoneLEDs(int zone)
{
    /*---------------------------------------------------------*\
    | Update a specific zone by sending all colors              |
    \*---------------------------------------------------------*/
    DeviceUpdateLEDs();
}

void RGBController_SteelSeriesArena7::UpdateSingleLED(int led)
{
    /*---------------------------------------------------------*\
    | Update a specific LED by sending all colors               |
    \*---------------------------------------------------------*/
    DeviceUpdateLEDs();
}

void RGBController_SteelSeriesArena7::DeviceUpdateMode()
{
    if(modes[active_mode].color_mode == MODE_FLAG_HAS_PER_LED_COLOR)
    {
        DeviceUpdateLEDs();
    }
    else
    {
        controller->SetColor(modes[active_mode].colors, modes[active_mode].value, modes[active_mode].brightness);
    }
}
