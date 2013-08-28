// Copyright (C) 2004-2009 Joe Linhoff - All Rights Reserved
// qeinp.h -- public interface to library
#ifndef QEINP_H
#define QEINP_H

#ifndef GPTYPES_H
#include "gptypes.h"
#endif // ndef GPTYPES_H

#ifdef __cplusplus  // C in C++
extern "C" {        //
#endif              //

///////////////////////////////////////////////////////////////////////////////
// LIBRARY

GP_API int gpinpInit();
GP_API void gpinpFinal();
GP_API int gpinpService();
GP_API int gpinpOpen();
GP_API void gpinpClose();

///////////////////////////////////////////////////////////////////////////////

//
// BUTTONS, MICE, KEYBOARD
//

enum { // button definitions
   QEINPBUTTON_NONE, ///< reserved
   QEINPBUTTON_UP, ///< up button or key
   QEINPBUTTON_DOWN, ///< down button or key
   QEINPBUTTON_LEFT, ///< left button or key
   QEINPBUTTON_RIGHT, ///< right button or key
   QEINPBUTTON_MOUSELB, ///< mouse left button
   QEINPBUTTON_MOUSERB, ///< mouse right button
   QEINPBUTTON_MOUSECB, ///< mouse center button
   QEINPBUTTON_UP2, ///< second up button or key
   QEINPBUTTON_DOWN2, ///< second down button or key
   QEINPBUTTON_LEFT2, ///< second left button or key
   QEINPBUTTON_RIGHT2, ///< second right button or key
   QEINPBUTTON_UP3, ///< third up button or key
   QEINPBUTTON_DOWN3, ///< third up button or key
   QEINPBUTTON_A, ///< A button or key (not keyboard A)
   QEINPBUTTON_B, ///< B button or key (not keyboard B)
   QEINPBUTTON_X, ///< X button or key (not keyboard X)
   QEINPBUTTON_Y, ///< Y button or key (not keyboard Y)
   QEINPBUTTON_START, ///< start button or key
   QEINPBUTTON_START2, ///< player2 start or key
   QEINPBUTTON_DRAWMODE, ///< drawmode button or key
   QEINPBUTTON_SPACEBAR, ///< spacebar
   QEINPBUTTON_ZERO, ///< zero button or key
   QEINPBUTTON_SELECT, ///< enter
   QEINPBUTTON_FIRSTGAME=32, ///< first game defined button 
   QEINPBUTTON_NUM=64 ///< max number of buttons -- not a button
}; // button definitions

// default mappings to keys
#define QEINPBUTTON_KEY_Z QEINPBUTTON_A
#define QEINPBUTTON_KEY_X QEINPBUTTON_B
#define QEINPBUTTON_KEY_C QEINPBUTTON_X
#define QEINPBUTTON_KEY_V QEINPBUTTON_Y
#define QEINPBUTTON_KEY_W QEINPBUTTON_UP2
#define QEINPBUTTON_KEY_A QEINPBUTTON_LEFT2
#define QEINPBUTTON_KEY_S QEINPBUTTON_DOWN2
#define QEINPBUTTON_KEY_D QEINPBUTTON_RIGHT2
#define QEINPBUTTON_KEY_0 QEINPBUTTON_ZERO
#define QEINPBUTTON_KEY_1 QEINPBUTTON_START
#define QEINPBUTTON_KEY_2 QEINPBUTTON_START2
#define QEINPBUTTON_KEY_ENTER QEINPBUTTON_SELECT

#define M_QEINPSTATE_ALT   0x0001
#define M_QEINPSTATE_SHIFT 0x0002
#define M_QEINPSTATE_CTL   0x0004

GP_API uns qeInpButton(uns inpb); ///< QEINPBUTTON_
GP_API uns qeInpMouseXY(int *xy); ///< fill xy array with window pos, get btn
GP_API int qeInpMouseSetXY(int *xy); ///< set position from xy array
GP_API uns qeInpState(void); ///< get current M_QEINPSTATE_ flags
GP_API int qeInpMouseWheel(void); ///< read the wheel
GP_API int qeInpKeyBuf(uns *keyBuf,uns keyBufSize); ///< empty keyboard buffer

//
// JOYSTICKS
//

enum {
   QEJOYAXIS_LEFT_X=0,
   QEJOYAXIS_LEFT_Y,
   QEJOYAXIS_RIGHT_X,
   QEJOYAXIS_RIGHT_Y,
   QEJOYAXIS_LEFT_TRIGGER,
   QEJOYAXIS_RIGHT_TRIGGER,
   QEJOYAXIS_LEFT_Z, // used for Wiimote
   QEJOYAXIS_RIGHT_Z, // used for Wiimote
   QEJOYAXIS_NUM
};

enum {
   QEJOYBUTTON_A=0,
   QEJOYBUTTON_B,
   QEJOYBUTTON_X,
   QEJOYBUTTON_Y,
   QEJOYBUTTON_LSHOULDER,
   QEJOYBUTTON_RSHOULDER,
   QEJOYBUTTON_DPAD_LEFT,
   QEJOYBUTTON_DPAD_RIGHT,
   QEJOYBUTTON_DPAD_UP,
   QEJOYBUTTON_DPAD_DOWN,
   QEJOYBUTTON_START,
   QEJOYBUTTON_BACK,
   QEJOYBUTTON_LTHUMB,
   QEJOYBUTTON_RTHUMB,
   QEJOYBUTTON_NUM
};

#define QEJOYMOTOR_SPEED_MAX 32767 // max motor speed
#define QEJOYMOTOR_MOTOR_ALL 0xffff // all motors

#define M_QEJOYFLAGS_XBOX360   0x00000001 ///< M_QEJOYFLAGS_DEVTYPE
#define M_QEJOYFLAGS_DIRECT    0x00000002 ///< M_QEJOYFLAGS_DEVTYPE
#define M_QEJOYFLAGS_WIIMOTE   0x00000003 ///< M_QEJOYFLAGS_DEVTYPE
#define M_QEJOYFLAGS_DEVTYPE   0x000000ff ///< M_QEJOYFLAGS_DEVTYPE
#define M_QEJOYFLAGS_ATTACHED  0x00001000 ///< currently attached
#define M_QEJOYFLAGS_LEFTAXIS  0x00002000 ///< has left axis
#define M_QEJOYFLAGS_RIGHTAXIS 0x00004000 ///< has right axis
#define M_QEJOYFLAGS_DPAD      0x00008000 // has dpad

// joy parameter can be either joynum or joymap
GP_API uns qeInpJoyNum(void); ///< joysticks attached -- valid after qeOpen()
GP_API int qeInpJoyInfo(uns joy,uns *axisp,uns *buttonp); ///< get axes, btns
GP_API float qeInpJoyAxisf(uns joy,uns axis); ///< use QEJOYAXIS_, return -1..1
GP_API uns qeInpJoyButton(uns joy,uns button); ///< use QEJOYBUTTON_
GP_API int qeInpJoyMotor(uns joy,uns motor,uns speed); ///< set, use QEJOYMOTOR_
GP_API uns qeInpJoyFlags(uns joy); ///< return M_QEJOYFLAGS_ for joy

//
// INPUT OPERATIONS
//

enum {
   QEINPOP_NONE,
   QEINPOP_KEYBUFGETNUM, ///< -- get number of entries in keyBuf
   QEINPOP_KEYBUFCHECKOVERFLOW, ///< -- return keyBuf overflow flag
   QEINPOP_KEYBUFCPYCHRBUF, ///< (chr *dst,uns dstSize) copy out of keyBuf
   QEINPOP_KEYBUFRESET, ///< -- reset keyBuf
   QEINPOP_KEYBOARDMAPPINGS_OFF, ///< -- turn keyboard mappings off
   QEINPOP_KEYBOARDMAPPINGS_ON, ///< -- turn keyboard mappings on
   QEINPOP_JOYGETNUM_HATS, ///< (uns joy) return number of hats
   QEINPOP_JOYGETNUM_MOTORS, ///< (uns joy) return number of motors
   QEINPOP_CURSOFF, ///< turn cursor off, returns cursor count
   QEINPOP_CURSON, ///< turn cursor on, returns cursor count
   QEINPOP_SETKEYMAP, ///< (int *mapTable) table is: QEINPBUTTON_,key,0 .. 0
   QEINPOP_DEFAULTKEYMAP, ///< reset to default mappings
   QEINPOP_RECOUNTJOYSTICKS, ///< (int n) count the number of joysticks attached
   QEINPOP_JOYMAPSET, ///< (uns joynum, uns joymap) joymap must be > max joynum
   QEINPOP_JOYMAPGET, ///< (uns joynum) return mapping -- zero = unmapped
   QEINPOP_JOYMAPRESETALL, ///< reset, i.e. unmap, all mappings
   QEINPOP_JOYGETDEVICEINFO, ///< (int n) chr *buf, uns bufsize
   QEINPOP_MOUSECAPTURE, ///< (int onff) onoff=1 to capture, 0=not captured
   QEINPOP_MOUSECONFINE, ///< (int onoff) onoff=1 to confine, 0=not confined
   QEINPOP_MOUSEGETRAWXY, ///< (int *xy) physical coords
};

GP_API int qeInpOp(uns op,...); ///< QEINPOP_

//
// RAW EVENTS
//

enum { // raw key codes are used for key mappings
   QEINPRAWKEYCODE_SPECIAL=0x1000,
   QEINPRAWKEYCODE_UP,
   QEINPRAWKEYCODE_DOWN,
   QEINPRAWKEYCODE_LEFT,
   QEINPRAWKEYCODE_RIGHT,
   QEINPRAWKEYCODE_ALT,
   QEINPRAWKEYCODE_LSHIFT,
   QEINPRAWKEYCODE_RSHIFT,
   QEINPRAWKEYCODE_CTL,
   QEINPRAWKEYCODE_PAUSE,
   QEINPRAWKEYCODE_CAPSLOCK,
   QEINPRAWKEYCODE_UP2,
   QEINPRAWKEYCODE_DOWN2,
   QEINPRAWKEYCODE_F1,
   QEINPRAWKEYCODE_F2,
   QEINPRAWKEYCODE_F3,
   QEINPRAWKEYCODE_F4,
   QEINPRAWKEYCODE_F5,
   QEINPRAWKEYCODE_F6,
   QEINPRAWKEYCODE_F7,
   QEINPRAWKEYCODE_F8,
   QEINPRAWKEYCODE_F9,
}; // raw key codes

enum {
   QEINPRAW_NONE, // reserved
   QEINPRAW_KEYDOWN, // int *zerotermlist
   QEINPRAW_KEYUP, // int *zerotermlist
   QEINPRAW_CHARDOWN, // int char
   QEINPRAW_MOUSEMOVE, // int x,int y
   QEINPRAW_BUTTON, // int QEINPBUTTON_, int up/down
   QEINPRAW_WHEELMOVE, // int delta
};
#define M_QEINPRAW 0xff

#define M_QEINPRAW_CUR   0x0100
#define M_QEINPRAW_ALT   0x0200
#define M_QEINPRAW_SHIFT 0x0400
#define M_QEINPRAW_CTL   0x0800

GP_API int qeInpRawEvent(uns op,...);

// helper for quick input
GP_API int qefnInpMoveLookSP(float *dstMove,float *dstLook,
   float *invCamM9,chr *sp,...);

///////////////////////////////////////////////////////////////////////////////

#ifdef __cplusplus  // C in C++
}                   //
#endif              //

#endif // QEINP_H