#ifndef __SECRIL_SHIM_H__
#define __SECRIL_SHIM_H__

#define LOG_TAG "secril-shim"
#define RIL_SHLIB

#include <pthread.h>
#include <termios.h>
#include <alloca.h>
#include <assert.h>
#include <getopt.h>
#include <string.h>
#include <unistd.h>
#include <dlfcn.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <inttypes.h>

#include <telephony/ril_cdma_sms.h>
#include <sys/system_properties.h>
#include <telephony/librilutils.h>
#include <cutils/sockets.h>
#include <cutils/compiler.h>
#include <telephony/ril.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/cdefs.h>
#include <utils/Log.h>
#include <sys/stat.h>
#define REAL_RIL_NAME				"/system/lib/libsec-ril.so"

extern const char * requestToString(int request);

/* TODO: Do we really need to redefine these? They aren't in a header... */
typedef struct {
    int requestNumber;
    void (*dispatchFunction) (void *p, void *pRI);
    int(*responseFunction) (void *p, void *response, size_t responselen);
} CommandInfo;

typedef struct RequestInfo {
    int32_t token;
    CommandInfo *pCI;
    struct RequestInfo *p_next;
    char cancelled;
    char local;
    RIL_SOCKET_ID socket_id;
    int wasAckSent;
} RequestInfo;

#endif /* __SECRIL_SHIM_H__ */
