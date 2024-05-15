#ifdef SUPPORT_MS_EXTENSIONS
#pragma bss_seg(".usb.data.bss")
#pragma data_seg(".usb.data")
#pragma code_seg(".usb.text")
#pragma const_seg(".usb.text.const")
#pragma str_literal_override(".usb.text.const")
#endif

#include "typedef.h"
#include "app_config.h"
#if TCFG_ADB_ENABLE
static  const u8 _open_session[] = {
    0x10, 0x00, 0x00, 0x00, 0x01, 0x00, 0x02, 0x10, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00
};
static const u8 get_device_info[] = {
    0x0C, 0x00, 0x00, 0x00, 0x01, 0x00, 0x01, 0x10, 0x01, 0x00, 0x00, 0x00,
};


static const u8 adb_signatrue_data[][256] = {
    {
        0xFA, 0xA6, 0xE3, 0x50, 0x3C, 0xC4, 0x95, 0xFE, 0xBB, 0x46, 0xE0, 0x9F, 0xD9, 0x9A, 0x18, 0xC1,
        0x28, 0x67, 0xA9, 0x46, 0xF8, 0x20, 0xBF, 0xDB, 0xFE, 0x6B, 0xC8, 0xC4, 0x0A, 0x09, 0xFA, 0x9A,
        0xCD, 0x51, 0xE3, 0x67, 0xD1, 0xDF, 0xD2, 0x92, 0xD3, 0x9E, 0xFA, 0x17, 0x76, 0x01, 0xF5, 0xE2,
        0xBD, 0x64, 0x9C, 0x92, 0x82, 0x4B, 0xE4, 0x27, 0x21, 0x22, 0x1A, 0x70, 0x99, 0x8F, 0xC5, 0xD5,
        0xE2, 0x02, 0x2C, 0xA4, 0x13, 0x08, 0x1E, 0x42, 0x83, 0x5C, 0x7E, 0x3C, 0x1F, 0x97, 0x1B, 0xAF,
        0x6F, 0x7E, 0x4F, 0xAB, 0xDA, 0x6A, 0x61, 0x56, 0x03, 0x79, 0xB5, 0xF0, 0x97, 0xEE, 0xEC, 0x88,
        0x6F, 0x9E, 0x8D, 0x41, 0xE2, 0x13, 0x9B, 0x21, 0xEE, 0x6F, 0x09, 0x81, 0x62, 0xC1, 0xB5, 0xE7,
        0xC2, 0x5C, 0x4A, 0x8C, 0x39, 0xAA, 0x50, 0x08, 0x48, 0xB5, 0x1D, 0xF6, 0x7C, 0x67, 0xD6, 0x39,
        0x63, 0x7E, 0x5E, 0x49, 0x3D, 0x9B, 0x49, 0x4B, 0x67, 0x8E, 0x06, 0x31, 0x07, 0x4E, 0x56, 0x8A,
        0xC4, 0x9D, 0x84, 0xA9, 0xF4, 0xFC, 0xE3, 0x2D, 0x1D, 0x2A, 0x98, 0x52, 0x40, 0x49, 0x93, 0x71,
        0xA7, 0x43, 0x0D, 0x78, 0xEB, 0xFA, 0x49, 0x7A, 0x39, 0xBF, 0xE4, 0x06, 0x08, 0x1B, 0x20, 0x84,
        0xDC, 0x64, 0xBB, 0xDE, 0x1A, 0x5E, 0x4B, 0xF8, 0x57, 0xBF, 0x9C, 0x8C, 0xB9, 0x1D, 0xEE, 0xB3,
        0x90, 0x17, 0x03, 0x8B, 0x3E, 0x9F, 0x8A, 0x23, 0xEC, 0x30, 0xA7, 0x24, 0x5E, 0x5B, 0x58, 0xAA,
        0x5A, 0xAE, 0xE2, 0x14, 0xC1, 0xAE, 0xA3, 0xF9, 0xAF, 0x70, 0xE0, 0x14, 0x7D, 0x73, 0x3B, 0x6D,
        0x9B, 0x06, 0x2F, 0xAA, 0xFF, 0x7A, 0x2A, 0x56, 0x6F, 0x91, 0x70, 0x6D, 0x4A, 0x18, 0x35, 0x51,
        0xD5, 0x5D, 0xFB, 0xA1, 0x8B, 0x03, 0xF2, 0x0C, 0x56, 0xF0, 0x5A, 0x4A, 0x08, 0x89, 0xFE, 0x86
    },
    {
        0x60, 0xE6, 0x4A, 0x3D, 0x12, 0xD1, 0x48, 0x25, 0x7D, 0x6E, 0x8E, 0x03, 0xE2, 0xC8, 0xE7, 0x66,
        0x96, 0xD7, 0xD3, 0xBF, 0xE6, 0x97, 0x13, 0x3A, 0x2D, 0x2B, 0x85, 0xE7, 0xDA, 0x5C, 0x87, 0xD8,
        0xDC, 0x88, 0xAC, 0xF7, 0xC3, 0xF0, 0x5A, 0xE8, 0x95, 0x66, 0x19, 0xA1, 0xA8, 0x2A, 0xE1, 0x70,
        0x13, 0xF0, 0x05, 0x59, 0x3D, 0x89, 0x04, 0x65, 0x08, 0x03, 0x9C, 0xDC, 0x71, 0x24, 0xC5, 0x9E,
        0x4D, 0x82, 0xD8, 0x72, 0x07, 0xFD, 0x8F, 0xD3, 0x37, 0x56, 0x8C, 0xB6, 0x01, 0xDB, 0x08, 0x5B,
        0xA3, 0x42, 0x8F, 0xF0, 0xCA, 0xDC, 0x80, 0xEB, 0x32, 0xC4, 0x67, 0x1F, 0x73, 0xAF, 0xF0, 0x56,
        0xBC, 0x89, 0x72, 0xB1, 0x7D, 0xDA, 0xA4, 0x79, 0x7D, 0x02, 0x35, 0x38, 0xBA, 0xA0, 0x36, 0xFE,
        0x5A, 0x70, 0x93, 0xF5, 0x10, 0x7A, 0x92, 0xE9, 0xD4, 0xB0, 0xED, 0xF3, 0x00, 0xD0, 0x27, 0x79,
        0x51, 0x54, 0x38, 0x2D, 0x4C, 0xAA, 0x27, 0xEF, 0xA7, 0x8A, 0x34, 0x4E, 0x4B, 0x29, 0x90, 0xC4,
        0x3E, 0xA8, 0x8D, 0x3D, 0x00, 0xD6, 0x84, 0x11, 0x17, 0x32, 0xD6, 0xE9, 0x33, 0x02, 0xCD, 0x04,
        0x35, 0x3F, 0x1A, 0xC3, 0x05, 0xCF, 0x6F, 0xF4, 0x39, 0x65, 0xE5, 0x6B, 0x88, 0x1E, 0x25, 0xA1,
        0xD7, 0xC0, 0x30, 0xE4, 0x0B, 0x2A, 0x61, 0x6D, 0x61, 0xF1, 0x93, 0xAE, 0xC3, 0x42, 0xDC, 0x15,
        0x1D, 0x87, 0x60, 0x09, 0x92, 0x64, 0xC1, 0x63, 0xAD, 0xCA, 0x36, 0x63, 0x0E, 0x69, 0x51, 0x45,
        0xD0, 0x18, 0x5E, 0x10, 0x88, 0x7B, 0xD9, 0xDE, 0xA3, 0x12, 0x85, 0xF9, 0x30, 0x01, 0x0A, 0xE1,
        0x82, 0xD1, 0x49, 0x44, 0xD9, 0x97, 0xE4, 0xF1, 0x55, 0x2D, 0xE2, 0xF3, 0x32, 0xC8, 0xA0, 0xC8,
        0x81, 0xB9, 0x02, 0x87, 0x5C, 0x19, 0xB7, 0x21, 0x6A, 0xB9, 0xB0, 0x81, 0x61, 0x8C, 0x35, 0x78
    },
    {
        0x0C, 0x7E, 0xDC, 0x78, 0x60, 0x1A, 0xC8, 0x9B, 0x3A, 0x23, 0x0B, 0x1D, 0x6F, 0xAE, 0x71, 0x6D,
        0xD8, 0x3C, 0xE9, 0xA3, 0x51, 0x90, 0xAA, 0x7B, 0x7E, 0x2F, 0x2B, 0xBD, 0x34, 0xF4, 0x43, 0x3F,
        0x77, 0xC4, 0x0E, 0x41, 0x04, 0xD9, 0xD4, 0x9C, 0xB3, 0xD2, 0x6B, 0xE1, 0xC6, 0xA8, 0xEF, 0x50,
        0x00, 0x11, 0xE1, 0x08, 0x8B, 0xB4, 0xF1, 0xE3, 0x3D, 0x56, 0x83, 0x07, 0x7F, 0xB8, 0x47, 0xF2,
        0x84, 0xD2, 0xA1, 0x50, 0x64, 0x5A, 0x08, 0x42, 0x36, 0x23, 0x09, 0x31, 0x9A, 0x6B, 0x61, 0x6F,
        0x60, 0x2C, 0xF2, 0x75, 0x4E, 0x6B, 0xB9, 0x15, 0xEE, 0x3C, 0x5E, 0xA2, 0x7F, 0xA0, 0x41, 0xFE,
        0x00, 0x6A, 0x30, 0x49, 0x2C, 0xEC, 0x17, 0x8B, 0x04, 0x32, 0xE9, 0x7A, 0x68, 0xA0, 0xF4, 0xDF,
        0x34, 0xF7, 0x1E, 0x6F, 0x19, 0x09, 0x37, 0x87, 0x99, 0xAA, 0x81, 0x1A, 0xCD, 0xF3, 0x1F, 0x89,
        0x50, 0xB2, 0x17, 0x52, 0x6D, 0x8E, 0xA6, 0x02, 0xC4, 0x2A, 0xAB, 0x3E, 0x5B, 0x38, 0x0C, 0x3F,
        0x50, 0xAA, 0x5F, 0xFE, 0x47, 0x04, 0xED, 0xCD, 0xEE, 0x7C, 0xD5, 0xED, 0x5F, 0x0E, 0xC6, 0x9C,
        0x79, 0x10, 0x11, 0x6F, 0x65, 0x58, 0x37, 0x95, 0x54, 0x50, 0x59, 0x68, 0x4C, 0x8E, 0xE7, 0x35,
        0xF0, 0x96, 0x5A, 0x21, 0x48, 0xB4, 0x53, 0x52, 0xFC, 0xA4, 0x7C, 0x2B, 0xB1, 0xE1, 0x54, 0x2C,
        0x42, 0x3B, 0x68, 0xBF, 0xBB, 0x68, 0x0D, 0x62, 0x16, 0x2F, 0xF5, 0xC8, 0x5F, 0x95, 0x11, 0xF2,
        0xDF, 0x03, 0x1E, 0xCB, 0x7C, 0xD0, 0x9C, 0xE9, 0x89, 0x62, 0xEA, 0xC5, 0x4B, 0xA9, 0xD5, 0xCC,
        0xD2, 0x42, 0x33, 0xA8, 0x7B, 0x2C, 0x56, 0xCF, 0xCE, 0x0D, 0x09, 0x64, 0x62, 0x3F, 0x58, 0x41,
        0x71, 0x79, 0x5D, 0x1D, 0xDF, 0x08, 0x0B, 0x36, 0x97, 0x16, 0x24, 0x20, 0x76, 0x9C, 0x9E, 0xEA
    }
};
static const u8 adb_rsa_pub_key[] = {
    0x51, 0x41, 0x41, 0x41, 0x41, 0x46, 0x4F, 0x56, 0x4F, 0x6E, 0x49, 0x6C, 0x69, 0x51, 0x58, 0x44,
    0x73, 0x42, 0x43, 0x42, 0x31, 0x75, 0x6F, 0x68, 0x70, 0x2B, 0x52, 0x71, 0x6E, 0x6E, 0x59, 0x48,
    0x2F, 0x75, 0x45, 0x58, 0x34, 0x59, 0x6A, 0x50, 0x71, 0x52, 0x4D, 0x35, 0x4B, 0x75, 0x62, 0x56,
    0x50, 0x71, 0x66, 0x57, 0x35, 0x64, 0x56, 0x46, 0x33, 0x2B, 0x76, 0x57, 0x6B, 0x53, 0x4B, 0x71,
    0x35, 0x4C, 0x31, 0x42, 0x4F, 0x4E, 0x4D, 0x36, 0x4B, 0x4F, 0x31, 0x69, 0x31, 0x73, 0x69, 0x4F,
    0x54, 0x69, 0x34, 0x6C, 0x45, 0x30, 0x6F, 0x54, 0x6F, 0x74, 0x30, 0x41, 0x4B, 0x6E, 0x4D, 0x67,
    0x4E, 0x6A, 0x6F, 0x33, 0x45, 0x4D, 0x65, 0x72, 0x30, 0x6C, 0x57, 0x56, 0x54, 0x54, 0x43, 0x39,
    0x68, 0x52, 0x66, 0x67, 0x46, 0x65, 0x56, 0x73, 0x43, 0x32, 0x44, 0x74, 0x71, 0x62, 0x61, 0x6D,
    0x4A, 0x48, 0x63, 0x41, 0x66, 0x59, 0x77, 0x36, 0x54, 0x62, 0x4C, 0x44, 0x6C, 0x4B, 0x70, 0x6A,
    0x38, 0x34, 0x33, 0x63, 0x31, 0x59, 0x5A, 0x65, 0x59, 0x6D, 0x52, 0x56, 0x4D, 0x7A, 0x4D, 0x34,
    0x6E, 0x74, 0x49, 0x78, 0x64, 0x56, 0x33, 0x33, 0x76, 0x4B, 0x75, 0x39, 0x38, 0x34, 0x6A, 0x72,
    0x43, 0x41, 0x47, 0x68, 0x77, 0x4A, 0x41, 0x67, 0x4A, 0x46, 0x53, 0x41, 0x4B, 0x56, 0x59, 0x51,
    0x55, 0x33, 0x6A, 0x4C, 0x76, 0x41, 0x76, 0x57, 0x45, 0x6C, 0x59, 0x47, 0x37, 0x2F, 0x4B, 0x59,
    0x6D, 0x55, 0x34, 0x54, 0x71, 0x73, 0x70, 0x64, 0x76, 0x4C, 0x42, 0x6F, 0x65, 0x36, 0x68, 0x64,
    0x46, 0x44, 0x65, 0x76, 0x4D, 0x4D, 0x43, 0x63, 0x72, 0x6C, 0x44, 0x49, 0x66, 0x65, 0x45, 0x53,
    0x57, 0x68, 0x42, 0x56, 0x35, 0x67, 0x78, 0x6A, 0x57, 0x41, 0x70, 0x4D, 0x47, 0x67, 0x53, 0x71,
    0x53, 0x45, 0x6A, 0x70, 0x36, 0x79, 0x62, 0x6A, 0x33, 0x38, 0x50, 0x4C, 0x72, 0x76, 0x49, 0x51,
    0x48, 0x77, 0x2B, 0x66, 0x70, 0x6F, 0x51, 0x74, 0x6F, 0x4F, 0x4E, 0x65, 0x37, 0x6F, 0x68, 0x66,
    0x42, 0x77, 0x45, 0x66, 0x47, 0x46, 0x4E, 0x63, 0x33, 0x61, 0x70, 0x48, 0x50, 0x6E, 0x59, 0x53,
    0x47, 0x4F, 0x67, 0x70, 0x54, 0x78, 0x70, 0x57, 0x57, 0x75, 0x49, 0x42, 0x79, 0x2F, 0x67, 0x38,
    0x35, 0x2B, 0x65, 0x54, 0x30, 0x44, 0x61, 0x36, 0x53, 0x65, 0x71, 0x33, 0x67, 0x62, 0x4A, 0x59,
    0x64, 0x75, 0x52, 0x44, 0x65, 0x36, 0x5A, 0x39, 0x63, 0x4A, 0x77, 0x48, 0x79, 0x38, 0x43, 0x34,
    0x59, 0x79, 0x6B, 0x44, 0x56, 0x45, 0x4B, 0x6A, 0x39, 0x75, 0x52, 0x41, 0x41, 0x45, 0x59, 0x70,
    0x52, 0x6B, 0x74, 0x39, 0x66, 0x34, 0x79, 0x51, 0x4A, 0x31, 0x73, 0x4D, 0x48, 0x31, 0x5A, 0x75,
    0x4F, 0x55, 0x46, 0x4A, 0x46, 0x65, 0x74, 0x6B, 0x72, 0x67, 0x32, 0x44, 0x46, 0x61, 0x35, 0x30,
    0x50, 0x39, 0x48, 0x61, 0x78, 0x6F, 0x4D, 0x59, 0x30, 0x41, 0x79, 0x78, 0x7A, 0x51, 0x72, 0x53,
    0x77, 0x4D, 0x44, 0x79, 0x6E, 0x36, 0x64, 0x49, 0x65, 0x38, 0x65, 0x58, 0x46, 0x78, 0x51, 0x62,
    0x56, 0x4D, 0x4F, 0x6C, 0x4B, 0x36, 0x79, 0x33, 0x70, 0x6F, 0x2B, 0x4A, 0x4D, 0x42, 0x34, 0x79,
    0x4D, 0x42, 0x36, 0x51, 0x77, 0x30, 0x7A, 0x31, 0x35, 0x62, 0x6F, 0x58, 0x4C, 0x78, 0x4D, 0x4B,
    0x76, 0x4E, 0x59, 0x6E, 0x4B, 0x4E, 0x70, 0x69, 0x6F, 0x33, 0x67, 0x45, 0x78, 0x5A, 0x2B, 0x48,
    0x68, 0x57, 0x62, 0x43, 0x47, 0x69, 0x37, 0x64, 0x4A, 0x6C, 0x56, 0x47, 0x50, 0x6F, 0x74, 0x34,
    0x4D, 0x42, 0x45, 0x4C, 0x7A, 0x43, 0x38, 0x66, 0x4C, 0x55, 0x44, 0x69, 0x41, 0x43, 0x49, 0x54,
    0x37, 0x75, 0x31, 0x58, 0x31, 0x62, 0x68, 0x65, 0x71, 0x6C, 0x35, 0x59, 0x7A, 0x43, 0x30, 0x6C,
    0x67, 0x2F, 0x4B, 0x48, 0x5A, 0x7A, 0x62, 0x36, 0x6D, 0x63, 0x74, 0x4E, 0x2B, 0x34, 0x62, 0x52,
    0x74, 0x79, 0x4B, 0x35, 0x75, 0x52, 0x52, 0x4A, 0x70, 0x48, 0x45, 0x56, 0x63, 0x4B, 0x58, 0x57,
    0x50, 0x34, 0x30, 0x73, 0x31, 0x79, 0x38, 0x37, 0x75, 0x30, 0x6D, 0x49, 0x50, 0x4A, 0x6E, 0x73,
    0x39, 0x6D, 0x4F, 0x2F, 0x2F, 0x44, 0x41, 0x35, 0x4C, 0x32, 0x6D, 0x64, 0x77, 0x56, 0x79, 0x73,
    0x72, 0x74, 0x4B, 0x51, 0x69, 0x51, 0x37, 0x36, 0x57, 0x6A, 0x74, 0x59, 0x51, 0x63, 0x41, 0x73,
    0x46, 0x2B, 0x42, 0x54, 0x4E, 0x56, 0x48, 0x62, 0x41, 0x6E, 0x7A, 0x7A, 0x52, 0x75, 0x6C, 0x52,
    0x61, 0x43, 0x45, 0x78, 0x2B, 0x6E, 0x30, 0x49, 0x6A, 0x35, 0x34, 0x49, 0x45, 0x41, 0x4F, 0x75,
    0x55, 0x4B, 0x70, 0x6F, 0x61, 0x48, 0x71, 0x6F, 0x56, 0x4F, 0x33, 0x51, 0x42, 0x36, 0x52, 0x41,
    0x51, 0x7A, 0x4D, 0x67, 0x70, 0x44, 0x73, 0x41, 0x30, 0x58, 0x34, 0x4C, 0x6A, 0x4F, 0x32, 0x52,
    0x2B, 0x4D, 0x4B, 0x6F, 0x6D, 0x6F, 0x6C, 0x52, 0x5A, 0x6F, 0x32, 0x34, 0x57, 0x32, 0x41, 0x35,
    0x57, 0x2B, 0x30, 0x56, 0x4A, 0x77, 0x45, 0x41, 0x41, 0x51, 0x41, 0x3D, 0x20, 0x75, 0x6E, 0x6B,
    0x6E, 0x6F, 0x77, 0x6E, 0x40, 0x75, 0x6E, 0x6B, 0x6E, 0x6F, 0x77, 0x6E, 0x00
};
#endif
