#pragma once

#include <DirectXMath.h>
#include <d3d11.h>
#include <wrl/client.h>

#include <memory>

#pragma comment(lib, "d3d11.lib")

namespace Seed
{
	using DeviceContext = Microsoft::WRL::ComPtr<ID3D11DeviceContext>;

	class ViewPort final
	{
		friend class Graphics;

	public:
		ViewPort(ViewPort const&) = delete;
		ViewPort& operator= (ViewPort const&) = delete;

		virtual ~ViewPort(void);

	private:
		static std::unique_ptr<ViewPort> Create(const DeviceContext & device_context, const unsigned int & width, const unsigned int & height);

	private:
		void Setup(void) const;

	private:
		ViewPort(const DeviceContext & device_context) noexcept(false);

		// Private implementation.
		class Impl;

		std::unique_ptr<Impl> impl_;
	};
}