/*
MIT License

Copyright (c) 2017-2019 Nefarius Software Solutions e.U. and Contributors

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/


#pragma once

//
// Represents the desired target type for the emulated device.
//  
typedef enum _VIGEM_TARGET_TYPE
{
    // 
    // Microsoft Xbox 360 Controller (wired)
    // 
    Xbox360Wired = 0,
    //
    // Sony DualSense 5 (wired)
    // 
    DualSense5Wired = 2, // NOTE: 1 skipped on purpose to maintain compatibility

} VIGEM_TARGET_TYPE, *PVIGEM_TARGET_TYPE;

//
// Possible XUSB report buttons.
// 
typedef enum _XUSB_BUTTON
{
    XUSB_GAMEPAD_DPAD_UP            = 0x0001,
    XUSB_GAMEPAD_DPAD_DOWN          = 0x0002,
    XUSB_GAMEPAD_DPAD_LEFT          = 0x0004,
    XUSB_GAMEPAD_DPAD_RIGHT         = 0x0008,
    XUSB_GAMEPAD_START              = 0x0010,
    XUSB_GAMEPAD_BACK               = 0x0020,
    XUSB_GAMEPAD_LEFT_THUMB         = 0x0040,
    XUSB_GAMEPAD_RIGHT_THUMB        = 0x0080,
    XUSB_GAMEPAD_LEFT_SHOULDER      = 0x0100,
    XUSB_GAMEPAD_RIGHT_SHOULDER     = 0x0200,
    XUSB_GAMEPAD_GUIDE              = 0x0400,
    XUSB_GAMEPAD_A                  = 0x1000,
    XUSB_GAMEPAD_B                  = 0x2000,
    XUSB_GAMEPAD_X                  = 0x4000,
    XUSB_GAMEPAD_Y                  = 0x8000

} XUSB_BUTTON, *PXUSB_BUTTON;

//
// Represents an XINPUT_GAMEPAD-compatible report structure.
// 
typedef struct _XUSB_REPORT
{
    USHORT wButtons;
    BYTE bLeftTrigger;
    BYTE bRightTrigger;
    SHORT sThumbLX;
    SHORT sThumbLY;
    SHORT sThumbRX;
    SHORT sThumbRY;

} XUSB_REPORT, *PXUSB_REPORT;

//
// Initializes a _XUSB_REPORT structure.
// 
VOID FORCEINLINE XUSB_REPORT_INIT(
    _Out_ PXUSB_REPORT Report
)
{
    RtlZeroMemory(Report, sizeof(XUSB_REPORT));
}

//
// The color value (RGB) of a DualSense 5 Lightbar
// 
typedef struct _DS5_LIGHTBAR_COLOR
{
    //
    // Red part of the Lightbar (0-255).
    //
    UCHAR Red;

    //
    // Green part of the Lightbar (0-255).
    //
    UCHAR Green;

    //
    // Blue part of the Lightbar (0-255).
    //
    UCHAR Blue;

} DS5_LIGHTBAR_COLOR, *PDS5_LIGHTBAR_COLOR;

//
// DualSense 5 digital buttons
// 
typedef enum _DS5_BUTTONS
{
    DS5_BUTTON_THUMB_RIGHT      = 1 << 15,
    DS5_BUTTON_THUMB_LEFT       = 1 << 14,
    DS5_BUTTON_OPTIONS          = 1 << 13,
    DS5_BUTTON_SHARE            = 1 << 12,
    DS5_BUTTON_TRIGGER_RIGHT    = 1 << 11,
    DS5_BUTTON_TRIGGER_LEFT     = 1 << 10,
    DS5_BUTTON_SHOULDER_RIGHT   = 1 << 9,
    DS5_BUTTON_SHOULDER_LEFT    = 1 << 8,
    DS5_BUTTON_TRIANGLE         = 1 << 7,
    DS5_BUTTON_CIRCLE           = 1 << 6,
    DS5_BUTTON_CROSS            = 1 << 5,
    DS5_BUTTON_SQUARE           = 1 << 4

} DS5_BUTTONS, *PDS5_BUTTONS;

//
// DualSense 5 special buttons
// 
typedef enum _DS5_SPECIAL_BUTTONS
{
    DS5_SPECIAL_BUTTON_PS           = 1 << 0,
    DS5_SPECIAL_BUTTON_TOUCHPAD     = 1 << 1

} DS5_SPECIAL_BUTTONS, *PDS5_SPECIAL_BUTTONS;

//
// DualSense 5 directional pad (HAT) values
// 
typedef enum _DS5_DPAD_DIRECTIONS
{
    DS5_BUTTON_DPAD_NONE        = 0x8,
    DS5_BUTTON_DPAD_NORTHWEST   = 0x7,
    DS5_BUTTON_DPAD_WEST        = 0x6,
    DS5_BUTTON_DPAD_SOUTHWEST   = 0x5,
    DS5_BUTTON_DPAD_SOUTH       = 0x4,
    DS5_BUTTON_DPAD_SOUTHEAST   = 0x3,
    DS5_BUTTON_DPAD_EAST        = 0x2,
    DS5_BUTTON_DPAD_NORTHEAST   = 0x1,
    DS5_BUTTON_DPAD_NORTH       = 0x0

} DS5_DPAD_DIRECTIONS, *PDS5_DPAD_DIRECTIONS;

#include <pshpack1.h> // pack structs tightly

//
// DualSense 5 HID Touch finger data (4 bytes)
//
typedef struct _DS5_TOUCH_FINGER
{
    /*0.0*/ ULONG Index : 7;
    /*0.7*/ ULONG NotTouching : 1;
    /*1.0*/ ULONG FingerX : 12;
    /*2.4*/ ULONG FingerY : 12;
} DS5_TOUCH_FINGER, *PDS5_TOUCH_FINGER;

