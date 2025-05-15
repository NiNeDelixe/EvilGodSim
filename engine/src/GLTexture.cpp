#include "enginecore/core/assets/texture/GLTexture.h"

GLTexture::GLTexture(const uint_t& height, const uint_t& width)
	: Texture(height, width), m_id(0)
{
    glGenTextures(1, &m_id);
}

GLTexture::~GLTexture()
{
    glDeleteTextures(1, &m_id);
}

void GLTexture::load()
{
    glActiveTexture(GL_TEXTURE0);

    glBindTexture(GL_TEXTURE_2D, m_id);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    
    GLenum format = UTILS_NAMESPACE::gl::to_glenum(m_image_data->getFormat());
    glTexImage2D(
        GL_TEXTURE_2D, 0, GL_RGBA, getWidth(), getHeight(), 0,
        GL_RGBA, GL_UNSIGNED_BYTE, static_cast<const GLvoid*>(getBytesArray().get())
    );
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glGenerateMipmap(GL_TEXTURE_2D);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, 1);
    /*glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);*/
    glBindTexture(GL_TEXTURE_2D, 0);
}

void GLTexture::bind() const
{
    glBindTexture(GL_TEXTURE_2D, m_id);
}

void GLTexture::unbind() const
{
    glBindTexture(GL_TEXTURE_2D, 0);
}

void GLTexture::reload()
{
    glBindTexture(GL_TEXTURE_2D, m_id);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, getWidth(), getHeight(), 0,
        GL_RGBA, GL_UNSIGNED_BYTE, static_cast<const GLvoid*>(getBytesArray().get()));
    glBindTexture(GL_TEXTURE_2D, 0);
}

void GLTexture::setNearestFilter() const
{
    bind();
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glBindTexture(GL_TEXTURE_2D, 0);
}

void GLTexture::setMipMapping(bool flag, bool pixelated) const
{
    bind();
    if (flag) 
    {
        glTexParameteri(
            GL_TEXTURE_2D,
            GL_TEXTURE_MIN_FILTER,
            pixelated ? GL_NEAREST : GL_LINEAR_MIPMAP_NEAREST
        );
    }
    else 
    {
        glTexParameteri(
            GL_TEXTURE_2D,
            GL_TEXTURE_MIN_FILTER,
            pixelated ? GL_NEAREST : GL_LINEAR
        );
    }
    glBindTexture(GL_TEXTURE_2D, 0);
}