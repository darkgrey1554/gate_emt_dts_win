#include "tcp_unit.h"



/// вспомогательные функции
int read_config_file(const char* Namefile, std::list<ConfigSharedMemory>* listsharmem, std::list<ConfigUnitGate>* listunitgate)
{
    FILE* config_file = NULL;
    char simvol = 0;
    std::string str_info;
    std::string helpstr;
    int res_read = 0;
    int pos[2] = { 0,0 };
    ConfigSharedMemory UnitMem;
    ConfigUnitGate UnitGate;

    config_file = fopen(Namefile, "r");
    if (config_file == NULL) return -1;

    for (;;)
    {
        simvol = 0;
        str_info.clear();
        while (simvol != '\n' && res_read != EOF)
        {
            res_read = fscanf(config_file, "%c", &simvol);
            if ((simvol > 0x1F || simvol == '\t') && res_read != EOF) str_info += simvol;
        }

        if (str_info == "[List]" || res_read == EOF || str_info == "[GATE]" && listunitgate == NULL)
        {
            if (res_read == EOF)
            {
                std::cout << "MAIT\tERROR_FORMATION_OF_CONFIG_FILE" << std::endl;
                getch();
                return -1;
            }
            break;
        }

        if (str_info.substr(0, 4) == "@EMT")
        {
            pos[0] = 0;
            pos[1] = 0;
            UnitMem.clear();

            if (str_info.find("Input") != -1)
            {
                UnitMem.type_data = TypeData::InPut;
            }
            else if (str_info.find("Output") != -1)
            {
                UnitMem.type_data = TypeData::OutPut;
            }
            else
            {
                std::cout << "MAIT\tERROR_FORMATION_OF_CONFIG_FILE" << std::endl;
                getch();
                return -1;
            }

            if (str_info.find("Discrete") != -1)
            {
                UnitMem.type_signal = TypeSignal::Discrete;
            }
            else if (str_info.find("Analog") != -1)
            {
                UnitMem.type_signal = TypeSignal::Analog;
            }
            else
            {
                std::cout << "MAIT\tERROR_FORMATION_OF_CONFIG_FILE" << std::endl;
                getch();
                return -1;
            }

            pos[0] = str_info.find('\t', 0);
            if (pos[0] == -1)
            {
                std::cout << "MAINT\tERROR_FORMATION_OF_CONFIG_FILE" << std::endl;
                getch();
                return -1;
            }

            pos[1] = str_info.find('\t', (size_t)pos[0] + 1);
            if (pos[1] == -1)
            {
                std::cout << "MAINT\tERROR_FORMATION_OF_CONFIG_FILE" << std::endl;
                getch();
                return -1;
            }
            helpstr.clear();
            helpstr = str_info.substr((size_t)pos[0] + 1, (size_t)pos[1] - pos[0] - 1);
            UnitMem.size = atoi(helpstr.c_str());
            helpstr.clear();
            helpstr = str_info.substr((size_t)pos[1] + 1);
            UnitMem.name_memory = helpstr;
            listsharmem->push_back(UnitMem);
        }
        else if (str_info.substr(0, 5) == "@GATE")
        {
            pos[0] = 0;
            pos[1] = 0;
            UnitGate.clear();

            if (str_info.find("Input") != -1)
            {
                UnitGate.type_unit = TypeUnitGate::CLIENT;
            }
            else if (str_info.find("Output") != -1)
            {
                UnitGate.type_unit = TypeUnitGate::SERVER;
            }
            else
            {
                std::cout << "MAIT\tERROR_FORMATION_OF_CONFIG_FILE" << std::endl;
                getch();
                return -1;
            }

            if (str_info.find("Discrete") != -1)
            {
                UnitGate.type_signal = TypeSignal::Discrete;
            }
            else if (str_info.find("Analog") != -1)
            {
                UnitGate.type_signal = TypeSignal::Analog;
            }
            else
            {
                std::cout << "MAIT\tERROR_FORMATION_OF_CONFIG_FILE" << std::endl;
                getch();
                return -1;
            }

            pos[0] = str_info.find('\t', 0);
            if (pos[0] == -1)
            {
                std::cout << "MAINT\tERROR_FORMATION_OF_CONFIG_FILE" << std::endl;
                getch();
                return -1;
            }
            pos[1] = str_info.find('\t', (size_t)pos[0] + 1);
            if (pos[1] == -1)
            {
                std::cout << "MAINT\tERROR_FORMATION_OF_CONFIG_FILE" << std::endl;
                getch();
                return -1;
            }

            helpstr.clear();
            helpstr = str_info.substr((size_t)pos[0] + 1, (size_t)pos[1] - pos[0] - 1);
            UnitGate.offset = atoi(helpstr.c_str());

            pos[0] = pos[1];
            pos[1] = str_info.find('\t', (size_t)pos[0] + 1);
            if (pos[1] == -1)
            {
                std::cout << "MAINT\tERROR_FORMATION_OF_CONFIG_FILE" << std::endl;
                getch();
                return -1;
            }
            helpstr.clear();
            helpstr = str_info.substr((size_t)pos[0] + 1, (size_t)pos[1] - pos[0] - 1);
            UnitGate.size_data = atoi(helpstr.c_str());

            pos[0] = pos[1];
            pos[1] = str_info.find('\t', (size_t)pos[0] + 1);
            if (pos[1] == -1)
            {
                std::cout << "MAINT\tERROR_FORMATION_OF_CONFIG_FILE" << std::endl;
                getch();
                return -1;
            }
            helpstr.clear();
            helpstr = str_info.substr((size_t)pos[0] + 1, (size_t)pos[1] - pos[0] - 1);
            UnitGate.IP = helpstr.c_str();

            pos[0] = pos[1];
            pos[1] = str_info.find('\t', (size_t)pos[0] + 1);
            if (pos[1] == -1)
            {
                std::cout << "MAINT\tERROR_FORMATION_OF_CONFIG_FILE" << std::endl;
                getch();
                return -1;
            }
            helpstr.clear();
            helpstr = str_info.substr((size_t)pos[0] + 1, (size_t)pos[1] - pos[0] - 1);
            UnitGate.Port = atoi(helpstr.c_str());

            pos[0] = pos[1];
            helpstr.clear();
            helpstr = str_info.substr((size_t)pos[0] + 1);
            UnitGate.frequency = atoi(helpstr.c_str());
            listunitgate->push_back(UnitGate);
        }
        else if (str_info.substr(0, 5) != "[EMT]" && str_info.substr(0, 6) != "[GATE]")
        {
            std::cout << "MAIN\tERROR_FORMATION_OF_CONFIG_FILE" << std::endl;
            getch();
            return -1;
        }
    }
    return 0;
}

