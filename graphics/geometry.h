#pragma once

#include <DirectXMath.h>
#include <d3d11.h>
#include <wrl/client.h>

#include <memory>

#pragma comment(lib, "d3d11.lib")

namespace Seed
{
	using DeviceContext = Microsoft::WRL::ComPtr<ID3D11DeviceContext>;
	
	class Geometry final
	{
		friend class Graphics;

	public:
		Geometry(Geometry const&) = delete;
		Geometry& operator= (Geometry const&) = delete;

		virtual ~Geometry(void);

		// Factory
	private:
		static std::unique_ptr<Geometry> Box(const DeviceContext & device_context, const DirectX::XMFLOAT3 & size = { 1, 1, 1 });
		static std::unique_ptr<Geometry> Sphere(const DeviceContext & device_context, const float & diameter = 1, const size_t & tessellation = 16);

	private:
		void Draw(void) const;

	private:
		Geometry(const DeviceContext & device_context) noexcept(false);

		// Private implementation.
		class Impl;

		std::unique_ptr<Impl> impl_;
	};
}