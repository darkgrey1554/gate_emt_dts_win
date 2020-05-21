#ifndef TCP_UNIT_H
#define TCP_UNIT_H

#include <winsock2.h>
#pragma comment(lib,"ws2_32.lib")
#pragma warning(disable:4996)
#include <iostream>
#include <windows.h>
#include <thread>
#include <conio.h>
#include <list>
#pragma warning(disable:4996)

enum class TypeData
{
    Not,
    OutPut,
    InPut
};

enum class TypeSignal
{
    Nothing,
    Analog,
    Discrete
};

enum class TypeUnitGate
{
    EMPTY,
    SERVER,
    CLIENT
};

struct ConfigSharedMemory
{
    std::string name_memory;
    int size;
    TypeData type_data;
    TypeSignal type_signal;
    void clear()
    {
        name_memory.clear();
        size = 0;
        type_data = TypeData::Not;
        type_signal = TypeSignal::Nothing;
    }
};

struct ConfigUnitGate
{
    std::string IP;
    int Port;
    int frequency;
    int offset;
    int size_data;
    TypeSignal type_signal;
    TypeUnitGate type_unit;
    char* buf_data;
    HANDLE mutex_data = INVALID_HANDLE_VALUE;

    void clear()
    {
        IP.clear();
        Port = 0;
        frequency = 0;
        offset = 0;
        size_data = 0;
        type_signal = TypeSignal::Nothing;
        type_unit = TypeUnitGate::EMPTY;
        buf_data = NULL;
        mutex_data = INVALID_HANDLE_VALUE;
    }
};

int read_config_file(const char* Namefile, std::list<ConfigSharedMemory>* listsharmem, std::list<ConfigUnitGate>* listunitgate = NULL);

class tcp_unit
{
 public:
	std::string type_unit;
	std::thread thread_unit;
	std::string type_data;
	int size_data;
	int frequency;
	int ID;
	int offset;
    char* mass_data;

	void virtual restart_thread() {}
	void virtual close_tcp_unit() {}

	static tcp_unit* create_tcp_unit(std::string type_unit, int id, std::string ip, int port, std::string t_data, int s_data, char* mass_data, int bais);

};

class tcp_server : public tcp_unit
{
	std::string IP_Server;
	int PORT;

	int thread_tcp_server();

    public:

	tcp_server(int id, std::string ip, int port, std::string t_data, int s_data, char* mass_data, int bais);
	void restart_thread() override;
	void close_tcp_unit() override;
};

class tcp_client : public tcp_unit
{
	std::string IP_Server;
	int PORT;

	int thread_tcp_client();

public:

	tcp_client(int id, std::string ip, int port, std::string t_data, int s_data, char* mass_data, int bais);
	void restart_thread() override;
	void close_tcp_unit() override;
};



#endif