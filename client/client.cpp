#include <ws2tcpip.h>
#include <windows.h>
#include <thread>
#include <iostream>
#include <string>

#pragma comment(lib, "ws2_32.lib")

std::string name = "";
bool exited = false;

void recv_thread(SOCKET socket);
void send_thread(SOCKET socket);

void erase_text(int count);

int main() {

	WSADATA winsock_data;
	WSAStartup(MAKEWORD(2, 0), &winsock_data);

	SOCKET client_socket = socket(AF_INET, SOCK_STREAM, 0);
	sockaddr_in client;
	client.sin_family = AF_INET;
	client.sin_port = htons(1432);
	InetPtonW(AF_INET, L"127.0.0.1", &client.sin_addr.s_addr);

	connect(client_socket, (sockaddr*)&client, sizeof(client));

	std::cout << "Name: " << std::endl;
	std::cin >> name;

	char buffer[1024];
	strcpy_s(buffer, name.c_str());

	send(client_socket, buffer, sizeof(buffer), 0);

	std::thread __recv(recv_thread, client_socket);
	std::thread __send(send_thread, client_socket);

	move(__recv);
	move(__send);

	__recv.join();
	__send.join();

	return 0;

}

void recv_thread(SOCKET socket) {

	while (1) {

		char buffer[1024];

		Sleep(1);

		int bytes = recv(socket, buffer, sizeof(buffer), 0);
		if (!bytes)
			continue;
		
		erase_text(17);

		std::string str_buffer = buffer;

		std::cout << str_buffer << std::endl;

		std::cout << "You : ";

		fflush(stdout);

	}

}

void send_thread(SOCKET socket) {

	std::string temp;
	std::getline(std::cin, temp);

	while (1) {

		std::string str_buffer = "";
		char buffer[1024] = "";

		Sleep(1);

		std::cout << "You : ";
		std::getline(std::cin, str_buffer);

		strcpy_s(buffer, str_buffer.c_str());

		send(socket, buffer, sizeof(buffer), 0);

		if (!strcmp(buffer, "#exit")) {
			exit(0);
		}

	}

}

void erase_text(int count) {
	char del = 0x8;
	for (int i = 0; i < count; i++)
	{
		std::cout << del;
	}
}