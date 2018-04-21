#ifndef __KEY_H__
#define __KEY_H__

#define VK_ENTER          '\n'
#define VK_BACK_SPACE     '\b'
#define VK_TAB            '\t'
#define VK_CANCEL         0x03
#define VK_CLEAR          0x0C
#define VK_SHIFT          0x10
#define VK_CONTROL        0x11
#define VK_ALT            0x12
#define VK_PAUSE          0x13
#define VK_CAPS_LOCK      0x14
#define VK_ESCAPE         0x1B
#define VK_SPACE          0x20
#define VK_PAGE_UP        0x21
#define VK_PAGE_DOWN      0x22
#define VK_END            0x23
#define VK_HOME           0x24

// Constant for the non-numpad <b>left</b> arrow key.
#define VK_LEFT           0x25

// Constant for the non-numpad <b>up</b> arrow key.
#define VK_UP             0x26

// Constant for the non-numpad <b>right</b> arrow key.
#define VK_RIGHT          0x27

// Constant for the non-numpad <b>down</b> arrow key.
#define VK_DOWN           0x28

#define VK_COMMA          0x2C

// Constant for the "-" key.
#define VK_MINUS          0x2D

#define VK_PERIOD         0x2E
#define VK_SLASH          0x2F

// VK_0 thru VK_9 are the same as ASCII '0' thru '9' (0x30 - 0x39) 
#define VK_0              0x30
#define VK_1              0x31
#define VK_2              0x32
#define VK_3              0x33
#define VK_4              0x34
#define VK_5              0x35
#define VK_6              0x36
#define VK_7              0x37
#define VK_8              0x38
#define VK_9              0x39

#define VK_SEMICOLON      0x3B
#define VK_EQUALS         0x3D

// VK_A thru VK_Z are the same as ASCII 'A' thru 'Z' (0x41 - 0x5A) 
#define VK_A              0x41
#define VK_B              0x42
#define VK_C              0x43
#define VK_D              0x44
#define VK_E              0x45
#define VK_F              0x46
#define VK_G              0x47
#define VK_H              0x48
#define VK_I              0x49
#define VK_J              0x4A
#define VK_K              0x4B
#define VK_L              0x4C
#define VK_M              0x4D
#define VK_N              0x4E
#define VK_O              0x4F
#define VK_P              0x50
#define VK_Q              0x51
#define VK_R              0x52
#define VK_S              0x53
#define VK_T              0x54
#define VK_U              0x55
#define VK_V              0x56
#define VK_W              0x57
#define VK_X              0x58
#define VK_Y              0x59
#define VK_Z              0x5A

#define VK_OPEN_BRACKET   0x5B
#define VK_BACK_SLASH     0x5C
#define VK_CLOSE_BRACKET  0x5D

#define VK_NUMPAD0        0x60
#define VK_NUMPAD1        0x61
#define VK_NUMPAD2        0x62
#define VK_NUMPAD3        0x63
#define VK_NUMPAD4        0x64
#define VK_NUMPAD5        0x65
#define VK_NUMPAD6        0x66
#define VK_NUMPAD7        0x67
#define VK_NUMPAD8        0x68
#define VK_NUMPAD9        0x69
#define VK_MULTIPLY       0x6A
#define VK_ADD            0x6B
 
// Constant for the Numpad Separator key. 
#define VK_SEPARATOR      VK_SEPARATER

#define VK_SUBTRACT       0x6D
#define VK_DECIMAL        0x6E
#define VK_DIVIDE         0x6F
#define VK_DELETE         0x7F/// ASCII DEL 
#define VK_NUM_LOCK       0x90
#define VK_SCROLL_LOCK    0x91

// Constant for the F1, F2, ... function keys. 
#define VK_F1             0x70
#define VK_F2             0x71
#define VK_F3             0x72
#define VK_F4             0x73
#define VK_F5             0x74
#define VK_F6             0x75
#define VK_F7             0x76
#define VK_F8             0x77
#define VK_F9             0x78
#define VK_F10            0x79
#define VK_F11            0x7A
#define VK_F12            0x7B

#define VK_PRINTSCREEN    0x9A
#define VK_INSERT         0x9B
#define VK_HELP           0x9C
#define VK_META           0x9D

#define VK_BACK_QUOTE     0xC0
#define VK_QUOTE          0xDE

// Constant for the numeric keypad <b>up</b> arrow key.
#define VK_KP_UP          0xE0

// Constant for the numeric keypad <b>down</b> arrow key.
#define VK_KP_DOWN        0xE1

// Constant for the numeric keypad <b>left</b> arrow key.
#define VK_KP_LEFT        0xE2

// Constant for the numeric keypad <b>right</b> arrow key.
#define VK_KP_RIGHT       0xE3
    
/// For European keyboards 
#define VK_DEAD_GRAVE               0x80

#define VK_DEAD_ACUTE               0x81

#define VK_DEAD_CIRCUMFLEX          0x82

#define VK_DEAD_TILDE               0x83

#define VK_DEAD_MACRON              0x84

#define VK_DEAD_BREVE               0x85

#define VK_DEAD_ABOVEDOT            0x86

#define VK_DEAD_DIAERESIS           0x87

#define VK_DEAD_ABOVERING           0x88

#define VK_DEAD_DOUBLEACUTE         0x89

#define VK_DEAD_CARON               0x8a

#define VK_DEAD_CEDILLA             0x8b

#define VK_DEAD_OGONEK              0x8c

#define VK_DEAD_IOTA                0x8d

#define VK_DEAD_VOICED_SOUND        0x8e

#define VK_DEAD_SEMIVOICED_SOUND    0x8f

#define VK_AMPERSAND                0x96

#define VK_ASTERISK                 0x97

#define VK_QUOTEDBL                 0x98

#define VK_LESS                     0x99

#define VK_GREATER                  0xa0

#define VK_BRACELEFT                0xa1

#define VK_BRACERIGHT               0xa2
 
#define VK_AT                       0x0200

// Constant for the ":" key.
#define VK_COLON                    0x0201
 
// Constant for the "^" key.
#define VK_CIRCUMFLEX               0x0202

// Constant for the "$" key.
#define VK_DOLLAR                   0x0203
 
// Constant for the Euro currency sign key.
#define VK_EURO_SIGN                0x0204
 
// Constant for the "!" key.
#define VK_EXCLAMATION_MARK         0x0205
 
// Constant for the inverted exclamation mark key.
#define VK_INVERTED_EXCLAMATION_MARK 0x0206

// Constant for the "(" key.
#define VK_LEFT_PARENTHESIS         0x0207
 
// Constant for the "#" key.
#define VK_NUMBER_SIGN              0x0208
 
// Constant for the "+" key.
#define VK_PLUS                     0x0209

// Constant for the ")" key.
#define VK_RIGHT_PARENTHESIS        0x020A

// Constant for the "_" key.
#define VK_UNDERSCORE               0x020B

// Constant for the AltGraph function key.
#define VK_ALT_GRAPH                0xFF7E

// This value is used to indicate that the keyCode is unknown.
// KEY_TYPED events do not have a keyCode value this value 
// is used instead.  
#define VK_UNDEFINED      0x0

#endif
