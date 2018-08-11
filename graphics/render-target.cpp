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

void Seed::RenderTarget::Impl::Clear(void) const
{
	float color[4] = {};
	this->device_context_->ClearRenderTargetView(this->rtv_.Get(), color);
}
