#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <openssl/evp.h>
#include <openssl/bio.h>

const EVP_CIPHER *cipher;

unsigned char key[] = {
	0x40, 0x46, 0x4C, 0x5C, 0x2D, 0x4B, 0xED, 0x04,
	0xE6, 0xFC, 0x1A, 0x06, 0x56, 0x13, 0xD3, 0xA3,
	0xBF, 0x8C, 0x16, 0x84, 0xDB, 0x3B, 0x20, 0x90,
	0xF8, 0xEA, 0x58, 0x15, 0xDB, 0x9D, 0x4C, 0xEB
};
#if 1
char packet_bytes[] = {
	0xf0, 0x95, 0x33, 0x8b, 0xe5, 0xff, 0x9e, 0xf4,
	0x14, 0xd2, 0xfa, 0x0b, 0x37, 0xd5, 0xb5, 0x1b,
	0x56, 0x9c, 0xc3, 0xeb, 0x99, 0x42, 0xa1, 0xa1,
	0xbd, 0xa4, 0xcd, 0xac, 0x42, 0x44, 0x8e, 0xb6,
	0x7c, 0xdf, 0x13, 0x1b, 0x14, 0xff, 0xf4, 0x17,
	0xc4, 0x54, 0xdc, 0x57, 0xff, 0x61, 0x0f, 0x7f,
	0x9e, 0xbc, 0xda, 0xee, 0x3a, 0x36, 0x19, 0xda,
	0x72, 0x72, 0x5e, 0x0c, 0x1a, 0xbe, 0x90, 0x7f,
	0x55, 0xe1, 0x65, 0x5e, 0x51, 0x5f, 0x18, 0xe4,
	0xff, 0x1c, 0x3d, 0xc4, 0xef, 0xe9, 0x32, 0x5e,
	0x00, 0x2c, 0xb9, 0xaa, 0xea, 0x00, 0xbe, 0x81,
	0x92, 0x54, 0xe2, 0xbe, 0x0e, 0x1c, 0x78, 0x7e,
	0x13, 0x6c, 0xfe, 0x06, 0x49, 0x3d, 0x8c, 0x65,
	0x48, 0xf6, 0x78, 0xab, 0xf4, 0x17, 0x6a, 0xf4,
	0xab, 0xc1, 0x51, 0xef, 0xd9, 0x26, 0xf1, 0x83,
	0xce, 0x3c, 0x10, 0xed, 0xc8, 0xb0, 0x74, 0x34,
	0x0c, 0x13, 0xc0, 0xa5, 0xb2, 0xd8, 0x75, 0xbe,
	0x3b, 0x78, 0xb6, 0x53, 0xbe, 0xdc, 0x0b, 0x24,
	0xcf, 0x4d, 0xfd, 0x45, 0xd8, 0x43, 0x71, 0x02,
	0x5c, 0xa3, 0xcb, 0x17, 0xb7, 0xba, 0x73, 0x6b,
	0x56, 0xc5, 0xb2, 0xde, 0x88, 0x96, 0xf3, 0xc0,
	0xf8, 0xf9, 0xe2, 0xbf, 0x90, 0x5c, 0x7b, 0xba,
	0x2a, 0x0b, 0xbc, 0x82, 0x03, 0xc1, 0x51, 0x0e,
	0x4b, 0x56, 0x7c, 0xc0, 0xe9, 0x9e, 0x92, 0x64,
	0x46, 0x10, 0x23, 0xce, 0xa6, 0x4b, 0x13, 0xa0,
	0x2c, 0xb9, 0x82, 0xb9, 0xcf, 0x66, 0x6c, 0x6a,
	0x32, 0x6d, 0xbe, 0x81, 0x05, 0x69, 0x83, 0x1d,
	0x0f, 0x8d, 0xd5, 0xb7, 0x04, 0x72, 0x93, 0x46,
	0xfc, 0x43, 0x0c, 0xbb, 0x8e, 0x3a, 0xba, 0x37,
	0xbf, 0x9d, 0x4e, 0x25, 0xf4, 0x8a, 0x39, 0x4b,
	0x6b, 0x1b, 0xd1, 0xa7, 0x5e, 0xd8, 0x0c, 0xb0,
	0x6f, 0x4f, 0x7c, 0xee, 0xe8
};
#endif

