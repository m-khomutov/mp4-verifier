//
// Created by mkh on 19.11.2019.
//

#ifndef FMP4VERIFIER_ELEMENTARYSTREAMDESCRIPTORBOX_H
#define FMP4VERIFIER_ELEMENTARYSTREAMDESCRIPTORBOX_H

#include <vector>
#include <ostream>

/*
 *                http://xhelmboyx.tripod.com/formats/mp4-layout.txt
 *
 * -> 1 byte ES descriptor type tag = 8-bit hex value 0x03
   -> 3 bytes extended descriptor type tag string = 3 * 8-bit hex value types are Start = 0x80 ; End = 0xFE NOTE: the extended start tags may be left out
   -> 1 byte descriptor type length = 8-bit unsigned length

   -> 2 bytes ES ID = 16-bit unsigned value
   -> 1 byte stream priority = 8-bit unsigned value Defaults to 16 and ranges from 0 through to 31

   -> 1 byte decoder config descriptor type tag = 8-bit hex value 0x04
   -> 3 bytes extended descriptor type tag string = 3 * 8-bit hex value types are Start = 0x80 ; End = 0xFE NOTE: the extended start tags may be left out
   -> 1 byte descriptor type length = 8-bit unsigned length

   -> 1 byte object type ID = 8-bit unsigned value
     - type IDs are system v1 = 1 ; system v2 = 2
     - type IDs are MPEG-4 video = 32 ; MPEG-4 AVC SPS = 33
     - type IDs are MPEG-4 AVC PPS = 34 ; MPEG-4 audio = 64
     - type IDs are MPEG-2 simple video = 96
     - type IDs are MPEG-2 main video = 97
     - type IDs are MPEG-2 SNR video = 98
     - type IDs are MPEG-2 spatial video = 99
     - type IDs are MPEG-2 high video = 100
     - type IDs are MPEG-2 4:2:2 video = 101
     - type IDs are MPEG-4 ADTS main = 102
     - type IDs are MPEG-4 ADTS Low Complexity = 103
     - type IDs are MPEG-4 ADTS Scalable Sampling Rate = 104
     - type IDs are MPEG-2 ADTS = 105 ; MPEG-1 video = 106
     - type IDs are MPEG-1 ADTS = 107 ; JPEG video = 108
     - type IDs are private audio = 192 ; private video = 208
     - type IDs are 16-bit PCM LE audio = 224 ; vorbis audio = 225
     - type IDs are dolby v3 (AC3) audio = 226 ; alaw audio = 227
     - type IDs are mulaw audio = 228 ; G723 ADPCM audio = 229
     - type IDs are 16-bit PCM Big Endian audio = 230
     - type IDs are Y'CbCr 4:2:0 (YV12) video = 240 ; H264 video = 241
     - type IDs are H263 video = 242 ; H261 video = 243
    -> 6 bits stream type = 3/4 byte hex value
     - type IDs are object descript. = 1 ; clock ref. = 2
     - type IDs are scene descript. = 4 ; visual = 4
     - type IDs are audio = 5 ; MPEG-7 = 6 ; IPMP = 7
     - type IDs are OCI = 8 ; MPEG Java = 9
     - type IDs are user private = 32
    -> 1 bit upstream flag = 1/8 byte hex value
    -> 1 bit reserved flag = 1/8 byte hex value set to 1
    -> 3 bytes buffer size = 24-bit unsigned value
    -> 4 bytes maximum bit rate = 32-bit unsigned value
    -> 4 bytes average bit rate = 32-bit unsigned value

    -> 1 byte decoder specific descriptor type tag = 8-bit hex value 0x05
    -> 3 bytes extended descriptor type tag string = 3 * 8-bit hex value types are Start = 0x80 ; End = 0xFE NOTE: the extended start tags may be left out
    -> 1 byte descriptor type length = 8-bit unsigned length

    -> ES header start codes = hex dump

    -> 1 byte SL config descriptor type tag = 8-bit hex value 0x06
    -> 3 bytes extended descriptor type tag string = 3 * 8-bit hex value types are Start = 0x80 ; End = 0xFE NOTE: the extended start tags may be left out
    -> 1 byte descriptor type length = 8-bit unsigned length

    -> 1 byte SL value = 8-bit hex value set to 0x02
*/

class ElementaryStreamDescriptorBox {
public:
    ElementaryStreamDescriptorBox( std::ifstream& f, uint32_t sz );

private:
    uint8_t m_version;
    uint32_t m_flags;

    uint16_t m_esId;

    uint8_t m_objectType{0};
    uint8_t m_streamType{0};
    bool m_upstream{false};

    uint32_t m_maximumBitrate{0};
    uint32_t m_averageBitrate{0};
    std::vector< uint8_t > m_esHeaderStartCodes;

private:
    bool f_get_tag( std::ifstream& f, uint8_t tagType );

    friend std::ostream & operator <<( std::ostream& out, const ElementaryStreamDescriptorBox& stsd );
};


#endif //FMP4VERIFIER_ELEMENTARYSTREAMDESCRIPTORBOX_H