//
// DualSense 5 HID Touchpad structure (9 bytes)
//
typedef struct _DS5_TOUCH
{
    /*0*/ DS5_TOUCH_FINGER Finger[2];
    /*8*/ BYTE bTimestamp;
} DS5_TOUCH, *PDS5_TOUCH;

//
// DualSense 5 HID Input report (USB Get State Data - 63 bytes)
//
typedef struct _DS5_REPORT
{
    /* 0  */ BYTE bThumbLX;
    /* 1  */ BYTE bThumbLY;
    /* 2  */ BYTE bThumbRX;
    /* 3  */ BYTE bThumbRY;
    /* 4  */ BYTE bTriggerL;
    /* 5  */ BYTE bTriggerR;
    /* 6  */ BYTE bSeqNo;                  // always 0x01 on BT

    // Byte 7: DPad + face buttons
    /* 7.0*/ BYTE DPad : 4;
    /* 7.4*/ BYTE ButtonSquare : 1;
    /* 7.5*/ BYTE ButtonCross : 1;
    /* 7.6*/ BYTE ButtonCircle : 1;
    /* 7.7*/ BYTE ButtonTriangle : 1;

    // Byte 8: shoulder/trigger/menu/thumbstick buttons
    /* 8.0*/ BYTE ButtonL1 : 1;
    /* 8.1*/ BYTE ButtonR1 : 1;
    /* 8.2*/ BYTE ButtonL2 : 1;
    /* 8.3*/ BYTE ButtonR2 : 1;
    /* 8.4*/ BYTE ButtonCreate : 1;
    /* 8.5*/ BYTE ButtonOptions : 1;
    /* 8.6*/ BYTE ButtonL3 : 1;
    /* 8.7*/ BYTE ButtonR3 : 1;

    // Byte 9: special buttons
    /* 9.0*/ BYTE ButtonHome : 1;
    /* 9.1*/ BYTE ButtonPad : 1;
    /* 9.2*/ BYTE ButtonMute : 1;
    /* 9.3*/ BYTE UNK1 : 1;               // appears unused
    /* 9.4*/ BYTE ButtonLeftFunction : 1;  // DualSense Edge
    /* 9.5*/ BYTE ButtonRightFunction : 1; // DualSense Edge
    /* 9.6*/ BYTE ButtonLeftPaddle : 1;    // DualSense Edge
    /* 9.7*/ BYTE ButtonRightPaddle : 1;   // DualSense Edge

    /*10  */ BYTE bUNK2;                   // appears unused
    /*11  */ ULONG ulUNKCounter;           // Linux driver calls this reserved
    /*15  */ SHORT wAngularVelocityX;
    /*17  */ SHORT wAngularVelocityZ;
    /*19  */ SHORT wAngularVelocityY;
    /*21  */ SHORT wAccelerometerX;
    /*23  */ SHORT wAccelerometerY;
    /*25  */ SHORT wAccelerometerZ;
    /*27  */ ULONG ulSensorTimestamp;
    /*31  */ CHAR bTemperature;            // reserved2 in Linux driver
    /*32  */ DS5_TOUCH sCurrentTouch;      // 9 bytes touch data

    // Byte 41: trigger feedback
    /*41.0*/ BYTE TriggerRightStopLocation : 4; // range 0-9
    /*41.4*/ BYTE TriggerRightStatus : 4;
    /*42.0*/ BYTE TriggerLeftStopLocation : 4;
    /*42.4*/ BYTE TriggerLeftStatus : 4;   // 0 feedbackNoLoad / 1 feedbackLoadApplied
                                           // 0 weaponReady / 1 weaponFiring / 2 weaponFired
                                           // 0 vibrationNotVibrating / 1 vibrationIsVibrating

    /*43  */ ULONG ulHostTimestamp;         // mirrors data from report write

    // Byte 47: active trigger effect
    /*47.0*/ BYTE TriggerRightEffect : 4;  // 0 reset, 1 feedback, 2 weapon, 3 vibration
    /*47.4*/ BYTE TriggerLeftEffect : 4;

    /*48  */ ULONG ulDeviceTimeStamp;

    // Byte 52: power info
    /*52.0*/ BYTE PowerPercent : 4;        // 0x00-0x0A
    /*52.4*/ BYTE PowerState : 4;

    // Byte 53: plugged device info
    /*53.0*/ BYTE PluggedHeadphones : 1;
    /*53.1*/ BYTE PluggedMic : 1;
    /*53.2*/ BYTE MicMuted : 1;            // Mic muted by powersave/mute command
    /*53.3*/ BYTE PluggedUsbData : 1;
    /*53.4*/ BYTE PluggedUsbPower : 1;     // cannot be 1 if PluggedUsbData is 1
    /*53.5*/ BYTE UsbPowerOnBT : 1;        // only 1 if BT connected and USB powered
    /*53.6*/ BYTE DockDetect : 1;
    /*53.7*/ BYTE PluggedUnk : 1;

    // Byte 54
    /*54.0*/ BYTE PluggedExternalMic : 1;  // Is external mic active
    /*54.1*/ BYTE HapticLowPassFilter : 1; // Is the Haptic Low-Pass-Filter active
    /*54.2*/ BYTE PluggedUnk3 : 6;

    /*55  */ BYTE bAesCmac[8];

} DS5_REPORT, *PDS5_REPORT;