#if 0
char packet_bytes[] = {
	0x8f, 0x03, 0x80, 0x91, 0xca, 0xc5, 0xa7, 0xad,
	0x8d, 0x1c, 0xc2, 0xd8, 0x18, 0xca, 0xf5, 0x4d,
	0xeb, 0x9d, 0x8d, 0x45, 0x14, 0xa0, 0x0a, 0xca,
	0x8e, 0xb2, 0xd1, 0xbf, 0x1b, 0x40, 0x37, 0x28,
	0xc3, 0xb6, 0xfe, 0xe5, 0xd2, 0x27, 0x6b, 0xaa,
	0xaa, 0x04, 0x29, 0x23, 0x23, 0x08, 0xd4, 0xc0,
	0x3f, 0x74, 0x13, 0xdf, 0x2e, 0x89, 0x31, 0x23,
	0x06, 0x9a, 0xb9, 0x9d, 0x59, 0x48, 0x64, 0xb0,
	0x0c, 0xb5, 0xae, 0xfe, 0xfb, 0x00, 0x8d, 0x5d,
	0x7e, 0xb5, 0x14, 0xaa, 0x0a, 0x6a, 0xb7, 0x1b,
	0x3b, 0x53, 0xc4, 0x7e, 0xae, 0xfd, 0x24, 0x8e,
	0x79, 0xc5, 0xc6, 0x72, 0xb3, 0xcb, 0x2d, 0xf1,
	0xcf, 0xbd, 0x37, 0xdf, 0xb5, 0x4a, 0x5f, 0xfb,
	0x1c, 0x11, 0xf9, 0x6a, 0xbe, 0x0f, 0x64, 0x35,
	0xfc, 0xe2, 0x30, 0x94, 0xa7, 0xc1, 0x1a, 0xc9,
	0x87, 0xea, 0x8d, 0x63, 0xdc, 0x12, 0xc0, 0xd3,
	0x98, 0x8a, 0xa0, 0xa7, 0x84, 0xd3, 0xe2, 0x9e,
	0x4e, 0x5d, 0x9e, 0xda, 0x3e, 0x8b, 0x15, 0xe0,
	0x2b, 0xf6, 0x75, 0x57, 0x1c, 0x74, 0x89, 0x8c,
	0x94, 0xf9, 0x71, 0xe8, 0x27, 0xb5, 0xbb, 0xfa,
	0xb9, 0xfe, 0xcc, 0x50, 0x49, 0x6f, 0xa9, 0x53,
	0xe4, 0x32, 0x5e, 0xf8, 0x6a, 0x4c, 0x36, 0x52,
	0x95, 0x88, 0xf5, 0x20, 0x5c, 0xdb, 0x42, 0x13,
	0xde, 0x60, 0xdd, 0xa3, 0x22, 0x3a, 0x8f, 0x35,
	0x1c, 0xea, 0xb1, 0x6d, 0x36, 0x07, 0x11, 0x25,
	0x28, 0xe6, 0x82, 0xca, 0x91, 0xce, 0x7a, 0x3b,
	0xf2, 0x6d, 0xa9, 0x48, 0xc1, 0x28, 0x4c, 0xd3,
	0x8c, 0xf4, 0x45, 0x03, 0x96, 0x4e, 0xc3, 0xaf,
	0x83, 0x43, 0xc6, 0x8e, 0xfd, 0x48, 0x8a, 0x01,
	0xee, 0xcc, 0x63, 0xc2, 0x9c, 0x49, 0xd1, 0xed,
	0x8a, 0x6e, 0x59, 0xd1, 0xf3, 0xfd, 0x7b, 0x04,
	0x7b, 0xdf, 0xff, 0xa8, 0x28, 0x7e, 0x21, 0x09,
	0x57, 0xef, 0x45, 0xbe, 0x17, 0x28, 0xe1, 0xad,
	0xec, 0x93, 0xb2, 0x84, 0x4b, 0x07, 0x56, 0x20,
	0x0d, 0xda, 0x08, 0x9d, 0xc1, 0xc9, 0x69, 0xbe,
	0x1a, 0x0a, 0xc9, 0xe2, 0xf3, 0x39, 0x1a, 0x15,
	0xd0, 0x33, 0xb2, 0x49, 0xbb, 0xf9, 0xd3, 0x53,
	0x10, 0x5d, 0xfa, 0x13, 0x8b, 0x5b, 0xde, 0x69,
	0x99, 0xa7, 0x12, 0x8e, 0xa3, 0xbb, 0x05, 0x5c,
	0x4d, 0x21, 0x85, 0x7b, 0xfa, 0x76, 0x53, 0x4f,
	0xf5, 0x6e, 0x88, 0x2d, 0x83, 0x94, 0x93, 0x24,
	0x7c, 0x46, 0x8b, 0xfc, 0xcc, 0x5a, 0x4f, 0x1a,
	0x76, 0x8b, 0xd7, 0x3d, 0xb9, 0x15, 0x77, 0x55,
	0xac, 0x7a, 0xac, 0xcd, 0x42, 0x4f, 0x10, 0xff,
	0x35, 0x00, 0x18, 0x1a, 0x50, 0x03, 0xb9, 0xb6,
	0xb6, 0xcc, 0x31, 0x06, 0x20, 0xe5, 0xc0, 0x2d,
	0x62, 0x3a, 0x98, 0x36, 0xfc, 0xb6, 0x0e, 0xed,
	0x72, 0x09, 0xd5, 0xef, 0x0c, 0x7b, 0x21, 0x24,
	0xd0, 0x26, 0x81, 0xda, 0x11, 0x87, 0x3e, 0xfd,
	0xb0, 0x26, 0xea, 0xa1, 0xb5, 0x7c, 0x6d, 0xdf,
	0x06, 0x50, 0x7b, 0x50, 0xf8, 0xfc, 0xb5, 0xd0,
	0x29, 0x49, 0x66, 0x62, 0x1c, 0x63, 0x96, 0xe9,
	0xab, 0x18, 0x4f, 0x13, 0x77, 0x21, 0x3d, 0x10,
	0x33, 0x03, 0xe3, 0xe2, 0xbc, 0xa3, 0xc4, 0xf6,
	0x35, 0x68, 0x20, 0xd4, 0x9f, 0x06, 0xd6, 0x79,
	0x11, 0x75, 0x06, 0xfe, 0xf6, 0x7b, 0x3b, 0x31,
	0x33, 0x7c, 0xea, 0x91, 0x3a, 0x76, 0x2a, 0x00,
	0xbe, 0x82, 0xa1, 0x8c, 0xc6, 0x90, 0xde, 0xf0,
	0xfc, 0xb2, 0x3a, 0x0d, 0xe3, 0xe4, 0x13, 0xc7,
	0x7d, 0xd0, 0xe8, 0x91, 0xde, 0x71, 0x28, 0xfc,
	0x42, 0xe1, 0x1a, 0xb7, 0x07, 0x3b, 0x8e, 0x82,
	0x2c, 0xfe, 0x3e, 0x3f, 0x8b, 0xd6, 0x60, 0x26,
	0x8f, 0x28, 0x90, 0x6b, 0x78, 0x1b, 0x56, 0x5e,
	0x11, 0xcd, 0x52, 0x23, 0xad, 0xd9, 0x11, 0xf5,
	0xf6, 0x86, 0xda, 0x33, 0x33, 0x40, 0x31, 0xd7,
	0x5c, 0x8c, 0xff, 0x75, 0x0e, 0xe6, 0xdd, 0x04,
	0xe0, 0x25, 0x38, 0xda, 0x88, 0x19, 0xfa, 0x10,
	0x09, 0x70, 0x65, 0x90, 0xc1, 0x5c, 0xd6, 0xa5,
	0x9d, 0x9f, 0xc6, 0x1d, 0xcd, 0xb5, 0xb8, 0xe1,
	0x2e, 0x3b, 0xb7, 0xb0, 0xee, 0xa2, 0x47, 0xb4,
	0x14, 0x83, 0x44, 0x2f, 0x50, 0x7c, 0xae, 0xc0,
	0xe3, 0x2c, 0x57, 0xf5, 0x59, 0xe2, 0x58, 0x79,
	0xe0, 0xa9, 0x4f, 0xa3, 0x64, 0xe9, 0xad, 0x9e,
	0x19, 0xa0, 0x89, 0x82, 0xe6, 0xa0, 0x15, 0xc3,
	0x58, 0xe6, 0xf4, 0xb4, 0x95, 0x52, 0x54, 0x6c,
	0x47, 0xbb, 0x6d, 0x05, 0x08, 0x0f, 0x0f, 0x33,
	0x1e, 0xe7, 0xf2, 0x70, 0xb7, 0x84, 0x5d, 0xd4,
	0x9c, 0xde, 0xd8, 0xf1, 0x9c, 0xf2, 0x09, 0xf6,
	0x89, 0x7f, 0xd9, 0x10, 0x51, 0x26, 0x84, 0x26,
	0xd9, 0x00, 0x11, 0xd8, 0x70, 0xd3, 0xd4, 0x57,
	0x4e, 0x54, 0x21, 0xef, 0x62, 0x53, 0x8e, 0x92,
	0xe3, 0xf9, 0xc4, 0x17, 0x3b, 0x53, 0xef, 0xab,
	0x81, 0x79, 0x10, 0x65, 0xcb, 0x7e, 0xc2, 0x35,
	0x0f, 0xc4, 0x9f, 0x16, 0xe0, 0x6f, 0x2c, 0xeb,
	0x80, 0x9f, 0x9c, 0xe7, 0xbf, 0x5e, 0x85, 0xa0,
	0x1d, 0x1d, 0x1e, 0xfb, 0xc7, 0x48, 0x35, 0x65,
	0xd3, 0x53, 0x02, 0x6a, 0x39, 0x08, 0xed, 0x48,
	0x40, 0xde, 0xc8, 0x38, 0xa1, 0x9a, 0x28, 0xa3,
	0xec, 0x07, 0x0d, 0x86, 0x1a, 0x93, 0x67, 0xb9,
	0x9e, 0xf2, 0xf4, 0xb1, 0xac, 0xef, 0x06, 0x9c,
	0xf4, 0xc3, 0xd9, 0xd6, 0xdc, 0x40, 0xb8, 0xab,
	0x17, 0xb2, 0x53, 0xc1, 0x45, 0xc5, 0x40, 0xf8,
	0x0e, 0xb2, 0x87, 0x0b, 0x93, 0x3d, 0xfd, 0x02,
	0x08, 0x34, 0x9c, 0x34, 0x54, 0x99, 0xcd, 0x0b,
	0x1b, 0x5e, 0x99, 0x58, 0x19, 0xaa, 0xb8, 0xf3,
	0xc9, 0xca, 0xde, 0xb5, 0x93, 0xf1, 0x46, 0xbf,
	0xdb, 0x2a, 0x49, 0x53, 0x33, 0xe4, 0x2f, 0x4e,
	0x4a, 0x09, 0x62, 0x88, 0x07, 0x64, 0xdf, 0x4e,
	0x78, 0x66, 0x1b, 0xef, 0x72, 0x74, 0x5f, 0x60,
	0x3e, 0x4e, 0x7d, 0xd0, 0x73, 0x40, 0xd3, 0x99,
	0xae, 0xf0, 0xf1, 0x31, 0xbf, 0x8d, 0xab, 0xd4,
	0xc0, 0x9e, 0x72, 0xe1, 0x13, 0x95, 0xe7, 0x9e,
	0x2b, 0xc8, 0xf0, 0xcd, 0xd1, 0xc4, 0x52, 0x14,
	0xd6, 0x33, 0xc5, 0xb0, 0x9b, 0x90, 0x1e, 0x41,
	0xcd, 0xc9, 0x08, 0x82, 0x33, 0xd5, 0x4b, 0xf1,
	0x35, 0x62, 0x3a, 0x4b, 0x9e, 0xe5, 0xeb, 0x65,
	0x0b, 0x1c, 0x9f, 0x84, 0x5e, 0xa8, 0x78, 0xd3,
	0x49, 0xe9, 0x38, 0x08, 0xcf, 0x20, 0xe3, 0x68,
	0xcb, 0xc8, 0x46, 0x00, 0x38, 0xf6, 0x12, 0x2b,
	0xa3, 0x8e, 0xd4, 0x3f, 0x8b, 0xa1, 0x6a, 0x82,
	0x2c, 0x53, 0x81, 0x04, 0x72, 0x2d, 0xf3, 0x57,
	0x4b, 0x61, 0x63, 0x24, 0x99, 0x11, 0xb0, 0x6f,
	0x0d, 0x4c, 0x6e, 0x6a, 0x2e, 0x5b, 0x26, 0xe4,
	0x85, 0xcb, 0x0c, 0x0c, 0x20, 0x51, 0xe4, 0x11,
	0xb8, 0xbf, 0xfe, 0x71, 0xd7, 0x91, 0x5f, 0x7f,
	0xf1, 0x49, 0xdb, 0x3f, 0x65, 0x57, 0x7a, 0xc8,
	0x68, 0x7b, 0xc0, 0x57, 0xba, 0x1b, 0x95, 0x9c,
	0x44, 0x3e, 0xf7, 0xf2, 0x50, 0xb6, 0xc3, 0xe1,
	0x12, 0x9e, 0x5e, 0xcb, 0x4d, 0x32, 0xe4, 0xe3,
	0x7c, 0x8c, 0xa7, 0x2a, 0x16, 0xdf, 0x14, 0xfb,
	0xef, 0x02, 0xde, 0xdf, 0x9a, 0x57, 0x32, 0xe0,
	0x43, 0x0d, 0x20, 0x8d, 0x22, 0xcc, 0x51, 0x6b,
	0x65, 0x64, 0x46, 0xc3, 0x7d, 0x23, 0x1e, 0x96,
	0xcc, 0xdb, 0xd2, 0xbc, 0x39, 0xd8, 0x50, 0xa5,
	0xa0, 0xeb, 0x90, 0xa5, 0x2f, 0x08, 0x47, 0x51,
	0x97, 0x79, 0xe0, 0x3a, 0xa6, 0xd3, 0x86, 0x0d,
	0xb9, 0x95, 0x04, 0x3a, 0xce, 0xa9, 0x70, 0x4f,
	0xd6, 0xa9, 0x64, 0x77, 0xcb, 0x9a, 0xf4, 0xf0,
	0x09, 0xd1, 0x7d, 0x49, 0x8f, 0x69, 0xaa, 0xc1,
	0xc5, 0xd2, 0x02, 0x3d, 0x4d, 0x9a, 0x0b, 0x3b,
	0x18, 0xb1, 0xd9, 0x15, 0xb2, 0xf5, 0x20, 0xdf,
	0xa4, 0x51, 0x5a, 0x0a, 0xe4, 0x40, 0x8f, 0x3d,
	0xd3, 0x0b, 0xc7, 0xc7, 0x6a, 0x71, 0xc3, 0x02,
	0xbe, 0x1b, 0x7f, 0xae, 0xd7, 0x60, 0x2f, 0x09,
	0x26, 0x34, 0x65, 0x8e, 0x54, 0x64, 0x9c, 0x59,
	0xec, 0x12, 0x30, 0x06, 0x1f, 0xfe, 0x5d, 0xd6,
	0x26, 0x8f, 0xc5, 0x40, 0x86, 0x24, 0xbd, 0x58,
	0x22, 0x55, 0x5b, 0x1b, 0xb5, 0x47, 0x33, 0x14,
	0x9b, 0xed, 0xf6, 0xdf, 0x3a, 0x5f, 0xcd, 0x2a,
	0x0b, 0x25, 0x07, 0x1c, 0xc7, 0xd9, 0x7b, 0x6e,
	0x37, 0x2a, 0xe3, 0xeb, 0x72, 0x68, 0x8d, 0xd0,
	0x70, 0x90, 0xce, 0x9b, 0x23, 0x23, 0xcd, 0xcb,
	0x69, 0x73, 0x22, 0xbc, 0x90, 0x8a, 0x0c, 0x12,
	0x04, 0xb5, 0xab, 0x81, 0xda, 0x8a, 0xe7, 0x87,
	0xa0, 0xa3, 0x33, 0xf1, 0xcf, 0xa8, 0x2a, 0xd0,
	0x8d, 0x77, 0x9e, 0x23, 0x94, 0x7b, 0x8b, 0xd0,
	0xa9, 0xc5, 0x66, 0x7a, 0x40, 0xc3, 0xe6, 0x3b,
	0xf3, 0x14, 0x1d, 0x35, 0x18, 0xc5, 0x7f, 0x5b,
	0x95, 0xec, 0x43, 0x89, 0x99, 0xec, 0x98, 0xa1,
	0x74, 0x01, 0xa8, 0x04, 0x4e, 0xdd, 0xb4, 0x09,
	0x45, 0x8b, 0x32, 0xaa, 0x6e, 0x4a, 0xbf, 0xaa,
	0x76, 0x60, 0x10, 0x64, 0x98, 0xd1, 0xff, 0xbd,
	0x0e, 0x8d, 0x07, 0x96, 0x38, 0xea, 0x9e, 0xa9,
	0x9f, 0xac, 0x63, 0xa1, 0x32, 0xec, 0x37, 0x41,
	0x7c, 0x60, 0x84, 0x9e, 0x5f, 0xc4, 0xdf, 0x93,
	0x7a, 0xa1, 0x89, 0x83, 0xa7, 0xe4, 0x57, 0xfc,
	0xef, 0xd0, 0xed, 0xe1, 0x9c, 0x5d, 0xfd, 0x57,
	0x8a, 0x1c, 0x02, 0x0c, 0x9d, 0xf9, 0xce, 0xa7,
	0x64, 0xf1, 0xfd, 0xa8, 0x26, 0x79, 0x24, 0xd8,
	0x9a, 0x42, 0x1f, 0x98, 0x97, 0x26, 0xca, 0x36,
	0x49, 0x9c, 0xaa, 0xc4, 0x03, 0x45, 0x77, 0xb3,
	0x81, 0xe6, 0x05, 0x30, 0x67, 0xeb, 0x6e, 0xef,
	0x2e, 0xcf, 0xe3, 0x11, 0xf8, 0x70, 0xc8, 0x9f,
	0x51, 0x70, 0xa5, 0x92, 0x28, 0x6a, 0x8f, 0x59,
	0xd5, 0x02, 0xbd, 0x6a, 0xa3, 0x13, 0xbf, 0xa2,
	0x3b, 0xf8, 0xd6, 0xfd, 0x98, 0xa8, 0x81, 0x41,
	0x9f, 0x16, 0xdd, 0xc0, 0x35, 0xdc, 0x36, 0x8a,
	0x63, 0xd8, 0xd8, 0x1b, 0x06, 0xbe, 0x83, 0x45,
	0xe9, 0x3c, 0xde, 0x44, 0xf3, 0x55, 0xcf, 0xb2,
	0x5b, 0xe4, 0xf8, 0x53, 0x8c, 0x2d, 0x09, 0x18,
	0xb1, 0x36, 0x05, 0xdd, 0x48, 0xac, 0x67, 0xf8,
	0x47, 0x08, 0x8e, 0xf3, 0xda, 0x74, 0x1a, 0xe1,
	0x1f, 0xad, 0x8f, 0x6f, 0x4a, 0xdb, 0xf0, 0xa3,
	0x7d, 0x13, 0x42, 0x77, 0x20, 0xb8, 0xb3, 0xbd,
	0xa9, 0xfc, 0x48, 0x41, 0x00, 0x06, 0xbe, 0x36,
	0x2d, 0x95, 0xbc, 0x5d, 0xf4, 0xe4, 0x4e, 0xbe,
	0x62, 0xbc, 0x43, 0xbd, 0x66, 0x7b, 0x95, 0xdb,
	0x7f
};
#endif
#if 0
char packet_bytes[] = {
	0x25, 0x0d, 0xfb, 0x5a, 0xf0, 0x28, 0xa5, 0x16,
	0x5d, 0xbc, 0xb1, 0xbb, 0x16, 0xd9, 0x8f, 0xf2,
	0x75, 0x1a, 0x6c, 0xc0, 0x81, 0x05, 0x8f, 0x06,
	0x23, 0x92, 0x0a, 0x92, 0x71, 0xdf, 0xca, 0x30,
	0xd9, 0xfd, 0x6d, 0xf6, 0x8f, 0x55, 0x88, 0x75,
	0x7e, 0xdb, 0x85, 0x9a, 0xf1, 0xb3, 0x0d, 0x3b,
	0x51, 0x56, 0x80, 0xbe, 0xb8, 0x46, 0x9b, 0x99,
	0x19, 0xc7, 0x97, 0xec, 0x7a, 0x35, 0xb2, 0x25,
	0x0f, 0xfe, 0x4d, 0x99, 0x81, 0xdf, 0xd6, 0x8c,
	0x72, 0xa8, 0x3f, 0xc5, 0x10, 0x2a, 0xfe, 0xb5,
	0x9b, 0x8d, 0xf6, 0x3d, 0x4d, 0x36, 0xe2, 0x6c,
	0xfc, 0x2e, 0x2d, 0x3a, 0xe1, 0x3d, 0x68, 0xb6,
	0x11, 0x9a, 0x77, 0x2c, 0x4d, 0x8c, 0x1f, 0xff,
	0x0b, 0x7e, 0x0d, 0x8a, 0x2f, 0x86, 0xa9, 0x8e,
	0x2c, 0x2c, 0x31, 0x78, 0x42, 0x50, 0x44, 0x71,
	0x1a, 0x2b, 0xf1, 0x75, 0xc3, 0x64, 0xe7, 0x26,
	0x1e, 0xee, 0x12, 0xab, 0x3c, 0x7f, 0x23, 0xed,
	0x6c, 0xb3, 0xd4, 0xdb, 0x8a, 0xb1, 0xa8, 0x1f,
	0x07, 0xad, 0x5e, 0x3c, 0x4e, 0x38, 0x7c, 0x7e,
	0xb4, 0x57, 0x9e, 0x9a, 0x5b, 0x94, 0x46, 0x2a,
	0x73, 0xb2, 0x61
};

