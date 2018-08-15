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

		// - SHader
		const unsigned int CreateShader(const std::string & file_name);
		void UnloadShader(const unsigned int & key);

		// - Geometry
		const unsigned int CreatePlane(const unsigned int & div_x, const unsigned int & div_y, const DirectX::XMFLOAT2 & size = { 1, 1 });
		const unsigned int CreateBox(const DirectX::XMFLOAT3 & size = { 1, 1, 1 });
		const unsigned int CreateSphere(const float & diameter = 1, const unsigned int & tessellation = 16);
		const unsigned int CreateGeoSphere(const float & diameter = 1, const unsigned int & tessellation = 16);
		const unsigned int CreateCapsule(const DirectX::XMFLOAT3 & p1, const DirectX::XMFLOAT3 & p2, const float & diameter = 1, const unsigned int & tessellation = 5);
		void UnloadGeometry(const unsigned int & key);

		// Setup
	public:
		void EnableWireFrame(const bool & enable);
		void ClearTarget(const std::vector<unsigned int> & render_targets, const std::vector<unsigned int> & depth_stencil);
		void SetViewPort(const unsigned int & view_port);
		void SetTarget(const std::vector<unsigned int> & render_targets, const unsigned int & depth_stencil);
		void SetShader(const unsigned int & shader, void * constant_buffer);
		void Draw(const unsigned int & key);

	private:
		// Private implementation.
		class Impl;

		std::unique_ptr<Impl> impl_;
	};
}