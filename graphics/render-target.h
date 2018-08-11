#pragma once

#include <DirectXMath.h>
#include <d3d11.h>
#include <wrl/client.h>

#include <memory>

#pragma comment(lib, "d3d11.lib")

namespace Seed
{
	using DeviceContext = Microsoft::WRL::ComPtr<ID3D11DeviceContext>;
	using SwapChain = Microsoft::WRL::ComPtr<IDXGISwapChain>;

	class RenderTarget final
	{
		friend class Graphics;

	public:
		RenderTarget(RenderTarget const&) = delete;
		RenderTarget& operator= (RenderTarget const&) = delete;

		virtual ~RenderTarget(void);

		// Factory
	private:
		static std::unique_ptr<RenderTarget> BackBuffer(const SwapChain & swap_chain, const DeviceContext & device_context);

	private:
		ID3D11RenderTargetView * const GetRTV(void) const;
		ID3D11ShaderResourceView * const GetSRV(void) const;
		void Clear(void) const;

	private:
		RenderTarget(const SwapChain & swap_chain, const DeviceContext & device_context) noexcept(false);

		// Private implementation.
		class Impl;

		std::unique_ptr<Impl> impl_;
	};
}