char packet_bytes[] = {
	0xa1, 0x01, 0xd9, 0x5d, 0xe7, 0xd2, 0x4b, 0xae,
	0x9f, 0xfa, 0x80, 0xf6, 0xe7, 0x1d, 0x88, 0xcb,
	0xac, 0x25, 0xef, 0xd1, 0xce, 0x2b, 0xbb, 0x6f,
	0x45, 0xcb, 0x53, 0xd4, 0x11, 0x3a, 0x69, 0xc1,
	0xb1, 0x2e, 0x12, 0x7e, 0x1b, 0x7e, 0xdb, 0x00,
	0x60, 0xd9, 0x82, 0x77, 0x1d, 0x6b, 0xf6, 0x88,
	0x10, 0x6b, 0xa2, 0x0e, 0xd9, 0xeb, 0x07, 0x2e,
	0x2a, 0x3b, 0x92, 0x7c, 0x83, 0x7d, 0x81, 0x43,
	0xa8, 0x28, 0xf9, 0x77, 0xc6, 0x51, 0x97, 0x18,
	0x5a, 0x9b, 0xa0, 0xd7, 0x1d, 0x3c, 0x8c, 0xf1,
	0x74, 0xf6, 0x41, 0xfc, 0xb4, 0xa1, 0xad, 0xda,
	0x17, 0xd7, 0xe4, 0xc5, 0x9b, 0x11, 0x17, 0xc1,
	0x69, 0x14, 0x42, 0xfc, 0x3b, 0xd8, 0x5c, 0x60,
	0x6c, 0xc0, 0xf7, 0xa5, 0x22, 0x03, 0x20, 0x60,
	0x9c, 0xf2, 0x10, 0xc3, 0xd0, 0x00, 0x01, 0x58,
	0x27, 0x81, 0xdf, 0x91, 0xe1, 0x35, 0x4c, 0x9b,
	0x89, 0x88, 0x19, 0x2a, 0xa4, 0x9c, 0xcc, 0x24,
	0x8f, 0xc0, 0xe3, 0xe5, 0x50, 0xfc, 0x4e, 0x96,
	0x94, 0xb0, 0xdb, 0xcf, 0xa7, 0xa2, 0x0f, 0xb6,
	0x7b, 0x97, 0xea, 0x31, 0xee, 0xdc, 0x86, 0x08,
	0x5f, 0x57, 0x02, 0xd3, 0xb4, 0x79, 0xe1, 0xc2,
	0xb9, 0x8d, 0xda, 0xfb, 0x53, 0x7b, 0xb9, 0xeb,
	0xbb, 0xc3, 0x76, 0xb9, 0x82, 0x2e, 0x4a, 0x1c,
	0x9f, 0xc5, 0x76, 0x76, 0x8a, 0x85, 0xf8, 0x8a,
	0x9e, 0x26, 0x36, 0x0a, 0x73, 0xc2, 0xe7, 0x9f,
	0xeb, 0x3d, 0xfc, 0x42, 0xea, 0x4c, 0xac, 0xbd,
	0x96, 0xda, 0x13, 0xd4, 0xcf, 0x9d, 0x24, 0xd4,
	0x99, 0x0f, 0x4f, 0x4d, 0xfd, 0xb6, 0x46, 0x1b,
	0xef, 0x05, 0x93, 0x08, 0x74, 0x12, 0xb2, 0x4e,
	0x28, 0x35, 0x2c, 0xbc, 0x9c, 0x0c, 0x51, 0xd8,
	0xd6, 0xcf, 0x74, 0xc9, 0xc1, 0xc2, 0x15, 0x89,
	0xff, 0x65, 0xf2, 0x2e, 0xbc, 0xf1, 0x8c, 0x75,
	0xd8, 0xdd, 0xa7, 0x12, 0xf4, 0x1a, 0x96, 0x1a,
	0x20, 0x95, 0xaf, 0x97, 0xd7, 0x08, 0x1a, 0x73,
	0xd6, 0xf4, 0xe3, 0x70, 0x04, 0x73, 0x34, 0x8d,
	0xde, 0x41, 0xb4, 0x92, 0x2c, 0xde, 0xef, 0xee,
	0x74, 0xeb, 0xfd, 0xc1, 0x88, 0x56, 0x99, 0x0a,
	0x1d, 0x77, 0x1d, 0x7b, 0xe0, 0x5c, 0x39, 0x5b,
	0xc0, 0xb6, 0xf2, 0xf4, 0x4d, 0x27, 0xc8, 0x4a,
	0x96, 0xa3, 0x1d, 0x7c, 0xd2, 0x62, 0x6f, 0x5d,
	0x09, 0x0d, 0x4c, 0x36, 0x39, 0xd1
};

