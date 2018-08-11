#pragma once

#include <DirectXMath.h>
#include <d3d11.h>
#include <wrl/client.h>

#include <memory>

#pragma comment(lib, "d3d11.lib")

namespace Seed
{
	using DeviceContext = Microsoft::WRL::ComPtr<ID3D11DeviceContext>;

	class DepthStencil final
	{
		friend class Graphics;

	public:
		DepthStencil(DepthStencil const&) = delete;
		DepthStencil& operator= (DepthStencil const&) = delete;

		virtual ~DepthStencil(void);

	private:
		static std::unique_ptr<DepthStencil> Create(const DeviceContext & device_context, const unsigned int & width, const unsigned int & height);

	private:
		void Clear(void) const;

	private:
		ID3D11DepthStencilView * const GetDSV(void) const;

	private:
		DepthStencil(const DeviceContext & device_context) noexcept(false);

		// Private implementation.
		class Impl;

		std::unique_ptr<Impl> impl_;
	};
}