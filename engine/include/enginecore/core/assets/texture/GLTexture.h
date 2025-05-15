#pragma once
#ifndef TEXTURE_GLTEXTURE_H_
#define TEXTURE_GLTEXTURE_H_

#include <stdexcept>
#include <memory>

#include <GL/glew.h>

#include "Texture.h"
#include "enginecore/utils/GLUtils.h"

class GLTexture : public Texture
{
public:
	GLTexture(const uint_t& height, const uint_t& width);
	GLTexture(const GLTexture& copy) = delete;
	~GLTexture();

protected:
	virtual void load() override;

public:
	virtual void bind() const override;
	virtual void unbind() const override;
	virtual void reload() override;
	virtual GLuint getId() const { return m_id; }

	void setNearestFilter() const;
	void setMipMapping(bool flag, bool pixelated) const;

protected:
	GLuint m_id = 0;
};


#endif // !TEXTURE_GLTEXTURE_H_