unsigned char packet_bytes[] = {
	0x30, 0x07, 0x22, 0x9b, 0x10, 0x9d, 0x0d, 0x8e,
	0xa2, 0x0e, 0xb9, 0xf3, 0x11, 0x15, 0x67, 0x65,
	0xa0, 0x3d, 0x79, 0xca, 0x08, 0xf7, 0xfa, 0x56,
	0x69, 0xac, 0xd9, 0x4c, 0x40, 0x93, 0x08, 0xb8,
	0xbe, 0x43, 0xd1, 0xd5, 0xb5, 0xd9, 0xc5, 0x03,
	0x4f, 0x09, 0x03, 0xd9, 0x0e, 0x3c, 0x27, 0x8b,
	0xd4, 0xb6, 0x3a, 0x6d, 0xf6, 0x1f, 0x6e, 0xf7,
	0x5f, 0xf0, 0x68, 0xe4, 0xde, 0x3d, 0x40, 0x00,
	0x40, 0x9a, 0x8a
};

char packet_bytes[] = {
	0x03, 0x4f, 0x09, 0x03, 0xd9, 0x0e, 0x3c, 0x27,
	0x8b, 0xd4, 0xb6, 0x3a, 0x1a, 0x66, 0x13, 0x2c,
	0xe0, 0x11, 0x0f, 0xb3, 0x64, 0x42, 0xf4, 0x28,
	0x05, 0x92, 0x81, 0xe6, 0x72, 0x71, 0x1e, 0x3b,
	0x4d, 0x3e, 0x21, 0xb7, 0x6f, 0x0c, 0x78, 0xb7,
	0xd3, 0x06, 0xf6, 0x84, 0xe3, 0x3c, 0xe8, 0xde,
	0x35, 0xf8, 0x9d, 0xee, 0xe6, 0x78, 0xe2, 0xc2,
	0x3c
};
#endif