//
// Sets the current state of the D-PAD on a DualSense 5 report.
// 
VOID FORCEINLINE DS5_SET_DPAD(
    _Out_ PDS5_REPORT Report,
    _In_ DS5_DPAD_DIRECTIONS Dpad
)
{
    Report->DPad = (BYTE)Dpad;
}

VOID FORCEINLINE DS5_REPORT_INIT(
    _Out_ PDS5_REPORT Report
)
{
    RtlZeroMemory(Report, sizeof(DS5_REPORT));

    Report->bThumbLX = 0x80;
    Report->bThumbLY = 0x80;
    Report->bThumbRX = 0x80;
    Report->bThumbRY = 0x80;

    DS5_SET_DPAD(Report, DS5_BUTTON_DPAD_NONE);
}

typedef struct _DS5_OUTPUT_BUFFER
{
	//
	// The output report buffer
	// 
	_Out_ UCHAR Buffer[64];
	
} DS5_OUTPUT_BUFFER, *PDS5_OUTPUT_BUFFER;

//
// Maximum audio data size per buffer
//
#ifndef DS5_AUDIO_DATA_MAX_SIZE
#define DS5_AUDIO_DATA_MAX_SIZE 4096
#endif

//
// DualSense 5 audio data buffer for user-mode consumption
//
typedef struct _DS5_AUDIO_BUFFER
{
	//
	// Actual audio data length in bytes
	//
	_Out_ ULONG AudioDataLength;

	//
	// Audio data payload
	//
	_Out_ UCHAR AudioData[DS5_AUDIO_DATA_MAX_SIZE];

} DS5_AUDIO_BUFFER, *PDS5_AUDIO_BUFFER;

#include <poppack.h>
