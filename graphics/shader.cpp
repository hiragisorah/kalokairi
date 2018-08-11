#include "shader.h"
#include <iostream>

#include <d3dcompiler.h>

#pragma comment(lib, "d3dcompiler.lib")
#pragma comment(lib, "dxguid.lib")

#if defined(DEBUG) || defined(_DEBUG)
constexpr DWORD SHADER_FLAGS = D3DCOMPILE_ENABLE_STRICTNESS | D3DCOMPILE_DEBUG;
#else
constexpr DWORD SHADER_FLAGS = D3DCOMPILE_ENABLE_STRICTNESS | D3DCOMPILE_OPTIMIZATION_LEVEL3;
#endif

using VertexShader = Microsoft::WRL::ComPtr<ID3D11VertexShader>;
using GeometryShader = Microsoft::WRL::ComPtr<ID3D11GeometryShader>;
using HullShader = Microsoft::WRL::ComPtr<ID3D11HullShader>;
using DomainShader = Microsoft::WRL::ComPtr<ID3D11DomainShader>;
using PixelShader = Microsoft::WRL::ComPtr<ID3D11PixelShader>;
using ConstantBuffer = Microsoft::WRL::ComPtr<ID3D11Buffer>;
using InputLayout = Microsoft::WRL::ComPtr<ID3D11InputLayout>;

class Seed::Shader::Impl
{
public:
	Impl(const DeviceContext & device_context)
		: device_context_(device_context)
	{}

private:
	const DeviceContext & device_context_;

private:
	VertexShader vertex_shader_;
	GeometryShader geometry_shader_;
	HullShader hull_shader_;
	DomainShader domain_shader_;
	PixelShader pixel_shader_;

	ConstantBuffer constant_buffer_;
	InputLayout input_layout_;

private:
	void CreateInputLayoutAndConstantBufferFromShader(ID3DBlob * blob);
	DXGI_FORMAT GetDxgiFormat(D3D_REGISTER_COMPONENT_TYPE type, BYTE mask);

public:
	void Initialize(std::string file_name);
	void Setup(void) const;
};

Seed::Shader::~Shader(void)
{
}

std::unique_ptr<Seed::Shader> Seed::Shader::Create(const DeviceContext & device_context, const std::string & file_name)
{
	std::unique_ptr<Shader> shader(new Shader(device_context));

	shader->impl_->Initialize(file_name);

	return shader;
}

void Seed::Shader::Setup(void) const
{
	this->impl_->Setup();
}

Seed::Shader::Shader(const DeviceContext & device_context) noexcept(false)
	: impl_(std::make_unique<Impl>(device_context))
{
}

void Seed::Shader::Impl::CreateInputLayoutAndConstantBufferFromShader(ID3DBlob * blob)
{
	Microsoft::WRL::ComPtr<ID3D11Device> device;

	this->device_context_->GetDevice(device.GetAddressOf());

	ID3D11ShaderReflection * reflector = nullptr;
	D3DReflect(blob->GetBufferPointer(), blob->GetBufferSize(), IID_ID3D11ShaderReflection, (void**)&reflector);

	D3D11_SHADER_DESC shader_desc;
	reflector->GetDesc(&shader_desc);

	auto cb = reflector->GetConstantBufferByName("unique");

	int size = 0;
	D3D11_SHADER_BUFFER_DESC desc;
	cb->GetDesc(&desc);

	for (size_t j = 0; j < desc.Variables; ++j)
	{
		auto v = cb->GetVariableByIndex(j);
		D3D11_SHADER_VARIABLE_DESC vdesc;
		v->GetDesc(&vdesc);
		if (vdesc.Size % 16)
			size += vdesc.Size + 16 - (vdesc.Size % 16);
		else
			size += vdesc.Size;
	}

	D3D11_BUFFER_DESC bd;
	bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bd.ByteWidth = size;
	bd.CPUAccessFlags = 0;
	bd.MiscFlags = 0;
	bd.StructureByteStride = 0;
	bd.Usage = D3D11_USAGE_DEFAULT;

	if (FAILED(device->CreateBuffer(&bd, nullptr, this->constant_buffer_.GetAddressOf())))
		std::cout << "コンスタントバッファーの作成に失敗しました。" << std::endl;

	std::vector<D3D11_INPUT_ELEMENT_DESC> element;
	for (unsigned int i = 0; i < shader_desc.InputParameters; ++i) {
		D3D11_SIGNATURE_PARAMETER_DESC sigdesc;
		reflector->GetInputParameterDesc(i, &sigdesc);

		auto format = GetDxgiFormat(sigdesc.ComponentType, sigdesc.Mask);

		D3D11_INPUT_ELEMENT_DESC eledesc =
		{
			sigdesc.SemanticName
			, sigdesc.SemanticIndex
			, format
			, 0
			, D3D11_APPEND_ALIGNED_ELEMENT
			, D3D11_INPUT_PER_VERTEX_DATA
			, 0
		};

		element.emplace_back(eledesc);
	}

	if (!element.empty())
		if (FAILED(device->CreateInputLayout(&element[0], element.size(),
			blob->GetBufferPointer(), blob->GetBufferSize(), this->input_layout_.GetAddressOf())))
			std::cout << "インプットレイアウトの作成に失敗しました。" << std::endl;
}

