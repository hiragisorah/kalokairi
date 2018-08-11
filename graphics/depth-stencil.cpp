#include "depth-stencil.h"

using DSV = Microsoft::WRL::ComPtr<ID3D11DepthStencilView>;

class Seed::DepthStencil::Impl
{
public:
	Impl(const DeviceContext & device_context)
		: device_context_(device_context)
	{}

private:
	const DeviceContext & device_context_;

private:
	DSV dsv_;

public:
	ID3D11DepthStencilView * const GetDSV(void) const;

public:
	void Initialize(const unsigned int & width, const unsigned int & height);

public:
	void Clear(void) const;
};

Seed::DepthStencil::~DepthStencil(void)
{
}

std::unique_ptr<Seed::DepthStencil> Seed::DepthStencil::Create(const DeviceContext & device_context, const unsigned int & width, const unsigned int & height)
{
	std::unique_ptr<DepthStencil> depth_stencil(new DepthStencil(device_context));

	depth_stencil->impl_->Initialize(width, height);

	return depth_stencil;
}

void Seed::DepthStencil::Clear(void) const
{
	this->impl_->Clear();
}

ID3D11DepthStencilView * const Seed::DepthStencil::GetDSV(void) const
{
	return this->impl_->GetDSV();
}

Seed::DepthStencil::DepthStencil(const DeviceContext& device_context) noexcept(false)
	: impl_(std::make_unique<Impl>(device_context))
{
}

void Seed::DepthStencil::Impl::Clear(void) const
{
	this->device_context_->ClearDepthStencilView(this->dsv_.Get(), D3D11_CLEAR_DEPTH, 1.0f, 0);
}

ID3D11DepthStencilView * const Seed::DepthStencil::Impl::GetDSV(void) const
{
	return this->dsv_.Get();
}

void Seed::DepthStencil::Impl::Initialize(const unsigned int & width, const unsigned int & height)
{
	Microsoft::WRL::ComPtr<ID3D11Device> device;

	this->device_context_->GetDevice(device.GetAddressOf());

	Microsoft::WRL::ComPtr<ID3D11Texture2D> tex_2d;

	//深度マップテクスチャをレンダーターゲットにする際のデプスステンシルビュー用のテクスチャーを作成
	D3D11_TEXTURE2D_DESC tex_desc = {};
	tex_desc.Width = width;
	tex_desc.Height = height;
	tex_desc.MipLevels = 1;
	tex_desc.ArraySize = 1;
	tex_desc.Format = DXGI_FORMAT_D32_FLOAT;
	tex_desc.SampleDesc.Count = 1;
	tex_desc.SampleDesc.Quality = 0;
	tex_desc.Usage = D3D11_USAGE_DEFAULT;
	tex_desc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	tex_desc.CPUAccessFlags = 0;
	tex_desc.MiscFlags = 0;

	device->CreateTexture2D(&tex_desc, nullptr, tex_2d.GetAddressOf());
	device->CreateDepthStencilView(tex_2d.Get(), nullptr, this->dsv_.GetAddressOf());
}
