#include "render-target.h"

using RTV = Microsoft::WRL::ComPtr<ID3D11RenderTargetView>;
using SRV = Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>;

class Seed::RenderTarget::Impl
{
public:
	Impl(const SwapChain & swap_chain, const DeviceContext& device_context)
		: swap_chain_(swap_chain)
		, device_context_(device_context)
	{}

private:
	const SwapChain & swap_chain_;
	const DeviceContext& device_context_;

private:
	RTV rtv_;
	SRV srv_;

public:
	ID3D11RenderTargetView * const GetRTV(void) const;
	ID3D11ShaderResourceView * const GetSRV(void) const;

public:
	void BackBuffer(void);
	void ColorMap(const unsigned int & width, const unsigned int & height);
	void PositionMap(const unsigned int & width, const unsigned int & height);
	void NormalMap(const unsigned int & width, const unsigned int & height);
	void R32Map(const unsigned int & width, const unsigned int & height);

public:
	void Clear(void) const;
};

Seed::RenderTarget::~RenderTarget(void)
{
}

std::unique_ptr<Seed::RenderTarget> Seed::RenderTarget::BackBuffer(const SwapChain & swap_chain, const DeviceContext& device_context)
{
	std::unique_ptr<RenderTarget> render_target(new RenderTarget(swap_chain, device_context));

	render_target->impl_->BackBuffer();

	return render_target;
}

std::unique_ptr<Seed::RenderTarget> Seed::RenderTarget::ColorMap(const SwapChain & swap_chain, const DeviceContext & device_context, const unsigned int & width, const unsigned int & height)
{
	std::unique_ptr<RenderTarget> render_target(new RenderTarget(swap_chain, device_context));

	render_target->impl_->ColorMap(width, height);

	return render_target;
}

std::unique_ptr<Seed::RenderTarget> Seed::RenderTarget::PositionMap(const SwapChain & swap_chain, const DeviceContext & device_context, const unsigned int & width, const unsigned int & height)
{
	std::unique_ptr<RenderTarget> render_target(new RenderTarget(swap_chain, device_context));

	render_target->impl_->PositionMap(width, height);

	return render_target;
}

std::unique_ptr<Seed::RenderTarget> Seed::RenderTarget::NormalMap(const SwapChain & swap_chain, const DeviceContext & device_context, const unsigned int & width, const unsigned int & height)
{
	std::unique_ptr<RenderTarget> render_target(new RenderTarget(swap_chain, device_context));

	render_target->impl_->NormalMap(width, height);

	return render_target;
}

std::unique_ptr<Seed::RenderTarget> Seed::RenderTarget::R32Map(const SwapChain & swap_chain, const DeviceContext & device_context, const unsigned int & width, const unsigned int & height)
{
	std::unique_ptr<RenderTarget> render_target(new RenderTarget(swap_chain, device_context));

	render_target->impl_->NormalMap(width, height);

	return render_target;
}

ID3D11RenderTargetView * const Seed::RenderTarget::GetRTV(void) const
{
	return this->impl_->GetRTV();
}

ID3D11ShaderResourceView * const Seed::RenderTarget::GetSRV(void) const
{
	return this->impl_->GetSRV();
}

void Seed::RenderTarget::Clear(void) const
{
	this->impl_->Clear();
}

Seed::RenderTarget::RenderTarget(const SwapChain & swap_chain, const DeviceContext & device_context) noexcept(false)
	: impl_(std::make_unique<Impl>(swap_chain, device_context))
{

}

ID3D11RenderTargetView * const Seed::RenderTarget::Impl::GetRTV(void) const
{
	return this->rtv_.Get();
}

ID3D11ShaderResourceView * const Seed::RenderTarget::Impl::GetSRV(void) const
{
	return this->srv_.Get();
}

void Seed::RenderTarget::Impl::BackBuffer(void)
{
	Microsoft::WRL::ComPtr<ID3D11Device> device;
	
	this->device_context_->GetDevice(device.GetAddressOf());

	{ // バックバッファーのレンダーターゲットを作成
		Microsoft::WRL::ComPtr<ID3D11Texture2D> tex_2d;

		// バックバッファーテクスチャーを取得
		this->swap_chain_->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&tex_2d);

		// そのテクスチャーに対しレンダーターゲットビュー(RTV)を作成
		device->CreateRenderTargetView(tex_2d.Get(), nullptr, this->rtv_.GetAddressOf());
	}
}

void Seed::RenderTarget::Impl::ColorMap(const unsigned int & width, const unsigned int & height)
{
	Microsoft::WRL::ComPtr<ID3D11Device> device;

	this->device_context_->GetDevice(device.GetAddressOf());

	Microsoft::WRL::ComPtr<ID3D11Texture2D> texture_2d;

	D3D11_SHADER_RESOURCE_VIEW_DESC SRVDesc = {};
	D3D11_RENDER_TARGET_VIEW_DESC RTVDesc = {};
	D3D11_TEXTURE2D_DESC desc = {};
	//カラーマップ用テクスチャーとそのレンダーターゲットビュー、シェーダーリソースビューの作成	
	desc.Width = width;
	desc.Height = height;
	desc.MipLevels = 1;
	desc.ArraySize = 1;
	desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	desc.SampleDesc.Count = 1;
	desc.SampleDesc.Quality = 0;
	desc.Usage = D3D11_USAGE_DEFAULT;
	desc.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
	desc.CPUAccessFlags = 0;
	desc.MiscFlags = 0;
	device->CreateTexture2D(&desc, nullptr, texture_2d.GetAddressOf());

	RTVDesc.Format = desc.Format;
	RTVDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;
	RTVDesc.Texture2D.MipSlice = 0;
	device->CreateRenderTargetView(texture_2d.Get(), &RTVDesc, this->rtv_.GetAddressOf());

	SRVDesc.Format = desc.Format;
	SRVDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	SRVDesc.Texture2D.MipLevels = 1;
	device->CreateShaderResourceView(texture_2d.Get(), &SRVDesc, this->srv_.GetAddressOf());
}