std::ostream& operator<<(std::ostream& out, TypeSignal& m) 
{
    if (m == TypeSignal::Analog) out << "Analog";
    if (m == TypeSignal::Discrete) out << "Discrete";
    if (m == TypeSignal::Nothing) out << "Nothing";
    return out;
}

/// TCP_UNIT
tcp_unit* tcp_unit::create_tcp_unit(ConfigUnitGate gate, int id)
{
    if (gate.type_unit==TypeUnitGate::SERVER) return new tcp_server(gate, id);
    if (gate.type_unit == TypeUnitGate::CLIENT)return new tcp_client(gate,id);;
}


/// TCP _SERVER
tcp_server::tcp_server(ConfigUnitGate confgate, int id)
{
     set = confgate;
     ID = id;
     if (set.type_signal == TypeSignal::Analog || set.type_signal == TypeSignal::Discrete)
     {
         s_data=4;
     }

     thread_unit = std::thread(&tcp_server::thread_tcp_server, this);
}

int tcp_server::thread_tcp_server()
{
    WSADATA wsaData;
    int result=0;
    SOCKET listensocket = INVALID_SOCKET;
    SOCKET client = INVALID_SOCKET;
    sockaddr_in addr_server;
    sockaddr_in addr_client;
    int lenght_addr_client=sizeof(addr_client);
    char* buf_recv = new char[10];
    int count_recv = 0;
    int num_recv = 1;
    char* buf_send = new char[set.size_data * s_data +4+1];
    char* ibuf_send;
    char* imass_data;

    LARGE_INTEGER timenow;
    LARGE_INTEGER timelast;
    LARGE_INTEGER fhz;
    QueryPerformanceFrequency(&fhz);
    float time;

    result = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (result != 0)
    {
        std::cout << "SERVER ID: "<<ID<<"/tERROR INIT WSADATA CODE ERROR: " << WSAGetLastError() << std::endl;
        return -1;
    }
 
    listensocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (listensocket == INVALID_SOCKET)
    {
        std::cout << "SERVER ID: " << ID << "/tERROR INITIALIZATION CODE ERROR: " << WSAGetLastError() << std::endl;
        return -1;
    }

    addr_server.sin_family = AF_INET;
    addr_server.sin_addr.s_addr = inet_addr(set.IP.c_str());
    addr_server.sin_port = htons(set.Port);
    
    result = bind(listensocket, (sockaddr*)&addr_server, sizeof(addr_server));
    if (result == SOCKET_ERROR)
    {
        std::cout << "SERVER ID: " << ID << "\tERROR INITIALIZATION CODE ERROR: " << WSAGetLastError() << std::endl;
        return -1;
      
    }

    if (listen(listensocket, 1) == SOCKET_ERROR)
    {
        std::cout << "SERVER ID: " << ID << "\tERROR INITIALIZATION CODE ERROR: " << WSAGetLastError() << std::endl;
        closesocket(listensocket);
        return -1;
    }

    std::cout << "SERVER INITIALIZED ID: " << ID
        << " IP: " << set.IP
        << " PORT: " << set.Port
        << " TYPE_SIGNAL: " << set.type_signal << std::endl;

    for (;;)
    {
        client = accept(listensocket, (sockaddr*)&addr_client, &lenght_addr_client);
        if (client == INVALID_SOCKET)
        {
            std::cout << "SERVER ID: " << ID << "\tERROR CONNECTION CLIENT CODE ERROR: " << WSAGetLastError() << std::endl;
            continue;
        }

        std::cout << "SERVER ID: " << ID << "\tCONNECTION WITH CLIENT IP: "
            << (int)addr_client.sin_addr.S_un.S_un_b.s_b1 << "."
            << (int)addr_client.sin_addr.S_un.S_un_b.s_b2 << "."
            << (int)addr_client.sin_addr.S_un.S_un_b.s_b3 << "."
            << (int)addr_client.sin_addr.S_un.S_un_b.s_b4
            << "  PORT: " << addr_client.sin_port << std::endl;        
        
        QueryPerformanceCounter(&timenow);
        QueryPerformanceCounter(&timelast);
        for (;;)
        {
            count_recv = 0;
            for (;;)
            {
                count_recv += recv(client, buf_recv + count_recv, 1, NULL);
                if (count_recv == num_recv) break;
                if (count_recv == 0) break;
            }
            if (count_recv == 0)
            {
                std::cout << "SERVER ID: " << ID << "/tERROR RECV CODE ERROR: " << WSAGetLastError() << std::endl;
                break;
            }

            QueryPerformanceCounter(&timenow);
            time = (timenow.QuadPart - timelast.QuadPart) * 1000. / fhz.QuadPart;
            if (time > set.frequency) std::cout << "SERVER ID: " << ID << "\tWARNING: LIMIT_TIME_MESSENG_READING_EXCEEDED " << time << std::endl;
            QueryPerformanceCounter(&timelast);

            if (buf_recv[0] == 3)
            {
                ibuf_send = buf_send;
                *ibuf_send = 3;
                for (int i = 0; i < 4; i++)
                {
                    ibuf_send++;
                    *ibuf_send = *(((char*)&set.size_data) + i);
                }

                ibuf_send++;
                imass_data = set.buf_data;               
                for (int i = 0; i < set.size_data * s_data; i++)
                {
                    *ibuf_send = *imass_data;
                    ibuf_send++;
                    imass_data++;
                }

                send(client, buf_send, set.size_data * s_data + 5, NULL);

            }
        }
    }
    
    return 0;
}

