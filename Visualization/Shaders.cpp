#include "Precompiled.h"
#include "Shaders.h"
#include "Vertices.h"

using namespace Visualization;

//Geometry Shader

GeometryShader::GeometryShader(System& p_System)
	: m_System(p_System)
	, m_ShaderPointer(nullptr)
{}

GeometryShader::~GeometryShader()
{
	Assert(nullptr == m_ShaderPointer, "Not released!");
}

void GeometryShader::Compile(LPCWSTR p_FileName, LPCSTR p_EntryName, LPCSTR p_ShaderLevel)
{
	ID3DBlob* shaderBlob = nullptr;

	DWORD shaderFlags = D3DCOMPILE_ENABLE_STRICTNESS | D3DCOMPILE_DEBUG;
	ID3DBlob* errorBlob = nullptr;
	HRESULT hr = D3DCompileFromFile
		(p_FileName
		, nullptr
		, nullptr
		, p_EntryName
		, p_ShaderLevel
		, shaderFlags
		, 0
		, &shaderBlob
		, &errorBlob);

	Assert(SUCCEEDED(hr), "Could not compile geometry shader! %s", (char*)errorBlob->GetBufferPointer());
	ProperlyRelease(errorBlob);

	m_System.GetDevice()->CreateGeometryShader
		(shaderBlob->GetBufferPointer()
		, shaderBlob->GetBufferSize()
		, nullptr
		, &m_ShaderPointer);

	ProperlyRelease(shaderBlob);
}

void GeometryShader::Release()
{
	ProperlyRelease(m_ShaderPointer);
}

void GeometryShader::Bind() const
{
	m_System.GetContext()->GSSetShader(m_ShaderPointer, nullptr, 0);
}

void GeometryShader::Unbind() const
{
	m_System.GetContext()->GSSetShader(nullptr, nullptr, 0);
}

//Pixel Shader

PixelShader::PixelShader(System& p_System)
: m_System(p_System)
, m_ShaderPointer(nullptr)
{}

PixelShader::~PixelShader()
{
	Assert(nullptr == m_ShaderPointer, "Not released!");
}

void PixelShader::Compile(LPCWSTR p_FileName, LPCSTR p_EntryName, LPCSTR p_ShaderLevel)
{
	ID3DBlob* shaderBlob = nullptr;

	DWORD shaderFlags = D3DCOMPILE_ENABLE_STRICTNESS | D3DCOMPILE_DEBUG;
	ID3DBlob* errorBlob = nullptr;
	HRESULT hr = D3DCompileFromFile
	( p_FileName
	, nullptr
	, nullptr
	, p_EntryName
	, p_ShaderLevel
	, shaderFlags
	, 0
	, &shaderBlob
	, &errorBlob);

	Assert(SUCCEEDED(hr), "Could not compile pixel shader! %s", (char*)errorBlob->GetBufferPointer());
	ProperlyRelease(errorBlob);

	m_System.GetDevice()->CreatePixelShader
	( shaderBlob->GetBufferPointer()
	, shaderBlob->GetBufferSize()
	, nullptr
	, &m_ShaderPointer);

	ProperlyRelease(shaderBlob);
}

void PixelShader::Release()
{
	ProperlyRelease(m_ShaderPointer);
}

void PixelShader::Bind() const
{
	m_System.GetContext()->PSSetShader(m_ShaderPointer, nullptr, 0);
}