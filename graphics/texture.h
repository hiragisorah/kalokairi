#pragma once

#include <DirectXMath.h>
#include <d3d11.h>
#include <wrl/client.h>

#include <memory>
#include <string>

#pragma comment(lib, "d3d11.lib")

namespace Seed
{
	using DeviceContext = Microsoft::WRL::ComPtr<ID3D11DeviceContext>;

	class Texture final
	{
		friend class Graphics;

	public:
		Texture(Texture const&) = delete;
		Texture& operator= (Texture const&) = delete;

		virtual ~Texture(void);

		// Factory
	private:
		static std::unique_ptr<Texture> Load(const DeviceContext & device_context, const std::string & file_name);

	private:
		Texture(const DeviceContext & device_context) noexcept(false);

		// Private implementation.
		class Impl;

		std::unique_ptr<Impl> impl_;
	};
}