void tcp_server::restart_thread()
{
    std::cout << "restart_thread" << std::endl;
}

void tcp_server::close_tcp_unit()
{
    std::cout << "close_tcp_unit" << std::endl;
}


/// TCP_CLIENT
tcp_client::tcp_client(ConfigUnitGate confgate, int id)
{
    ID = id;
    set = confgate;

    if (set.type_signal == TypeSignal::Analog || set.type_signal == TypeSignal::Discrete)
    {
        s_data=4;
    }
    thread_unit = std::thread(&tcp_client::thread_tcp_client, this);
}

int tcp_client::thread_tcp_client()
{
    WSADATA wsaData;
    int result = 0;
    SOCKET server = INVALID_SOCKET;
    sockaddr_in addr_server;
    int size_addr = sizeof(addr_server);

    char* buf_recv = new char[set.size_data* s_data +5];
    int count_recv = 0;
    int res_recv = 0;
    int num_recv = 0;
    char* ibuf_recv;
    char* imass_data;
    char* buf_send = new char[1];

    LARGE_INTEGER timenow;
    LARGE_INTEGER timelast;
    LARGE_INTEGER fhz;
    QueryPerformanceFrequency(&fhz);
    float time;

    result = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (result != 0)
    {
        std::cout << "CLIENT ID: " << ID << "/tERROR INIT WSADATA CODE ERROR: " << WSAGetLastError() << std::endl;
        return -1;
    }

    server = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (server == INVALID_SOCKET)
    {
        std::cout << "CLIENT ID: " << ID << "/tERROR INITIALIZATION CODE ERROR: " << WSAGetLastError() << std::endl;
        return -1;
    }

    addr_server.sin_family = AF_INET;
    addr_server.sin_addr.s_addr = inet_addr(set.IP.c_str());
    addr_server.sin_port = htons(set.Port);

        
          
    for (;;)
    {
        server = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
        if (server == INVALID_SOCKET)
        {
            std::cout << "CLIENT ID: " << ID << "/tERROR INITIALIZATION CODE ERROR: " << WSAGetLastError() << std::endl;
            return -1;
        }

        if (connect(server, (sockaddr*)&addr_server, sizeof(addr_server)) == SOCKET_ERROR)
        {
            std::cout << "CLIENT ID: " << ID << "/tERROR CONNECTION WITH SERVER CODE ERROR: " << WSAGetLastError() << std::endl;
            closesocket(server);
            Sleep(2000);
            continue;
        }
        else
        {
            std::cout << "CLIENT ID: " << ID << " CONNECTED WITH SERVER IP: " << set.IP << " PORT: " << set.Port << std::endl;
        }

        QueryPerformanceCounter(&timenow);
        QueryPerformanceCounter(&timelast);

        for (;;)
        {           
            QueryPerformanceCounter(&timenow);
            time = (timenow.QuadPart - timelast.QuadPart) * 1000. / fhz.QuadPart;
            if (time > set.frequency) std::cout << "CLIENT ID: " << ID << "\tWARNING: LIMIT_TIME_MESSENG_READING_EXCEEDED " << time << " ms"<<std::endl;
                
            for (;;)
            {
                QueryPerformanceCounter(&timenow);
                time= (timenow.QuadPart - timelast.QuadPart) * 1000. / fhz.QuadPart;
                if (time > set.frequency-TIME_DIV) break;
                Sleep(1);
            }

            QueryPerformanceCounter(&timelast);
            buf_send[0] = 3;
            send(server, buf_send, 1, NULL);
            count_recv = 0;
            res_recv = 0;
            for (;;)
            {
                res_recv=recv(server, buf_recv + count_recv, set.size_data * s_data + 5 - count_recv, NULL);
                if (res_recv == 0) break;
                count_recv += res_recv;
                if (count_recv < 5) continue;             
                num_recv = *((int*)(buf_recv + 1));
                if (count_recv < num_recv * s_data + 5) { continue; }
                else break;
            }
            if (res_recv == 0)
            {
                closesocket(server);
                break;
            }
            ibuf_recv = buf_recv + 5;
            imass_data = set.buf_data;

            for (int i = 0; i < num_recv * s_data; i++)
            {
                *imass_data = *ibuf_recv;
                imass_data++;
                ibuf_recv++;
            }
        }
    }

    return 0;
}

