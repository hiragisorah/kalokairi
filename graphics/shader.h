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

	class Shader final
	{
	public:
		Shader(Shader const&) = delete;
		Shader& operator= (Shader const&) = delete;

		virtual ~Shader(void);

		// Factory
	public:
		static std::unique_ptr<Shader> Create(const DeviceContext & device_context, const std::string & file_name);
		
		// Setup
	public:
		void Setup(void * constant_buffer) const;

	private:
		Shader(const DeviceContext & device_context) noexcept(false);

		// Private implementation.
		class Impl;

		std::unique_ptr<Impl> impl_;
	};
}