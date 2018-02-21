#ifndef SENMLCBOR
#define SENMLCBOR

#include <stream.h>

#define SENML_BVER_LABEL    -1
#define SENML_CBOR_BN_LABEL -2
#define SENML_CBOR_BT_LABEL -3
#define SENML_CBOR_BU_LABEL -4
#define SENML_CBOR_BV_LABEL -5
#define SENML_CBOR_BS_LABEL -16
#define SENML_CBOR_N_LABEL   0
#define SENML_CBOR_U_LABEL   1
#define SENML_CBOR_V_LABEL   2
#define SENML_CBOR_VS_LABEL  3
#define SENML_CBOR_VB_LABEL  4
#define SENML_CBOR_S_LABEL   5
#define SENML_CBOR_T_LABEL   6
#define SENML_CBOR_UT_LABEL  7
#define SENML_CBOR_VD_LABEL  8

/**
 * @brief Serialize array of length @p array_length
 *
 * Basic usage:
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ {.c}
 * cbor_serialize_array(&stream, 2); // array of length 2 follows
 * cbor_serialize_int(&stream, 1)); // write item 1
 * cbor_serialize_int(&stream, 2)); // write item 2
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *
 * @note You have to make sure to serialize the correct amount of items.
 * If you exceed the length @p array_length, items will just be appened as normal
 *
 * @param[out] stream       The destination stream for serializing the array
 * @param[in]  array_length Length of the array of items which follows
 *
 * @return Number of bytes written to stream @p stream
 */
size_t cbor_serialize_array(Stream* stream, size_t array_length);


/**
 * @brief Serialize map of length @p map_length
 *
 * Basic usage:
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ {.c}
 * cbor_serialize_map(&stream, 2); // map of length 2 follows
 * cbor_serialize_int(&stream, 1)); // write key 1
 * cbor_serialize_byte_string(&stream, "1")); // write value 1
 * cbor_serialize_int(&stream, 2)); // write key 2
 * cbor_serialize_byte_string(&stream, "2")); // write value 2
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *
 * @param[out] stream  The destination stream for serializing the map
 * @param map_length Length of the map of items which follows
 *
 * @return Number of bytes written to stream @p stream
 */
size_t cbor_serialize_map(Stream* stream, size_t map_length);


/**
 * @brief Serializes an integer
 *
 * @param[out] stream   The destination stream for serializing the array
 * @param[in] val       The integer to serialize
 *
 * @return Number of bytes written to stream @p stream
 */
size_t cbor_serialize_int(Stream* stream, int val);


/**
 * @brief Serializes a unicode string.
 *
 * @param[out] stream   The destination stream for serializing the unicode
 *                      string
 * @param[out] val      The zero-terminated unicode string to serialize.
 *
 * @return Number of bytes written to stream @p stream
 */
size_t cbor_serialize_unicode_string(Stream* stream, const char *val);


/**
 * @brief Serializes a double precision floating point value
 *
 * @param[out] stream   The destination stream for serializing the array
 * @param[in] val       The double to serialize
 *
 * @return Number of bytes written to stream @p stream
 */
size_t cbor_serialize_double(Stream* stream, double val);


/**
 * @brief Serializes a boolean value
 *
 * @param[out] stream   The destination stream for serializing the array
 * @param[in] val       The boolean value to serialize
 *
 * @return Number of bytes written to stream @p stream
 */
size_t cbor_serialize_bool(Stream* stream, bool val);

/**
 * @brief Serializes a signed 64 bit value
 *
 * @param[out] stream   The destination stream for serializing the array
 * @param[in] val       The 64 bit integer to serialize
 *
 * @return Number of bytes written to stream @p stream
 */
size_t cbor_serialize_byte_string(Stream* stream, const char *val, int length);

#endif // SENMLCBOR