void tcp_client::restart_thread()
{
    std::cout << "restart_thread" << std::endl;
}

void tcp_client::close_tcp_unit()
{
    std::cout << "close_tcp_unit" << std::endl;
}



/// UNIT_SHARED_MEMORY

UnitSharedMemory::UnitSharedMemory(ConfigSharedMemory in_parametrs)
{
    parametrs = in_parametrs;
    /// --- надо сделать проверки по параметрам --- ///
    //---------
    ///////////////////////////////////////////////////
    std::string mutexname = "mutex";
    mutexname += parametrs.name_memory.c_str();
    if (parametrs.type_signal == TypeSignal::Analog || parametrs.type_signal == TypeSignal::Discrete)
    {
        parametrs.size *= 4;
    }
    mutex = CreateMutexA(NULL, FALSE, mutexname.c_str());
    memory = CreateFileMappingA(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, 0, parametrs.size, parametrs.name_memory.c_str());
    buf = (char*)MapViewOfFile(memory, FILE_MAP_ALL_ACCESS, 0, 0, parametrs.size);
};

int UnitSharedMemory::FillConfigUnitGate(ConfigUnitGate* configgate)
{
    if (configgate->type_signal == parametrs.type_signal && 
        (configgate->type_unit == TypeUnitGate::SERVER && parametrs.type_data == TypeData::OutPut ||
         configgate->type_unit == TypeUnitGate::CLIENT && parametrs.type_data == TypeData::InPut))
    {
        configgate->mutex_data = mutex;
        configgate->buf_data = buf;
        return 0;
    }
    return -1;
}