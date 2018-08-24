#include "texture.h"

using namespace DirectX;

class Seed::Texture::Impl
{
public:
	Impl(const DeviceContext & device_context)
		: device_context_(device_context)
	{}

private:
	const DeviceContext & device_context_;
	unsigned int width_;
	unsigned int height_;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> srv_;

public:
	const unsigned int & width(void);
	const unsigned int & height(void);
	ID3D11ShaderResourceView * const GetSRV(void) const;

public:
	void set_topology(const D3D11_PRIMITIVE_TOPOLOGY & topology);

public:
	void Initialize(const std::string & file_name);
};

Seed::Texture::~Texture(void)
{
}

std::unique_ptr<Seed::Texture> Seed::Texture::Load(const DeviceContext & device_context, const std::string & file_name)
{
	std::unique_ptr<Texture> texture(new Texture(device_context));

	texture->impl_->Initialize(file_name);

	return texture;
}

Seed::Texture::Texture(const DeviceContext & device_context) noexcept(false)
	: impl_(std::make_unique<Impl>(device_context))
{
}

void Seed::Texture::Impl::Initialize(const std::string & file_name)
{
}

const unsigned int & Seed::Texture::Impl::width(void)
{
	//return this->width ? 
}

const unsigned int & Seed::Texture::Impl::height(void)
{

}

ID3D11ShaderResourceView * const Seed::Texture::Impl::GetSRV(void) const
{

}