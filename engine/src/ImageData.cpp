#include "enginecore/core/assets/texture/ImageData.h"

ImageData::ImageData(const ImageFormat& format, const uint_t& width, const uint_t& height)
	: m_format(format), m_width(width), m_height(height)
{
    size_t pixsize;
    switch (format) 
    {
        case ImageFormat::rgb888: 
            pixsize = 3; 
            break;
        case ImageFormat::rgba8888: 
            pixsize = 4; 
            break;
        default:
            throw std::runtime_error("format is not supported");
    }
    m_bytes = std::make_shared<ubyte_t[]>(width * height * pixsize);
}

ImageData::ImageData(const ImageFormat& format, const uint_t& width, const uint_t& height, const std::shared_ptr<ubyte_t[]>& data)
    : m_format(format), m_width(width), m_height(height), m_bytes(std::move(data))
{
}

std::shared_ptr<ImageData> ImageData::createFromFile(const std::filesystem::path& path_to_file)
{
    cv::Mat raw_image = cv::imread(path_to_file.string(), cv::ImreadModes::IMREAD_UNCHANGED);

    cv::Mat image;
    cv::cvtColor(raw_image, image, cv::COLOR_BGR2RGBA);

    /*if (image.type() != CV_32FC1) {
        image.convertTo(image, CV_32FC1);
    }*/

    auto size = image.u->size;

    size_t width = image.size().width;
    size_t height = image.size().height;

    std::shared_ptr<ubyte_t[]> raw_data = std::make_shared<ubyte_t[]>(size);

    for (size_t i = 0; i < size; i++)
    {
        raw_data[i] = image.data[i];
    }

    std::shared_ptr<ImageData> data = std::make_shared<ImageData>(ImageData::ImageFormat::rgba8888, width, height, raw_data);

    return data;
}

void ImageData::flipByX()
{
    switch (m_format) 
    {
    case ImageFormat::rgb888:
    case ImageFormat::rgba8888: 
    {
        uint_t size = (m_format == ImageFormat::rgba8888) ? 4 : 3;
        for (uint_t y = 0; y < m_height; y++) 
        {
            for (uint_t x = 0; x < m_width / 2; x++) 
            {
                for (uint_t c = 0; c < size; c++) 
                {
                    ubyte_t temp = m_bytes[(y * m_width + x) * size + c];
                    m_bytes[(y * m_width + x) * size + c] =
                        m_bytes[(y * m_width + (m_width - x - 1)) * size + c];
                    m_bytes[(y * m_width + (m_width - x - 1)) * size + c] = temp;
                }
            }
        }
        break;
    }
    default:
        throw std::runtime_error("format is not supported");
    }
}

void ImageData::flipByY()
{
    switch (m_format) 
    {
    case ImageFormat::rgb888:
    case ImageFormat::rgba8888: 
    {
        uint_t size = (m_format == ImageFormat::rgba8888) ? 4 : 3;
        for (uint_t y = 0; y < m_height / 2; y++) 
        {
            for (uint_t x = 0; x < m_width; x++) 
            {
                for (uint_t c = 0; c < size; c++) 
                {
                    ubyte_t temp = m_bytes[(y * m_width + x) * size + c];
                    m_bytes[(y * m_width + x) * size + c] =
                        m_bytes[((m_height - y - 1) * m_width + x) * size + c];
                    m_bytes[((m_height - y - 1) * m_width + x) * size + c] = temp;
                }
            }
        }
        break;
    }
    default:
        throw std::runtime_error("format is not supported");
    }
}

void ImageData::drawLine(const int& x1, const int& y1, const int& x2, const int& y2, const glm::ivec4& color)
{
    switch (m_format) 
    {
    case ImageFormat::rgb888:
        drawLine<3>(*this, x1, y1, x2, y2, color);
        break;
    case ImageFormat::rgba8888:
        drawLine<4>(*this, x1, y1, x2, y2, color);
        break;
    default:
        break;
    }
}

void ImageData::blit(const ImageData& image, const int& x, const int& y)
{
    if (m_format == image.m_format)
    {
        blitMatchingFormat(image, x, y);
        return;
    }
    if (m_format == ImageFormat::rgba8888 &&
        image.m_format == ImageFormat::rgb888) 
    {
        blitRGBOnRGBA(image, x, y);
        return;
    }
    throw std::runtime_error("mismatching format");
}

