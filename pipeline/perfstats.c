////////////////////////////////////////////////////////////////////////
//
// Copyright 2014 PMC-Sierra, Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License"); you
// may not use this file except in compliance with the License. You may
// obtain a copy of the License at
// http://www.apache.org/licenses/LICENSE-2.0 Unless required by
// applicable law or agreed to in writing, software distributed under the
// License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
// CONDITIONS OF ANY KIND, either express or implied. See the License for
// the specific language governing permissions and limitations under the
// License.
//
////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////
//
//   Author: Logan Gunthorpe
//
//   Date:   Oct 23 2014
//
//   Description:
//     Capture Perf Stats
//
////////////////////////////////////////////////////////////////////////

#if defined (__cplusplus)
extern "C" {
#endif

#ifdef HAVE_LINUX_PERF_EVENT_H

#include "perfstats.h"

#include <linux/perf_event.h>
#include <linux/unistd.h>

#include <sys/types.h>
#include <unistd.h>
#include <sys/syscall.h>
#include <sys/ioctl.h>

#include <stdint.h>
#include <inttypes.h>
#include <stdio.h>

enum {
    COUNTER_PAGE_FAULTS,
    COUNTER_CPU_CYCLES,
    STALLED_CYCLES_FRONTEND,
    STALLED_CYCLES_BACKEND,
    INSTRUCTIONS,    
    DTLB_ACCESSES,
    DTLB_MISSES,
    BRANCHES,
    BRANCH_MISSES,
    CONTEXT_SWITCHES,
};

static struct perf_event_attr attrs[] = {
    { .type = PERF_TYPE_SOFTWARE, .config = PERF_COUNT_SW_PAGE_FAULTS},
    { .type = PERF_TYPE_HARDWARE, .config = PERF_COUNT_HW_CPU_CYCLES},
    { .type = PERF_TYPE_HARDWARE, .config = PERF_COUNT_HW_STALLED_CYCLES_FRONTEND},
    { .type = PERF_TYPE_HARDWARE, .config = PERF_COUNT_HW_STALLED_CYCLES_BACKEND},
    { .type = PERF_TYPE_HARDWARE, .config = PERF_COUNT_HW_INSTRUCTIONS},
    { .type = PERF_TYPE_HW_CACHE, .config = PERF_COUNT_HW_CACHE_DTLB | (PERF_COUNT_HW_CACHE_OP_READ << 8) | (PERF_COUNT_HW_CACHE_RESULT_ACCESS << 16) },
    { .type = PERF_TYPE_HW_CACHE, .config = PERF_COUNT_HW_CACHE_DTLB | (PERF_COUNT_HW_CACHE_OP_READ << 8) | (PERF_COUNT_HW_CACHE_RESULT_MISS << 16) },
    { .type = PERF_TYPE_HARDWARE, .config = PERF_COUNT_HW_BRANCH_INSTRUCTIONS},
    { .type = PERF_TYPE_HARDWARE, .config = PERF_COUNT_HW_BRANCH_MISSES},
    { .type = PERF_TYPE_SOFTWARE, .config = PERF_COUNT_SW_CONTEXT_SWITCHES},
    };

#define STAT_COUNT (sizeof(attrs) / sizeof(*attrs))

static int fds[STAT_COUNT];

static inline int
sys_perf_event_open(struct perf_event_attr *attr,
                    pid_t pid, int cpu, int group_fd,
                    unsigned long flags)
{
    attr->size = sizeof(*attr);
    return syscall(__NR_perf_event_open, attr, pid, cpu,
                   group_fd, flags);
}

void perfstats_init(void)
{
    int pid = getpid();
//    int pid = -1;
    int i;

    for (i = 0; i < STAT_COUNT; i++) {
        attrs[i].inherit = 1;
        attrs[i].disabled = 1;
        attrs[i].exclude_kernel = 0;
        attrs[i].enable_on_exec = 0;
        fds[i] = sys_perf_event_open(&attrs[i], pid, -1, -1, 0);
//        fprintf(stderr,"PC: %d %d %X\n",i, fds[i], attrs[i].config);
    }
}

void perfstats_deinit(void)
{
    int i;
    for (i = 0; i < STAT_COUNT; i++) {
        close(fds[i]);
        fds[i] = -1;
    }
}


void perfstats_enable(void)
{
    int i;
    for (i = 0; i < STAT_COUNT; i++) {
        if (fds[i] <= 0)
            continue;

        ioctl(fds[i], PERF_EVENT_IOC_ENABLE);
    }
}

void perfstats_disable(void)
{
    int i;
    for (i = 0; i < STAT_COUNT; i++) {
        if (fds[i] <= 0)
            continue;

        ioctl(fds[i], PERF_EVENT_IOC_DISABLE);
    }
}

static uint64_t readcounter(int i)
{
    uint64_t ret;
    read(fds[i], &ret, sizeof(ret));

    return ret;
}

void perfstats_print(void)
{
    if (fds[COUNTER_CPU_CYCLES] > 0)
        printf("CPU Cycles: %" PRIu64 "\n",
               readcounter(COUNTER_CPU_CYCLES));
    if (fds[INSTRUCTIONS] > 0)
        printf("Instructions: %" PRIu64 "\n",
               readcounter(INSTRUCTIONS));
/*    if (fds[COUNTER_PAGE_FAULTS] > 0)
        printf("Page Faults: %" PRIu64 "\n",
               readcounter(COUNTER_PAGE_FAULTS));*/
/*    if (fds[STALLED_CYCLES_FRONTEND] > 0)
        printf("Stalled Frontend: %" PRIu64 "\n",
               readcounter(STALLED_CYCLES_FRONTEND));
    if (fds[STALLED_CYCLES_BACKEND] > 0)
        printf("Stalled Backend: %" PRIu64 "\n",
               readcounter(STALLED_CYCLES_BACKEND));
    if (fds[DTLB_ACCESSES] > 0)
        printf("DTLB_ACCESSES: %" PRIu64 "\n",
               readcounter(DTLB_ACCESSES));
    if (fds[DTLB_MISSES] > 0)
        printf("DTLB_MISSES: %" PRIu64 "\n",
               readcounter(DTLB_MISSES));*/
    if (fds[BRANCHES] > 0)
        printf("BRANCHES: %" PRIu64 "\n",
               readcounter(BRANCHES));
    if (fds[BRANCH_MISSES] > 0)
        printf("BRANCH_MISSES: %" PRIu64 "\n",
               readcounter(BRANCH_MISSES));
/*    if (fds[CONTEXT_SWITCHES] > 0)
        printf("PERF_COUNT_SW_CONTEXT_SWITCHES: %" PRIu64 "\n",
               readcounter(CONTEXT_SWITCHES));*/
}
#endif
#if defined (__cplusplus)
}
#endif
