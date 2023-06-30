#ifndef __MBUS_H__
#define __MBUS_H__

#include <stddef.h>
#include <stdint.h>

#if defined (_WIN32) || defined (__CYGWIN__)
#   ifdef MBUS_BUILDING_DLL
#       ifdef __GNUC__
#           define MBUS_API __attribute__ ((dllexport))
#       else
#           define MBUS_API __declspec(dllexport) // Note: actually gcc seems to also supports this syntax.
#       endif
#   else
#       ifdef __GNUC__
#           define MBUS_API __attribute__ ((dllimport))
#       else
#           define MBUS_API __declspec(dllimport) // Note: actually gcc seems to also supports this syntax.
#       endif
#   endif
#   define MBUS_LOCAL
#else
#   if __GNUC__ >= 4
#       define MBUS_API __attribute__ ((visibility ("default")))
#       define MBUS_LOCAL  __attribute__ ((visibility ("hidden")))
#   else
#       define MBUS_API
#       define MBUS_LOCAL
#   endif
#endif

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Topic
 */
typedef struct mbus_topic mbus_topic_t;

/**
 * @brief Topic reader callback.
 * @param[in] data  Topic data.
 * @param[in] size  Topic data size.
 * @param[in] arg   User defined argument.
 */
typedef void (*mbus_topic_recv_fn)(const void* data, size_t size, void* arg);

/**
 * @brief Initialize mbus system.
 * @param[in] config    Configuration.
 * @return 0 for success, otherwise failure.
 */
MBUS_API int mbus_init(const char* config);

/**
 * @brief Exit mbus system.
 * @return 0 for success, otherwise failure.
 */
MBUS_API int mbus_exit(void);

/**
 * @brief Publish a topic.
 * @param[in] name      Topic name.
 * @param[out] topic    Topic handle.
 * @return 0 for success, otherwise failure.
 */
MBUS_API int mbus_publish(const char* name, mbus_topic_t** tpoic);

/**
 * @brief Subscribe a topic.
 * @param[in] name      Topic name.
 * @param[out] topic    Topic handle.
 * @return 0 for success, otherwise failure.
 */
MBUS_API int mbus_subscribe(const char* name, mbus_topic_t** tpoic);

/**
 * @brief Send data to topic.
 * @param[in] topic     Topic handle.
 * @param[in] data      Topic data.
 * @param[in] size      Topic data size.
 * @return 0 for success, otherwise failure.
 */
MBUS_API int mbus_topic_send(mbus_topic_t* topic, const void* data, size_t size);

/**
 * @brief Recv new data from topic.
 * @param[in] topic     Topic handle.
 * @param[in] timeout   Operation timeout.
 * @param[in] reader    Reader function.
 * @param[in] arg       User defined argument passed to \p reader.
 * @return 0 for success, otherwise failure.
 */
MBUS_API int mbus_topic_recv(mbus_topic_t* topic, uint32_t timeout,
    mbus_topic_recv_fn reader, void* arg);

/**
 * @brief Peek last data from topic.
 * @param[in] topic     Topic handle.
 * @param[in] reader    Reader function.
 * @param[in] arg       User defined argument passed to \p reader.
 * @return 0 for success, otherwise failure.
 */
MBUS_API int mbus_topic_peek(mbus_topic_t* topic,
    mbus_topic_recv_fn reader, void* arg);

#ifdef __cplusplus
}
#endif
#endif
