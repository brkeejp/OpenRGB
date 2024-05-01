/*-----------------------------------------*\
|  AlienwareAW510KController.h              |
|                                           |
|  Definitions and types for alienware      |
|  AW510K Keyboard                          |
|                                           |
|  Mohamad Sallal - msallal      05/22/2021 |
\*-----------------------------------------*/

#pragma once

#include <string>
#include <hidapi/hidapi.h>
#include "RGBController.h"

enum
{
    ALIENWARE_AW510K_ZONE_MODE_KEYBOARD         = 0x01,
    ALIENWARE_AW510K_ZONE_MODE_LOGO             = 0x07,     /* logo is only need key value, which equal 07  */
};

enum
{
    ALIENWARE_AW510K_ZONE_DIRECT_KEYBOARD       = 0x01,
    ALIENWARE_AW510K_ZONE_DIRECT_MEDIA          = 0x02,
    ALIENWARE_AW510K_ZONE_DIRECT_LOGO           = 0x07,
    ALIENWARE_AW510K_ZONE_DIRECT_INDICATORS     = 0x40,
};

enum
{
    ALIENWARE_AW510K_MODE_OFF                   = 0x00,
    ALIENWARE_AW510K_MODE_DIRECT_PER_LED        = 0x01,
    ALIENWARE_AW510K_MODE_DIRECT                = 0x01,
    ALIENWARE_AW510K_MODE_PULSE                 = 0x02,
    ALIENWARE_AW510K_MODE_MORPH                 = 0x03,
    ALIENWARE_AW510K_MODE_BREATHING             = 0x07,
    ALIENWARE_AW510K_MODE_SPECTRUM              = 0x08,
    ALIENWARE_AW510K_MODE_SINGLE_WAVE           = 0x0F,
    ALIENWARE_AW510K_MODE_RAINBOW_WAVE          = 0x10,
    ALIENWARE_AW510K_MODE_SCANNER               = 0x11,
    ALIENWARE_AW510K_MODE_STATIC                = 0x13,
};

enum
{
    ALIENWARE_AW510K_SPEED_SLOWEST              = 0x2D,     /* Slowest speed                                */
    ALIENWARE_AW510K_SPEED_NORMAL               = 0x19,     /* Normal speed                                 */
    ALIENWARE_AW510K_SPEED_FASTEST              = 0x0A,     /* Fastest speed                                */
};

enum
{
    ALIENWARE_AW510K_DIRECTION_LEFT_TO_RIGHT    = 0x01,
    ALIENWARE_AW510K_DIRECTION_RIGHT_TO_LEFT    = 0x02,
    ALIENWARE_AW510K_DIRECTION_TOP_TO_BOTTOM    = 0x03,
    ALIENWARE_AW510K_DIRECTION_BOTTOM_TO_TOP    = 0x04,
};

enum
{
    ALIENWARE_AW510K_SINGLE_COLOR_MODE          = 0x01,
    ALIENWARE_AW510K_TWO_USER_DEFINED_COLOR_MODE= 0x02,
    ALIENWARE_AW510K_RANBOW_COLOR_MODE          = 0x03,
};

struct SelectedKeys
{
    unsigned char idx;
    unsigned char red;
    unsigned char green;
    unsigned char blue;
};

class AlienwareAW510KController
{
public:
    AlienwareAW510KController(hid_device* dev_handle, const char* path);
    ~AlienwareAW510KController();

    std::string GetDeviceLocation();
    std::string GetSerialString();

    void        SendInitialize();
    void        SendCommit();
    void        SendfeatureReport
                    (
                    unsigned char   first_byte,
                    unsigned char   second_byte,
                    unsigned char   third_byte,
                    unsigned char   forth_byte
                    );

    void        SendEdit();

    void        SetDirect
                    (
                    unsigned char   zone,
                    unsigned char   r,
                    unsigned char   g,
                    unsigned char   b
                    );

    void    SendDirectOn
                    (
                    std::vector<SelectedKeys>     &frame_data
                    );

    void        SetMode
                    (
                    unsigned char   mode,
                    unsigned char   speed,
                    unsigned char   direction,
                    unsigned char   colorMode,
                    unsigned char   red,
                    unsigned char   green,
                    unsigned char   blue
                    );

    void        SetMorphMode
                    (
                    unsigned char   mode,
                    unsigned char   speed,
                    unsigned char   red1,
                    unsigned char   green1,
                    unsigned char   blue1,
                    unsigned char   red2,
                    unsigned char   green2,
                    unsigned char   blue2
                    );

    void        UpdateSingleLED
                    (
                    unsigned char   led,
                    unsigned char   red,
                    unsigned char   green,
                    unsigned char   blue
                    );

private:
    hid_device*             dev;
    std::string             location;

    void        SendMode
                    (
                    unsigned char   zone,
                    unsigned char   mode,
                    unsigned char   speed,
                    unsigned char   direction,
                    unsigned char   colorMode,
                    unsigned char   red,
                    unsigned char   green,
                    unsigned char   blue
                    );
};
