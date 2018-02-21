#include <cbor.h>


#define CBOR_TYPE_MASK          0xE0    /* top 3 bits */
#define CBOR_INFO_MASK          0x1F    /* low 5 bits */

/* Major types (cf. section 2.1) */
/* Major type 0: Unsigned integers */
#define CBOR_UINT8_FOLLOWS      24      /* 0x18 */
#define CBOR_UINT16_FOLLOWS     25      /* 0x19 */
#define CBOR_UINT32_FOLLOWS     26      /* 0x1a */
#define CBOR_UINT64_FOLLOWS     27      /* 0x1b */

#define CBOR_BYTE_FOLLOWS       24      /* indicator that the next byte is part of this item */

/* Jump Table for Initial Byte (cf. table 5) */
#define CBOR_UINT       0x00            /* type 0 */
#define CBOR_NEGINT     0x20            /* type 1 */
#define CBOR_BYTES      0x40            /* type 2 */
#define CBOR_TEXT       0x60            /* type 3 */
#define CBOR_ARRAY      0x80            /* type 4 */
#define CBOR_MAP        0xA0            /* type 5 */
#define CBOR_TAG        0xC0            /* type 6 */
#define CBOR_7          0xE0            /* type 7 (float and other types) */

/* Major type 6: Semantic tagging */
#define CBOR_DATETIME_STRING_FOLLOWS        0
#define CBOR_DATETIME_EPOCH_FOLLOWS         1

/* Major type 7: Float and other types */
#define CBOR_FALSE      (CBOR_7 | 20)
#define CBOR_TRUE       (CBOR_7 | 21)
#define CBOR_NULL       (CBOR_7 | 22)
#define CBOR_UNDEFINED  (CBOR_7 | 23)
/* CBOR_BYTE_FOLLOWS == 24 */
#define CBOR_FLOAT16    (CBOR_7 | 25)
#define CBOR_FLOAT32    (CBOR_7 | 26)
#define CBOR_FLOAT64    (CBOR_7 | 27)
#define CBOR_BREAK      (CBOR_7 | 31)


#ifndef  htonl
#define htonl(x) ( ((x)<<24 & 0xFF000000UL) | \
                   ((x)<< 8 & 0x00FF0000UL) | \
                   ((x)>> 8 & 0x0000FF00UL) | \
                   ((x)>>24 & 0x000000FFUL) )
#endif // ! htonl

#ifndef  htonll
#define htonll(x) ((((uint64_t)htonl(x)) << 32) + htonl((x) >> 32))
#endif // ! htonll


/**
 * Convert double @p x to network format
 */
static uint64_t htond(double x)
{
    union u {
        double d;
        uint64_t i;
    } u = { .d = x };
    return htonll(u.i);
}

/**
 * Convert double @p x to host format
 */
static double ntohd(uint64_t x)
{
    union u {
        double d;
        uint64_t i;
    } u = { .i = htonll(x) };
    return u.d;
}

/**
 * Return additional info field value for input value @p val
 *
 * @return Byte with the additional info bits set
 */
static unsigned char uint_additional_info(uint64_t val)
{
    if (val < CBOR_UINT8_FOLLOWS) {
        return val;
    }
    else if (val <= 0xff) {
        return CBOR_UINT8_FOLLOWS;
    }
    else if (val <= 0xffff) {
        return CBOR_UINT16_FOLLOWS;
    }
    else if (val <= 0xffffffffL) {
        return CBOR_UINT32_FOLLOWS;
    }

    return CBOR_UINT64_FOLLOWS;
}

/**
 * Return the number of bytes that would follow the additional info field @p additional_info
 *
 * @param additional_info Must be in the range [CBOR_UINT8_FOLLOWS, CBOR_UINT64_FOLLOWS]
 */
static unsigned char uint_bytes_follow(unsigned char additional_info)
{
    if (additional_info < CBOR_UINT8_FOLLOWS || additional_info > CBOR_UINT64_FOLLOWS) {
        return 0;
    }

    static const unsigned char BYTES_FOLLOW[] = {1, 2, 4, 8};
    return BYTES_FOLLOW[additional_info - CBOR_UINT8_FOLLOWS];
}

static size_t encode_int(unsigned char major_type, Stream* s, uint64_t val)
{
    unsigned char additional_info = uint_additional_info(val);
    unsigned char bytes_follow = uint_bytes_follow(additional_info);
    s->write( (unsigned char) (major_type | additional_info));

    for (int i = bytes_follow - 1; i >= 0; --i) {
        s->write( (unsigned char) ((val >> (8 * i)) & 0xff));
    }

    return bytes_follow + 1;
}

static size_t encode_bytes(unsigned char major_type, Stream* s, const char *data, size_t length)
{
    size_t length_field_size = uint_bytes_follow(uint_additional_info(length)) + 1;
    size_t bytes_start = encode_int(major_type, s, (uint64_t) length);

    if (!bytes_start) {
        return 0;
    }

    s->write(data, length);
    return (bytes_start + length);
}

size_t cbor_serialize_array(Stream* stream, size_t array_length)
{
    /* serialize number of array items */
    return encode_int(CBOR_ARRAY, stream, array_length);
}

size_t cbor_serialize_map(Stream* stream, size_t map_length)
{
    /* serialize number of item key-value pairs */
    return encode_int(CBOR_MAP, stream, map_length);
}

size_t cbor_serialize_int(Stream* stream, int val)
{
    if (val >= 0) {
        /* Major type 0: an unsigned integer */
        return encode_int(CBOR_UINT, stream, val);
    }
    else {
        /* Major type 1: an negative integer */
        return encode_int(CBOR_NEGINT, stream, -1 - val);
    }
}


size_t cbor_serialize_unicode_string(Stream* stream, const char *val)
{
    return encode_bytes(CBOR_TEXT, stream, val, strlen(val));
}

size_t cbor_serialize_double(Stream* stream, double val)
{
    stream->write((unsigned char) CBOR_FLOAT64);
    uint64_t encoded_val = htond(val);
    stream->write( (const uint8_t*)&encoded_val, 8);
    return 9;
}

size_t cbor_serialize_bool(Stream* stream, bool val)
{
    stream->write( val ? CBOR_TRUE : CBOR_FALSE);
    return 1;
}

size_t cbor_serialize_byte_string(Stream* stream, const char *val, int length)
{
    return encode_bytes(CBOR_BYTES, stream, val, length);
}