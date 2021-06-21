#pragma once
#include <Windows.h>
#include <windowsx.h>
#include <memory>
#include "base.h"
#include"algorithms.h"


namespace SoftRender
{
    int g_width = 0;
    int g_height = 0;

    HDC g_tempDC = nullptr;
    HBITMAP g_tempBm = nullptr;
    HBITMAP g_oldBm = nullptr;
    unsigned int* g_frameBuff = nullptr;
    std::shared_ptr<float[]> g_depthBuff = nullptr;

    unsigned int bgColor = RGB(123, 195, 211);

    // ��ʼ����Ⱦ�� ��Ļ���� ��Ļ����
    void initRenderer(int w, int h, HWND hWnd);
    // ÿ֡����
    void update(HWND hWnd);
    // ������Ļ����
    void clearBuffer();
    void shutDown();

    void drawPixel(int x, int y, unsigned int color);
}

void SoftRender::initRenderer(int w, int h, HWND hWnd)
{
    g_width = w;
    g_height = h;

    // 1. ����һ����Ļ����
    // 1.1 ����һ���뵱ǰ�豸���ݵ�DC
    HDC hDC = GetDC(hWnd);
    g_tempDC = CreateCompatibleDC(hDC);
    ReleaseDC(hWnd, hDC);
    // 1.2 ������DC��bitmap����  32λɫ
    BITMAPINFO bi = { { sizeof(BITMAPINFOHEADER), w, -h, 1, 32, BI_RGB,
        (DWORD)w * h * 4, 0, 0, 0, 0 } };
    g_tempBm = CreateDIBSection(g_tempDC, &bi, DIB_RGB_COLORS, (void**)&g_frameBuff, 0, 0);
    // 1.3 ѡ���bitmap��dc��
    g_oldBm = (HBITMAP)SelectObject(g_tempDC, g_tempBm);
    // 1.4 ������Ȼ�����
    g_depthBuff.reset(new float[w * h]);

    // ������Ļ����
    clearBuffer();
}

void SoftRender::update(HWND hWnd)
{
    // 1. clear frameBuffer
    //clearBuffer();

    // present frameBuffer to screen
    int x = rand() % g_width;
    int y = rand() % g_height;
    drawPixel(x, y, RGB(255, 0, 0));
    HDC hDC = GetDC(hWnd);
    BitBlt(hDC, 0, 0, g_width, g_height, g_tempDC, 0, 0, SRCCOPY);
    ReleaseDC(hWnd, hDC);
}

void SoftRender::clearBuffer()
{
    for (int row = 0; row < g_height; ++row)
    {
        for (int col = 0; col < g_width; ++col)
        {
            int idx = row * g_width + col;
            // Ĭ�ϱ���ɫǳ�� R123 G195 B221
            g_frameBuff[idx] = bgColor;
            // ��Ȼ����� 1.0f
            g_depthBuff[idx] = 1.0f;
        }
    }
}

void SoftRender::shutDown()
{
    if (g_tempDC)
    {
        if (g_oldBm)
        {
            SelectObject(g_tempDC, g_oldBm);
            g_oldBm = nullptr;
        }
        DeleteDC(g_tempDC);
        g_tempDC = nullptr;
    }

    if (g_tempBm)
    {
        DeleteObject(g_tempBm);
        g_tempBm = nullptr;
    }
}

void SoftRender::drawPixel(int x, int y, unsigned int color)
{
    if (x < 0 || x >= g_width || y < 0 || y >= g_height) return;

    int idx = y * g_width + x;
    g_frameBuff[idx] = color;
}
