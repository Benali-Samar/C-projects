#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <rabbitmq-c/amqp.h>
#include <rabbitmq-c/tcp_socket.h>

void die(const char* message) {
    fprintf(stderr, "%s\n", message);
    exit(1);
}

int main() {
    const char* hostname = "localhost";
    int port = 5672;

    const char* username = "mqtt-test";
    const char* password = "mqtt-test";
    const char* exchange = "myexchange";
    const char* routing_key = "mytopic";  // Add a semicolon here

    amqp_socket_t* socket = NULL;
    amqp_connection_state_t conn;

    conn = amqp_new_connection();

    socket = amqp_tcp_socket_new(conn);
    if (!socket) {
        die("Creating TCP socket failed");
    }

    if (amqp_socket_open(socket, hostname, port)) {
        die("Opening TCP socket failed");
    }

    amqp_channel_open(conn, 1);
    amqp_get_rpc_reply(conn);

    amqp_queue_declare_ok_t* r = amqp_queue_declare(conn, 1, amqp_empty_bytes, 0, 0, 0, 1, amqp_empty_table);
    amqp_get_rpc_reply(conn);

    amqp_bytes_t queue_name = amqp_bytes_malloc_dup(r->queue);
    if (queue_name.bytes == NULL) {
        die("Out of memory while copying queue name");
    }

    amqp_queue_bind(conn, 1, queue_name, amqp_cstring_bytes(exchange), amqp_cstring_bytes(routing_key), amqp_empty_table);  // Replace binding_key with routing_key
    amqp_get_rpc_reply(conn);

    amqp_basic_consume(conn, 1, queue_name, amqp_empty_bytes, 0, 1, 0, amqp_empty_table);
    amqp_get_rpc_reply(conn);

    while (1) {
        amqp_rpc_reply_t res;
        amqp_envelope_t envelope;

        amqp_maybe_release_buffers(conn);
        res = amqp_consume_message(conn, &envelope, NULL, 0);

        if (AMQP_RESPONSE_NORMAL != res.reply_type) {
            break;
        }

        printf("Received: %.*s\n", (int)envelope.message.body.len, (char*)envelope.message.body.bytes);
        amqp_destroy_envelope(&envelope);
    }

    return 0;
}
