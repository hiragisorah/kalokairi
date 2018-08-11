#pragma once

#include <DirectXMath.h>

#include <memory>
#include <vector>

namespace Seed
{
	class Graphics
	{
	public:
		Graphics(void);
		Graphics(Graphics const&) = delete;
		Graphics& operator= (Graphics const&) = delete;

		virtual ~Graphics(void);

	public:
		void Initialize(void * handle, const unsigned int & width, const unsigned int & height);
		void Run(void);
		void Finalize(void);

	public:
		void set_handle(void * handle);
		void set_width(const unsigned int & width);
		void set_height(const unsigned int & height);

		// Factory
	public:
		// - ViewPort
		const unsigned int CreateViewPort(const unsigned int & width, const unsigned int & height);
		void UnloadViewPort(const unsigned int & key);

		// - RenderTarget
		const unsigned int CreateBackBuffer(void);
		void UnloadRenderTarget(const unsigned int & key);

		// - DepthStencil
		const unsigned int CreateDepthStencil(const unsigned int & width, const unsigned int & height);
		void UnloadDepthStencil(const unsigned int & key);

		// - Geometry
		const unsigned int CreateBox(const DirectX::XMFLOAT3 & size = { 1, 1, 1 });
		const unsigned int CreateSphere(const float & diameter = 1, const size_t & tessellation = 16);
		void UnloadGeometry(const unsigned int & key);

		// Setup
	public:
		void ClearTarget(const std::vector<unsigned int> & render_targets, const std::vector<unsigned int> & depth_stencil);
		void SetViewPort(const unsigned int & view_port);
		void SetTarget(const std::vector<unsigned int> & render_targets, const unsigned int & depth_stencil);
		void Draw(const unsigned int & key);

	private:
		// Private implementation.
		class Impl;

		std::unique_ptr<Impl> impl_;
	};
}