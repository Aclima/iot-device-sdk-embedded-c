/* Copyright 2019-2020 Google LLC
 *
 * This is part of the Google Cloud IoT Device SDK for Embedded C.
 * It is licensed under the BSD 3-Clause license; you may not use this file
 * except in compliance with the License.
 *
 * You may obtain a copy of the License at:
 *  https://opensource.org/licenses/BSD-3-Clause
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <iotc_bsp_time.h>

#include <posix/time.h>
#include <posix/sys/time.h>

#include <stddef.h>
#include <time.h>
#include "iotc_sntp.h"

void iotc_bsp_time_init() { /* empty */
}

iotc_time_t iotc_bsp_time_getcurrenttime_seconds() {
    /* from nRF Connect SDK app */
    return my_k_time(NULL);
}

iotc_time_t iotc_bsp_time_getcurrenttime_milliseconds() {
    /* not implemented */
    return 0;
}
