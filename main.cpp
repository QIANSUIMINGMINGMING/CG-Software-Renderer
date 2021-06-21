#include <windows.h>
#include"renderWindow.h"


LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPSTR lpCmdLine, _In_ int nShowCmd)
{
    // 1 create win32 application
    // "https://docs.microsoft.com/zh-cn/previous-versions/visualstudio/visual-studio-2008/bb384843(v%3dvs.90)"
    // 1.1 register class
    WNDCLASSEX wcex = { 0 };
    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_APPLICATION));
    wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszClassName = L"simpleSoftRender";
    wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE((WORD)IDI_APPLICATION));
    if (!RegisterClassEx(&wcex))
    {
        MessageBox(NULL,
            L"Call to RegisterClassEx failed!",
            L"Win32 Guided Tour",
            NULL);

        return 1;
    }

    // 1.2 create window
    HWND hWnd = CreateWindow(
        L"simpleSoftRender",
        L"simpleSoftRender",
        WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU,
        CW_USEDEFAULT, CW_USEDEFAULT,
        800, 600,
        NULL,
        NULL,
        hInstance,
        NULL
    );
    if (!hWnd)
    {
        MessageBox(NULL,
            L"Call to CreateWindow failed!",
            L"Win32 Guided Tour",
            NULL);

        return 1;
    }

    // 1.3 show window
    ShowWindow(hWnd, nShowCmd);
    UpdateWindow(hWnd);

    // 1.4 start message loop
        // renderer init
    SoftRender::initRenderer(800, 600, hWnd);

    // 1.4 start message loop
    MSG msg = {};
    while (msg.message != WM_QUIT)
    {
        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        else
        {
            SoftRender::update(hWnd);
        }
    }

    SoftRender::shutDown();

    return (int)msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
        break;
    }

    return 0;
}

/*#include"tgaimage.h"
#include"model.h"
#include"geometry.h"
#include<iostream>

const TGAColor white = TGAColor(255, 255, 255, 255);
const TGAColor red = TGAColor(255, 0, 0, 255);

int main()
{
    /* Êä³öÍ¼Æ¬
    TGAImage image(100, 100, TGAImage::RGB);
    image.set(0, 99, red);
    //image.flip_vertically(); // i want to have the origin at the left bottom corner of the image
    image.write_tga_file("output.tga");
    return 0;
    */
    /*
        auto model = new Model("obj/african_head.obj");
        for (int i = 0; i < model->nfaces(); i++)
        {
            std::vector<int> face = model->face(i);
            for(int value : face)
            {
                std::cout << value;
                Vec3f vert = model->vert(value);
                std::cout << vert;
            }
        }
        delete model;
        return 0;
    }
    */