void ImageData::extrude(const int& x, const int& y, const int& w, const int& h)
{
    uint_t comps;
    switch (m_format) {
    case ImageFormat::rgb888: comps = 3; break;
    case ImageFormat::rgba8888: comps = 4; break;
    default:
        throw std::runtime_error("only unsigned byte formats supported");
    }
    int rx = x + w - 1;
    int ry = y + h - 1;
    // top-left pixel
    if (x > 0 && static_cast<uint_t>(x) < m_width &&
        y > 0 && static_cast<uint_t>(y) < m_height) {
        uint_t srcidx = (y * m_width + x) * comps;
        uint_t dstidx = ((y - 1) * m_width + x - 1) * comps;
        for (uint_t c = 0; c < comps; c++) {
            m_bytes[dstidx + c] = m_bytes[srcidx + c];
        }
    }

    // top-right pixel
    if (rx >= 0 && static_cast<uint_t>(rx) < m_width - 1 &&
        y > 0 && static_cast<uint_t>(y) < m_height) {
        uint_t srcidx = (y * m_width + rx) * comps;
        uint_t dstidx = ((y - 1) * m_width + rx + 1) * comps;
        for (uint_t c = 0; c < comps; c++) {
            m_bytes[dstidx + c] = m_bytes[srcidx + c];
        }
    }

    // bottom-left pixel
    if (x > 0 && static_cast<uint_t>(x) < m_width &&
        ry >= 0 && static_cast<uint_t>(ry) < m_height - 1) {
        uint_t srcidx = (ry * m_width + x) * comps;
        uint_t dstidx = ((ry + 1) * m_width + x - 1) * comps;
        for (uint_t c = 0; c < comps; c++) {
            m_bytes[dstidx + c] = m_bytes[srcidx + c];
        }
    }

    // bottom-right pixel
    if (rx >= 0 && static_cast<uint_t>(rx) < m_width - 1 &&
        ry >= 0 && static_cast<uint_t>(ry) < m_height - 1) {
        uint_t srcidx = (ry * m_width + rx) * comps;
        uint_t dstidx = ((ry + 1) * m_width + rx + 1) * comps;
        for (uint_t c = 0; c < comps; c++) {
            m_bytes[dstidx + c] = m_bytes[srcidx + c];
        }
    }

    // left border
    if (x > 0 && static_cast<uint_t>(x) < m_width) {
        for (uint_t ey = std::max(y, 0); static_cast<int>(ey) < y + h; ey++) {
            uint_t srcidx = (ey * m_width + x) * comps;
            uint_t dstidx = (ey * m_width + x - 1) * comps;
            for (uint_t c = 0; c < comps; c++) {
                m_bytes[dstidx + c] = m_bytes[srcidx + c];
            }
        }
    }

    // top border
    if (y > 0 && static_cast<uint_t>(y) < m_height) {
        for (uint_t ex = std::max(x, 0); static_cast<int>(ex) < x + w; ex++) {
            uint_t srcidx = (y * m_width + ex) * comps;
            uint_t dstidx = ((y - 1) * m_width + ex) * comps;
            for (uint_t c = 0; c < comps; c++) {
                m_bytes[dstidx + c] = m_bytes[srcidx + c];
            }
        }
    }

    // right border
    if (rx >= 0 && static_cast<uint_t>(rx) < m_width - 1) {
        for (uint_t ey = std::max(y, 0); static_cast<int>(ey) < y + h; ey++) {
            uint_t srcidx = (ey * m_width + rx) * comps;
            uint_t dstidx = (ey * m_width + rx + 1) * comps;
            for (uint_t c = 0; c < comps; c++) {
                m_bytes[dstidx + c] = m_bytes[srcidx + c];
            }
        }
    }

    // bottom border
    if (ry >= 0 && static_cast<uint_t>(ry) < m_height - 1) {
        for (uint_t ex = std::max(x, 0); static_cast<int>(ex) < x + w; ex++) {
            uint_t srcidx = (ry * m_width + ex) * comps;
            uint_t dstidx = ((ry + 1) * m_width + ex) * comps;
            for (uint_t c = 0; c < comps; c++) {
                m_bytes[dstidx + c] = m_bytes[srcidx + c];
            }
        }
    }
}