#if 0
unsigned char encmsg[] = {
	0x11, 0x15, 0x67, 0x65,
	0xa0, 0x3d, 0x79, 0xca, 0x08, 0xf7, 0xfa, 0x56,
	0x69, 0xac, 0xd9, 0x4c, 0x40, 0x93, 0x08, 0xb8,
	0xbe, 0x43, 0xd1, 0xd5, 0xb5, 0xd9, 0xc5, 0x03,
	0x4f, 0x09, 0x03, 0xd9, 0x0e, 0x3c, 0x27, 0x8b,
	0xd4, 0xb6, 0x3a
};

unsigned char iv[] = {
	0x30, 0x07, 0x22, 0x9b, 0x10, 0x9d, 0x0d, 0x8e,
	0xa2, 0x0e, 0xb9, 0xf3
};

unsigned char tag[] = {
	0x6d, 0xf6, 0x1f, 0x6e, 0xf7, 0x5f, 0xf0, 0x68, 
	0xe4, 0xde, 0x3d, 0x40, 0x00, 0x40, 0x9a, 0x8a
};
#endif

int main(int argc, char *argv[])
{
	unsigned int  size = sizeof(packet_bytes);
	unsigned char plaintext[4096] = {0};

	unsigned char *iv = packet_bytes;
	unsigned char *src = packet_bytes + 12;
	unsigned char *tag = packet_bytes + size - 16;
	unsigned int iv_len = 12;
	unsigned int tag_size = 16;
	unsigned int src_size = size - 16 -12;

	int outl;
	// New CTX
	EVP_CIPHER_CTX *ctx;
	ctx = EVP_CIPHER_CTX_new();

	// Select cipher
	cipher = EVP_get_cipherbyname("ChaCha20-Poly1305");
	EVP_DecryptInit_ex(ctx, cipher, NULL, NULL, NULL);

	// Set IV length
	EVP_CIPHER_CTX_ctrl(ctx, EVP_CTRL_AEAD_SET_IVLEN, 12, NULL);

	// Set Key and IV
	EVP_DecryptInit_ex(ctx, NULL, NULL, key, iv);

	// Decrypt
	EVP_DecryptUpdate(ctx, plaintext, &outl, src, src_size) ;
	BIO_dump_fp(stdout, plaintext, outl);

	// Verify
	int rv = 0;
	EVP_CIPHER_CTX_ctrl(ctx, EVP_CTRL_AEAD_SET_TAG, 16, tag);
	rv = EVP_DecryptFinal_ex(ctx, plaintext, &outl);
	printf("\nTag Verify %s\n", rv > 0 ? "Successful!" : "Failed!" );

	return 0;
}
