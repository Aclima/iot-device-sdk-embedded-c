# Copyright 2018-2020 Google LLC
#
# This is part of the Google Cloud IoT Device SDK for Embedded C.
# It is licensed under the BSD 3-Clause license; you may not use this file
# except in compliance with the License.
#
# You may obtain a copy of the License at:
#  https://opensource.org/licenses/BSD-3-Clause
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

include make/mt-os/mt-os-common.mk

#NOTE: we're depending on an external project to set CC, AR, and IOTC_C_FLAGS.
#if we want to build from within this project, we would have to set the
#appropriate ARM flags here, and perhaps set up a toolchain like is done in
#mt-arm-linux.mk

IOTC_COMMON_COMPILER_FLAGS += -Wno-ignored-qualifiers
IOTC_ARFLAGS += -rs -c $(XI)
