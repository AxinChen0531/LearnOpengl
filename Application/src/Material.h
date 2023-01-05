#pragma once

#include "Shader.h"
#include "Log.h"
#include <memory>

#include <GL/glew.h>

class Material
{
private:
	unsigned int m_id;

public:
	Material(const Shader& shader);
	~Material();

	unsigned int GetProgramID() const;
	void Use() const;
};