#include <exception>
#include <map>

#include "Image.hpp"

namespace tester
{
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
        BITMAP bmp;

        GetObject(m_bmp, sizeof(bmp), &bmp);
        return { static_cast<uint32_t>(bmp.bmWidth), static_cast<uint32_t>(bmp.bmHeight) };
    }

    void Image::facBmp(const std::string &_path)
    {
        m_bmp = (HBITMAP)LoadImageA(NULL, _path.c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
    }
}