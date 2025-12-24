#pragma once
#ifndef SHADER_SHADERHANDLER_H_
#define SHADER_SHADERHANDLER_H_

#include <list>
#include <memory>
#include <string>
#include <deque>
#include <optional>
#include <tuple>

#include "enginecore/core/assets/shader/GLShader.h"

template<typename TYPE>
class ShaderUniformHandler
{
public:
	ShaderUniformHandler() = default;
	~ShaderUniformHandler() = default;

public:
	void enqueueUniform(const std::string& name, const TYPE& first, const std::optional<TYPE>& second = std::nullopt,
		const std::optional<TYPE>& third = std::nullopt, const std::optional<TYPE>& fourth = std::nullopt)
	{
		m_uniforms.push_back(std::make_pair(name, std::make_tuple(first, second, third, fourth)));
	}

	void update()
	{
		for (auto& shader : m_shaders)
		{
			std::shared_ptr<GLShader> shader_ptr = shader.lock();
			// should use calls when need?
			shader_ptr->use();

			// should uniform calls once?
			for (auto& uniform_pair : m_uniforms)
			{
				shader_ptr->uniform(uniform_pair.first, std::get<0>(uniform_pair.second));

				if (std::get<1>(uniform_pair.second).has_value())
				{
					shader_ptr->uniform(uniform_pair.first, std::get<1>(uniform_pair.second).value());
				}
				if (std::get<2>(uniform_pair.second).has_value())
				{
					shader_ptr->uniform(uniform_pair.first, std::get<2>(uniform_pair.second).value());
				}
				if (std::get<3>(uniform_pair.second).has_value())
				{
					shader_ptr->uniform(uniform_pair.first, std::get<3>(uniform_pair.second).value());
				}

			}
		}
	}

private:
	std::list<std::weak_ptr<GLShader>> m_shaders;
	std::deque<std::pair<std::string,
		std::tuple<TYPE, std::optional<TYPE>, std::optional<TYPE>, std::optional<TYPE>>>> m_uniforms;
};

using HandlerFloat = ShaderUniformHandler<float>;
using HandlerInt = ShaderUniformHandler<int>;
using HandlerMat4 = ShaderUniformHandler<glm::mat4>;
using HandlerVec3 = ShaderUniformHandler<glm::vec3>;
using HandlerVec2 = ShaderUniformHandler<glm::vec2>;
using HandlerIVec2 = ShaderUniformHandler<glm::ivec2>;

class ShaderHandler
{
public:
	ShaderHandler() = default;
	~ShaderHandler() = default;

public:
	void update()
	{
		m_float_handler.update();
		m_int_handler.update();
		m_mat4_handler.update();
		m_vec3_handler.update();
		m_vec2_handler.update();
		m_ivec2_handler.update();
	}

public:
	HandlerFloat m_float_handler;
	HandlerInt m_int_handler;
	HandlerMat4 m_mat4_handler;
	HandlerVec3 m_vec3_handler;
	HandlerVec2 m_vec2_handler;
	HandlerIVec2 m_ivec2_handler;
};



#endif // !SHADER_SHADERHANDLER_H_