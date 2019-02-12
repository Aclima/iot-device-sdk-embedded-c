/* Copyright 2018 Google LLC
 *
 * This is part of the Google Cloud IoT Edge Embedded C Client,
 * it is licensed under the BSD 3-Clause license; you may not use this file
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

#include "bsp/iotc_bsp_io_net.h"
#include "gmock.h"
#include "gtest.h"

#include "iotc.h"
#include "iotc_bsp_crypto.h"
#include "iotc_heapcheck_test.h"
#include "iotc_helpers.h"
#include "iotc_jwt.h"
#include "iotc_macros.h"
#include "iotc_types.h"

#include <iostream>

#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

namespace iotctest {
namespace {
using namespace std;
class NetTest : public IotcHeapCheckTest {
public:
  NetTest() {
    open_server();
    iotc_initialize();
  }
  ~NetTest() { iotc_shutdown(); }
  void open_server();
  iotc_bsp_socket_t test_socket;
  const char* host_ipv6 = "localhost";
  // const char *host_ipv4 = "127.0.0.1";
  const char* msg = "hello\n";
  uint16_t port = 2000;
  char port_str[10];
  int out_written_count;
};
NetTest::open_server() {
  // TODO: define PORT
  int sock;
  struct sockaddr_in addr, client addr;
  char recv_buffer[1024];
  int recv_len;
  int addr_len;

  // Create socket.
  if ((sock = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
    perror("Error creating server socket.");
    return;
  }

  // Initialize and set server address.
  memset(&addr, 0x00, sizeof(addr));
  addr.sin_family = AF_INET;
  addr.sin_addr.s_addr = htonl(INADDR_ANY);
  addr.sin_port = htons(PORT);

  if (bind(sock, (struct sockaddr*)&addr, sizeof(addr)) < 0) {
    perror("Error binding");
    return;
  }

  addr_len = sizeof(client_addr);
  if (recv_len = recvfrom(soc, recv_buffer, 1024, 0,
                          (struct sockaddr*)&client_addr, &addr_len) < 0) {
    perror("Error recvfrom");
    return;
  }

  recv_buffer[recv_len] = '\0';

  printf("ip : %s\n", inet_ntoa(client_addr.sin_addr));
  printf("received data ; %s\n", recv_buffer);

  sendto(sock, recv_buffer, strlen(recv_buffer), 0,
         (struct sockaddr*)&client_addr, sizeof(client_addr));

  close(sock);

  return;
}

TEST_F(NetTest, SocketCreation) {
  EXPECT_EQ(iotc_bsp_io_net_socket_connect(&test_socket, host_ipv6, port),
            IOTC_BSP_IO_NET_STATE_OK);
}
TEST_F(NetTest, SocketConnectionCheck) {
  EXPECT_EQ(iotc_bsp_io_net_connection_check(test_socket, host_ipv6, port),
            IOTC_BSP_IO_NET_STATE_OK);
}
TEST_F(NetTest, EndToEndCommunicationWorks) {
  EXPECT_EQ(iotc_bsp_io_net_write(test_socket, &out_written_count,
                                  (uint8_t*)msg, strlen(msg)),
            IOTC_BSP_IO_NET_STATE_OK);
  EXPECT_EQ(out_written_count, (int)strlen(msg));
}
TEST_F(NetTest, SocketClosing) {
  EXPECT_EQ(iotc_bsp_io_net_close_socket(&test_socket),
            IOTC_BSP_IO_NET_STATE_OK);
}

} // namespace
} // namespace iotctest