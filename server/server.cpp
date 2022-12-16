#include <winsock.h>
#include <vector>
#include <iostream>
#include <thread>

#pragma comment(lib, "ws2_32.lib")

#define ALL_USERS 999

int last_id = 0;

struct terminal {
	SOCKET socket;
	std::string name;
	int id;
};

std::vector< terminal > clients = { };

int get_next_id();
void broadcast(std::string msg, std::string name, int id, bool include_name);
void broadcast_connection(terminal client);
void handle_client(terminal client);
void erase_text(int count);

void remove_client(int id) {
	for (int i = 0; i < clients.size(); i++) {
		if (clients[i].id == id) {
			clients.erase(clients.begin() + i);
			return;
		}
	}
}

int main() {

	WSADATA winsock_data;
	WSAStartup(MAKEWORD(2, 2), &winsock_data);

	SOCKET server_socket = socket(AF_INET, SOCK_STREAM, 0);

	sockaddr_in server;
	server.sin_family = AF_INET;
	server.sin_port = htons(1432);
	server.sin_addr.s_addr = INADDR_ANY;

	bind(server_socket, (sockaddr*)&server, sizeof(server));
	listen(server_socket, 0);

	sockaddr_in client;
	int client_size = sizeof(client);

	while (1) {

		SOCKET client = accept(server_socket, (sockaddr*)&server, &client_size);

		if (client != INVALID_SOCKET) {

			char buffer[1024];

			recv(client, buffer, sizeof(buffer), 0);

			terminal new_client;
			new_client.id = last_id;
			new_client.socket = client;
			new_client.name = buffer;

			last_id++;

			clients.push_back(new_client);

			std::thread t(handle_client, new_client);
			t.detach();

		}

	}
}

int get_next_id() {
	int i = 0;
	for (terminal client : clients) {
		if (client.id != i) {
			break;
		}
		i++;
	}
	return i;
}

void broadcast(std::string msg, std::string name, int id, bool include_name) {
	std::string display_msg = msg;
	if (include_name)
		display_msg = name + " : " + msg;

	char buffer[1024] = "";
	strcpy_s(buffer, display_msg.c_str());

	for (terminal client : clients) {
		if (client.id != id) {
			send(client.socket, buffer, sizeof(buffer), 0);
		}
	}
}

void broadcast_connection(terminal client) {

	broadcast(client.name + " joined!", client.name, ALL_USERS, false);

}

void handle_client(terminal client) {
	
	broadcast_connection(client);

	while (1) {
		char buffer[1024] = "";

		int bytes = recv(client.socket, buffer, sizeof(buffer), 0);
		if (!bytes)
			break;

		if (!strcmp(buffer, "#exit")) {
			remove_client(client.id);
			broadcast(client.name + " left!", client.name, client.id, false);
			return;
		}

		broadcast(buffer, client.name, client.id, true);
	}
}

void erase_text(int count) {
	char del = 0x8;
	for (int i = 0; i < count; i++)
	{
		std::cout << del;
	}
}