void ImageData::fixAlphaColor()
{
    int samples = 0;
    int sums[3] {};
    for (uint_t ly = 0; ly < m_height; ly++) {
        for (uint_t lx = 0; lx < m_width; lx++) {
            if (m_bytes[(ly * m_width + lx) * 4 + 3] == 0) {
                continue;
            }
            samples++;
            for (int c = 0; c < 3; c++) {
                sums[c] += m_bytes[(ly * m_width + lx) * 4 + c];
            }
        }
    }
    if (samples == 0) {
        return;
    }
    for (int i = 0; i < 3; i++) {
        sums[i] /= samples;
    }
    for (uint_t ly = 0; ly < m_height; ly++) {
        for (uint_t lx = 0; lx < m_width; lx++) {
            if (m_bytes[(ly * m_width + lx) * 4 + 3] != 0) {
                continue;
            }
            for (int i = 0; i < 3; i++) {
                m_bytes[(ly * m_width + lx) * 4 + i] = sums[i];
            }
        }
    }
}

void ImageData::blitRGBOnRGBA(const ImageData& image, const int& x, const int& y)
{
    const std::shared_ptr<const ubyte_t[]> source = image.m_bytes;
    uint_t srcwidth = image.getWidth();
    uint_t srcheight = image.getHeight();

    for (uint_t srcy = std::max(0, -y);
        srcy < std::min(srcheight, m_height - y);
        srcy++) {
        for (uint_t srcx = std::max(0, -x);
            srcx < std::min(srcwidth, m_width - x);
            srcx++) {
            uint_t dstx = srcx + x;
            uint_t dsty = srcy + y;
            uint_t dstidx = (dsty * m_width + dstx) * 4;
            uint_t srcidx = (srcy * srcwidth + srcx) * 3;
            for (uint_t c = 0; c < 3; c++) {
                m_bytes[dstidx + c] = source[srcidx + c];
            }
            m_bytes[dstidx + 3] = 255;
        }
    }
}

void ImageData::blitMatchingFormat(const ImageData& image, const int& x, const int& y) const
{
    uint_t comps;
    switch (m_format) 
    {
    case ImageFormat::rgb888: comps = 3; break;
    case ImageFormat::rgba8888: comps = 4; break;
    default:
        throw std::runtime_error("only unsigned byte formats supported");
    }
    const std::shared_ptr<const ubyte_t[]> source = image.m_bytes;

    const uint_t width = this->m_width;
    const uint_t height = this->m_height;
    const uint_t src_width = image.getWidth();
    const uint_t src_height = image.getHeight();
    std::shared_ptr<ubyte_t[]> data = this->m_bytes;

    for (uint_t srcy = std::max(0, -y);
        srcy < std::min(src_height, height - y);
        srcy++) {
        for (uint_t srcx = std::max(0, -x);
            srcx < std::min(src_width, width - x);
            srcx++) {
            uint_t dstx = srcx + x;
            uint_t dsty = srcy + y;
            uint_t dstidx = (dsty * width + dstx) * comps;
            uint_t srcidx = (srcy * src_width + srcx) * comps;
            for (uint_t c = 0; c < comps; c++) {
                data[dstidx + c] = source[srcidx + c];
            }
        }
    }
}

bool ImageData::clipLine(int& x1, int& y1, int& x2, int& y2, const int& width, const int& height)
{
    const int left = 0;
    const int right = width;
    const int bottom = 0;
    const int top = height;

    int dx = x2 - x1;
    int dy = y2 - y1;

    float t0 = 0.0f;
    float t1 = 1.0f;

    auto clip = [](int p, int q, float& t0, float& t1) {
        if (p == 0) {
            return q >= 0;
        }
        float t = static_cast<float>(q) / p;
        if (p < 0) {
            if (t > t1) return false;
            if (t > t0) t0 = t;
        }
        else {
            if (t < t0) return false;
            if (t < t1) t1 = t;
        }
        return true;
        };

    if (!clip(-dx, x1 - left, t0, t1)) return false;
    if (!clip(dx, right - x1, t0, t1)) return false;
    if (!clip(-dy, y1 - bottom, t0, t1)) return false;
    if (!clip(dy, top - y1, t0, t1)) return false;

    if (t1 < 1.0f) {
        x2 = x1 + static_cast<int>(std::round(t1 * dx));
        y2 = y1 + static_cast<int>(std::round(t1 * dy));
    }
    if (t0 > 0.0f) {
        x1 = x1 + static_cast<int>(std::round(t0 * dx));
        y1 = y1 + static_cast<int>(std::round(t0 * dy));
    }
    return true;
}