void Seed::RenderTarget::Impl::PositionMap(const unsigned int & width, const unsigned int & height)
{
	Microsoft::WRL::ComPtr<ID3D11Device> device;

	this->device_context_->GetDevice(device.GetAddressOf());

	Microsoft::WRL::ComPtr<ID3D11Texture2D> texture_2d;

	D3D11_SHADER_RESOURCE_VIEW_DESC SRVDesc = {};
	D3D11_RENDER_TARGET_VIEW_DESC RTVDesc = {};
	D3D11_TEXTURE2D_DESC desc = {};
	desc.Width = width;
	desc.Height = height;
	desc.MipLevels = 1;
	desc.ArraySize = 1;
	desc.CPUAccessFlags = 0;
	desc.MiscFlags = 0;
	device->CreateTexture2D(&desc, nullptr, texture_2d.GetAddressOf());

	//ポジションマップ用テクスチャーとそのレンダーターゲットビュー、シェーダーリソースビューの作成	
	desc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
	desc.SampleDesc.Count = 1;
	desc.SampleDesc.Quality = 0;
	desc.Usage = D3D11_USAGE_DEFAULT;
	desc.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
	device->CreateTexture2D(&desc, nullptr, texture_2d.GetAddressOf());

	RTVDesc.Format = desc.Format;
	RTVDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;
	RTVDesc.Texture2D.MipSlice = 0;
	device->CreateRenderTargetView(texture_2d.Get(), &RTVDesc, this->rtv_.GetAddressOf());

	SRVDesc.Format = desc.Format;
	SRVDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	SRVDesc.Texture2D.MipLevels = 1;
	device->CreateShaderResourceView(texture_2d.Get(), &SRVDesc, this->srv_.GetAddressOf());
}

void Seed::RenderTarget::Impl::NormalMap(const unsigned int & width, const unsigned int & height)
{
	Microsoft::WRL::ComPtr<ID3D11Device> device;

	this->device_context_->GetDevice(device.GetAddressOf());

	Microsoft::WRL::ComPtr<ID3D11Texture2D> texture_2d;

	D3D11_SHADER_RESOURCE_VIEW_DESC SRVDesc = {};
	D3D11_RENDER_TARGET_VIEW_DESC RTVDesc = {};
	D3D11_TEXTURE2D_DESC desc = {};
	desc.Width = width;
	desc.Height = height;
	desc.MipLevels = 1;
	desc.ArraySize = 1;
	desc.CPUAccessFlags = 0;
	desc.MiscFlags = 0;
	device->CreateTexture2D(&desc, nullptr, texture_2d.GetAddressOf());

	//ノーマルマップ用テクスチャーとそのレンダーターゲットビュー、シェーダーリソースビューの作成	
	desc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
	desc.SampleDesc.Count = 1;
	desc.SampleDesc.Quality = 0;
	desc.Usage = D3D11_USAGE_DEFAULT;
	desc.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
	device->CreateTexture2D(&desc, nullptr, texture_2d.GetAddressOf());

	RTVDesc.Format = desc.Format;
	RTVDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;
	RTVDesc.Texture2D.MipSlice = 0;
	device->CreateRenderTargetView(texture_2d.Get(), &RTVDesc, this->rtv_.GetAddressOf());

	SRVDesc.Format = desc.Format;
	SRVDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	SRVDesc.Texture2D.MipLevels = 1;
	device->CreateShaderResourceView(texture_2d.Get(), &SRVDesc, this->srv_.GetAddressOf());
}

void Seed::RenderTarget::Impl::R32Map(const unsigned int & width, const unsigned int & height)
{
	Microsoft::WRL::ComPtr<ID3D11Device> device;

	this->device_context_->GetDevice(device.GetAddressOf());

	Microsoft::WRL::ComPtr<ID3D11Texture2D> texture_2d;

	D3D11_SHADER_RESOURCE_VIEW_DESC SRVDesc = {};
	D3D11_RENDER_TARGET_VIEW_DESC RTVDesc = {};
	D3D11_TEXTURE2D_DESC desc = {};
	desc.Width = width;
	desc.Height = height;
	desc.MipLevels = 1;
	desc.ArraySize = 1;
	desc.CPUAccessFlags = 0;
	desc.MiscFlags = 0;
	device->CreateTexture2D(&desc, nullptr, texture_2d.GetAddressOf());

	//ノーマルマップ用テクスチャーとそのレンダーターゲットビュー、シェーダーリソースビューの作成	
	desc.Format = DXGI_FORMAT_R32_FLOAT;
	desc.SampleDesc.Count = 1;
	desc.SampleDesc.Quality = 0;
	desc.Usage = D3D11_USAGE_DEFAULT;
	desc.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
	device->CreateTexture2D(&desc, nullptr, texture_2d.GetAddressOf());

	RTVDesc.Format = desc.Format;
	RTVDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;
	RTVDesc.Texture2D.MipSlice = 0;
	device->CreateRenderTargetView(texture_2d.Get(), &RTVDesc, this->rtv_.GetAddressOf());

	SRVDesc.Format = desc.Format;
	SRVDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	SRVDesc.Texture2D.MipLevels = 1;
	device->CreateShaderResourceView(texture_2d.Get(), &SRVDesc, this->srv_.GetAddressOf());
}

void Seed::RenderTarget::Impl::Clear(void) const
{
	float color[4] = { .2f,.4f,.8f,1.f };
	this->device_context_->ClearRenderTargetView(this->rtv_.Get(), color);
}