DXGI_FORMAT Seed::Shader::Impl::GetDxgiFormat(D3D_REGISTER_COMPONENT_TYPE type, BYTE mask)
{
	if (mask == 0x0F)
	{
		// xyzw
		switch (type)
		{
		case D3D_REGISTER_COMPONENT_FLOAT32:
			return DXGI_FORMAT_R32G32B32A32_FLOAT;
		case D3D_REGISTER_COMPONENT_UINT32:
			return DXGI_FORMAT_R32G32B32A32_UINT;
		}
	}

	if (mask == 0x07)
	{
		// xyz
		switch (type)
		{
		case D3D_REGISTER_COMPONENT_FLOAT32:
			return DXGI_FORMAT_R32G32B32_FLOAT;
		case D3D_REGISTER_COMPONENT_UINT32:
			return DXGI_FORMAT_R32G32B32_UINT;
		}
	}

	if (mask == 0x3)
	{
		// xy
		switch (type)
		{
		case D3D_REGISTER_COMPONENT_FLOAT32:
			return DXGI_FORMAT_R32G32_FLOAT;
		case D3D_REGISTER_COMPONENT_UINT32:
			return DXGI_FORMAT_R32G32_UINT;
		}
	}

	if (mask == 0x1)
	{
		// x
		switch (type)
		{
		case D3D_REGISTER_COMPONENT_FLOAT32:
			return DXGI_FORMAT_R32_FLOAT;
		case D3D_REGISTER_COMPONENT_UINT32:
			return DXGI_FORMAT_R32_UINT;
		}
	}

	return DXGI_FORMAT_UNKNOWN;
}

void Seed::Shader::Impl::Initialize(std::string file_name)
{
	Microsoft::WRL::ComPtr<ID3D11Device> device;

	this->device_context_->GetDevice(device.GetAddressOf());

	ID3DBlob * blob = nullptr;
	ID3DBlob * error = nullptr;

	if (FAILED(D3DCompileFromFile(std::wstring(file_name.begin(), file_name.end()).c_str(), nullptr,
		D3D_COMPILE_STANDARD_FILE_INCLUDE, "VS", "vs_5_0", SHADER_FLAGS, 0, &blob, &error)))
	{
		char * err = (char*)error->GetBufferPointer();
		if (error != nullptr)
			std::cout << __FUNCTION__ << "::" << err << std::endl;
		else
			std::cout << __FUNCTION__ << "::シェーダーの読み込みに失敗しました。" << std::endl;

		return;
	}
	else
	{
		device->CreateVertexShader(blob->GetBufferPointer(), blob->GetBufferSize(), nullptr, this->vertex_shader_.GetAddressOf());
		this->CreateInputLayoutAndConstantBufferFromShader(blob);
	}

	if (SUCCEEDED(D3DCompileFromFile(std::wstring(file_name.begin(), file_name.end()).c_str(), nullptr,
		D3D_COMPILE_STANDARD_FILE_INCLUDE, "GS", "gs_5_0", SHADER_FLAGS, 0, &blob, &error)))
	{
		device->CreateGeometryShader(blob->GetBufferPointer(), blob->GetBufferSize(), nullptr, this->geometry_shader_.GetAddressOf());
	}

	if (SUCCEEDED(D3DCompileFromFile(std::wstring(file_name.begin(), file_name.end()).c_str(), nullptr,
		D3D_COMPILE_STANDARD_FILE_INCLUDE, "HS", "hs_5_0", SHADER_FLAGS, 0, &blob, &error)))
	{
		device->CreateHullShader(blob->GetBufferPointer(), blob->GetBufferSize(), nullptr, this->hull_shader_.GetAddressOf());
	}

	if (SUCCEEDED(D3DCompileFromFile(std::wstring(file_name.begin(), file_name.end()).c_str(), nullptr,
		D3D_COMPILE_STANDARD_FILE_INCLUDE, "DS", "ds_5_0", SHADER_FLAGS, 0, &blob, &error)))
	{
		device->CreateDomainShader(blob->GetBufferPointer(), blob->GetBufferSize(), nullptr, this->domain_shader_.GetAddressOf());
	}

	if (SUCCEEDED(D3DCompileFromFile(std::wstring(file_name.begin(), file_name.end()).c_str(), nullptr,
		D3D_COMPILE_STANDARD_FILE_INCLUDE, "PS", "ps_5_0", SHADER_FLAGS, 0, &blob, &error)))
	{
		device->CreatePixelShader(blob->GetBufferPointer(), blob->GetBufferSize(), nullptr, this->pixel_shader_.GetAddressOf());
	}
}

void Seed::Shader::Impl::Setup(void) const
{
	this->device_context_->VSSetShader(this->vertex_shader_.Get(), nullptr, 0);
	this->device_context_->GSSetShader(this->geometry_shader_.Get(), nullptr, 0);
	this->device_context_->HSSetShader(this->hull_shader_.Get(), nullptr, 0);
	this->device_context_->DSSetShader(this->domain_shader_.Get(), nullptr, 0);
	this->device_context_->PSSetShader(this->pixel_shader_.Get(), nullptr, 0);

	this->device_context_->VSSetConstantBuffers(0, 1, this->constant_buffer_.GetAddressOf());
	this->device_context_->GSSetConstantBuffers(0, 1, this->constant_buffer_.GetAddressOf());
	this->device_context_->HSSetConstantBuffers(0, 1, this->constant_buffer_.GetAddressOf());
	this->device_context_->DSSetConstantBuffers(0, 1, this->constant_buffer_.GetAddressOf());
	this->device_context_->PSSetConstantBuffers(0, 1, this->constant_buffer_.GetAddressOf());
}