#pragma once

#include "Shader.h"
#include "Log.h"
#include <memory>

class Material
{
private:
	unsigned int m_id;

public:
	Material(const Shader& shader);
	~Material();

	unsigned int GetID() const;
	void Use() const;
	void Unuse() const;
};