#pragma once

#include <wrl/client.h>
#include <DirectXMath.h>
#include <d3d11.h>

#include <memory>
#include <vector>

#pragma comment(lib, "d3d11.lib")

namespace Seed
{
	using DeviceContext = Microsoft::WRL::ComPtr<ID3D11DeviceContext>;

	struct Vertex
	{
		Vertex(
			const DirectX::XMFLOAT3 & position,
			const DirectX::XMFLOAT3 & normal,
			const DirectX::XMFLOAT2 & uv)
			: position_(position)
			, normal_(normal)
			, uv_(uv)
		{}

		Vertex(DirectX::FXMVECTOR position, DirectX::FXMVECTOR normal, DirectX::FXMVECTOR textureCoordinate)
        {
            DirectX::XMStoreFloat3(&this->position_, position);
            DirectX::XMStoreFloat3(&this->normal_, normal);
            DirectX::XMStoreFloat2(&this->uv_, textureCoordinate);
        }

		DirectX::XMFLOAT3 position_;
		DirectX::XMFLOAT3 normal_;
		DirectX::XMFLOAT2 uv_;
	};

	using IndexCollection = std::vector<unsigned int>;
	using VertexCollection = std::vector<Vertex>;

	class Buffer final
	{
	public:
		Buffer(Buffer const&) = delete;
		Buffer& operator= (Buffer const&) = delete;

		virtual ~Buffer(void);

		// Factory
	public:
		static std::unique_ptr<Buffer> IndexBuffer(const DeviceContext & device_context, const IndexCollection & indices);
		static std::unique_ptr<Buffer> VertexBuffer(const DeviceContext & device_context, const VertexCollection & vertices);

		// Setup
	public:
		void Setup(void) const;

	private:
		Buffer(const DeviceContext & device_context) noexcept(false);

		// Private implementation.
		class Impl;

		std::unique_ptr<Impl> impl_;
	};
}