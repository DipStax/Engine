#include <exception>
#include <map>

#include "Image.hpp"

namespace tester
{
    Image::~Image()
    {
        if (m_bmp != NULL)
            DeleteObject(m_bmp);
    }

    void Image::load(const std::string &_path)
    {
        using facFn = void (Image::*)(const std::string&);

        static std::map<std::string, facFn> fac = {
            { "bmp", &Image::facBmp }
        };
        std::string ext = EXT(_path);

        if (fac.contains(ext))
            (this->*fac[ext])(_path);
        else
            throw std::exception("Unable to load the image");
    }

    Point2<uint32_t> Image::getSize() const
    {
        return m_size;
    }

    Color Image::getPixel(const Point2<uint32_t>& _pos) const
    {
        uint32_t pos = (_pos.y * getSize().x + _pos.x) * 4;
        return Color{ m_pxl.at(pos + 2), m_pxl.at(pos + 1), m_pxl.at(pos + 0) };
    }

    void Image::facBmp(const std::string &_path)
    {
        BITMAP bmp;
        BITMAPINFO bmpInfo;
        HDC hdc;

        m_bmp = (HBITMAP)LoadImageA(NULL, _path.c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
        GetObject(m_bmp, sizeof(BITMAP), &bmp);
        hdc = CreateCompatibleDC(NULL);
        SelectObject(hdc, m_bmp);
        ZeroMemory(&bmpInfo, sizeof(BITMAPINFO));
        bmpInfo.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
        bmpInfo.bmiHeader.biWidth = bmp.bmWidth;
        bmpInfo.bmiHeader.biHeight = bmp.bmHeight;
        bmpInfo.bmiHeader.biPlanes = 1;
        bmpInfo.bmiHeader.biBitCount = bmp.bmBitsPixel;
        bmpInfo.bmiHeader.biCompression = BI_RGB;
        m_size = { static_cast<uint32_t>(bmp.bmWidth), static_cast<uint32_t>(bmp.bmHeight) };
        m_pxl.resize(bmp.bmWidth * bmp.bmHeight * bmp.bmBitsPixel);
        GetDIBits(hdc, m_bmp, 0, bmp.bmHeight, m_pxl.data(), &bmpInfo, DIB_RGB_COLORS);
        DeleteDC(hdc);
    }
}