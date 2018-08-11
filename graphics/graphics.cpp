#include "graphics.h"

#include "depth-stencil.h"
#include "geometry.h"
#include "render-target.h"
#include "shader.h"
#include "view-port.h"

#include "resource-pool.h"

#include <Windows.h>

using DeviceContext = Microsoft::WRL::ComPtr<ID3D11DeviceContext>;

class Seed::Graphics::Impl
{
private:
	DeviceContext device_context_;
	Microsoft::WRL::ComPtr<IDXGISwapChain> swap_chain_;
	Microsoft::WRL::ComPtr<ID3D11InputLayout> input_layout_;

public:
	void Initialize(void);
	void Run(void);
	void Finalize(void);

private:
	HWND handle_;
	unsigned int width_;
	unsigned int height_;

public:
	void set_handle(void * handle);
	void set_width(const unsigned int & width);
	void set_height(const unsigned int & height);

private:
	ResourcePool<RenderTarget> render_target_pool_;
	ResourcePool<DepthStencil> depth_stencil_pool_;
	ResourcePool<ViewPort> view_port_pool_;
	ResourcePool<Shader> shader_pool_;
	ResourcePool<Geometry> geometry_pool_;

private:
	const unsigned int LoadViewPort(std::unique_ptr<ViewPort> && view_port);
	const unsigned int LoadRenderTarget(std::unique_ptr<RenderTarget> && render_target);
	const unsigned int LoadDepthStencil(std::unique_ptr<DepthStencil> && depth_stencil);
	const unsigned int LoadShader(std::unique_ptr<Shader> && shader);
	const unsigned int LoadGeometry(std::unique_ptr<Geometry> && geometry);

public:
	const unsigned int CreateViewPort(const unsigned int & width, const unsigned int & height);
		
	const unsigned int CreateBackBuffer(void);

	const unsigned int CreateDepthStencil(const unsigned int & width, const unsigned int & height);

	const unsigned int CreateShader(const std::string & file_name);

	const unsigned int CreateBox(const DirectX::XMFLOAT3 & size);
	const unsigned int CreateSphere(const float & diameter, const size_t & tessellation);

	void UnloadViewPort(const unsigned int & key);
	void UnloadRenderTarget(const unsigned int & key);
	void UnloadDepthStencil(const unsigned int & key);
	void UnloadShader(const unsigned int & key);
	void UnloadGeometry(const unsigned int & key);

	void ClearTarget(const std::vector<unsigned int> & render_targets, const std::vector<unsigned int> & depth_stencil);
	void SetViewPort(const unsigned int & view_port);
	void SetTarget(const std::vector<unsigned int> & render_targets, const unsigned int & depth_stencil);
	void SetShader(const unsigned int & shader);
	void Draw(const unsigned int & key);
};

const unsigned int Seed::Graphics::CreateBox(const DirectX::XMFLOAT3 & size)
{
	return this->impl_->CreateBox(size);
}

const unsigned int Seed::Graphics::CreateSphere(const float & diameter, const size_t & tessellation)
{
	return this->impl_->CreateSphere(diameter, tessellation);
}

void Seed::Graphics::UnloadGeometry(const unsigned int & key)
{
	this->impl_->UnloadGeometry(key);
}

void Seed::Graphics::ClearTarget(const std::vector<unsigned int>& render_targets, const std::vector<unsigned int>& depth_stencil)
{
	this->impl_->ClearTarget(render_targets, depth_stencil);
}

void Seed::Graphics::SetViewPort(const unsigned int & view_port)
{
	this->impl_->SetViewPort(view_port);
}

void Seed::Graphics::SetTarget(const std::vector<unsigned int> & render_targets, const unsigned int & depth_stencil)
{
	this->impl_->SetTarget(render_targets, depth_stencil);
}

void Seed::Graphics::SetShader(const unsigned int & shader)
{
	this->impl_->SetShader(shader);
}

void Seed::Graphics::Draw(const unsigned int & key)
{
	this->impl_->Draw(key);
}

Seed::Graphics::~Graphics(void)
{
	
}

void Seed::Graphics::Initialize(void * handle, const unsigned int & width, const unsigned int & height)
{
	this->impl_->set_handle(handle);
	this->impl_->set_width(width);
	this->impl_->set_height(height);
	this->impl_->Initialize();
}

void Seed::Graphics::Run(void)
{
	this->impl_->Run();
}

void Seed::Graphics::Finalize(void)
{
	this->impl_->Finalize();
}

void Seed::Graphics::set_handle(void * handle)
{
	this->impl_->set_handle(handle);
}

void Seed::Graphics::set_width(const unsigned int & width)
{
	this->impl_->set_width(width);
}

void Seed::Graphics::set_height(const unsigned int & height)
{
	this->impl_->set_height(height);
}

const unsigned int Seed::Graphics::CreateDepthStencil(const unsigned int & width, const unsigned int & height)
{
	return this->impl_->CreateDepthStencil(width, height);
}

void Seed::Graphics::UnloadDepthStencil(const unsigned int & key)
{
	this->impl_->UnloadDepthStencil(key);
}

const unsigned int Seed::Graphics::CreateShader(const std::string & file_name)
{
	return this->impl_->CreateShader(file_name);
}

void Seed::Graphics::UnloadShader(const unsigned int & key)
{
	this->impl_->UnloadShader(key);
}

const unsigned int Seed::Graphics::CreateViewPort(const unsigned int & width, const unsigned int & height)
{
	return this->impl_->CreateViewPort(width, height);
}

void Seed::Graphics::UnloadViewPort(const unsigned int & key)
{
	this->impl_->UnloadViewPort(key);
}

const unsigned int Seed::Graphics::CreateBackBuffer(void)
{
	return this->impl_->CreateBackBuffer();
}

void Seed::Graphics::UnloadRenderTarget(const unsigned int & key)
{
	this->impl_->UnloadRenderTarget(key);
}

Seed::Graphics::Graphics(void)
	: impl_(std::make_unique<Impl>())
{
}

void Seed::Graphics::Impl::Initialize(void)
{
	Microsoft::WRL::ComPtr<ID3D11Device> device;

	this->device_context_->GetDevice(device.GetAddressOf());
	
	{ // デバイスとスワップチェーンの作成 
		DXGI_SWAP_CHAIN_DESC sd;
		memset(&sd, 0, sizeof(sd));
		sd.BufferCount = 1;
		sd.BufferDesc.Width = this->width_;
		sd.BufferDesc.Height = this->height_;
		sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		sd.BufferDesc.RefreshRate.Numerator = 60;
		sd.BufferDesc.RefreshRate.Denominator = 1;
		sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		sd.OutputWindow = this->handle_;
		sd.SampleDesc.Count = 1;
		sd.SampleDesc.Quality = 0;
		sd.Windowed = true;

		D3D_FEATURE_LEVEL feature_levels = D3D_FEATURE_LEVEL_11_0;
		D3D_FEATURE_LEVEL * feature_level = nullptr;

		D3D11CreateDeviceAndSwapChain(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr,
			0, &feature_levels, 1, D3D11_SDK_VERSION, &sd, this->swap_chain_.GetAddressOf(), device.GetAddressOf(),
			feature_level, &this->device_context_);
	}
}

void Seed::Graphics::Impl::Run(void)
{
	this->swap_chain_->Present(1, 0);
}

void Seed::Graphics::Impl::Finalize(void)
{
}

void Seed::Graphics::Impl::set_handle(void * handle)
{
	this->handle_ = static_cast<HWND>(handle);
}

void Seed::Graphics::Impl::set_width(const unsigned int & width)
{
	this->width_ = width;
}

void Seed::Graphics::Impl::set_height(const unsigned int & height)
{
	this->height_ = height;
}

const unsigned int Seed::Graphics::Impl::LoadViewPort(std::unique_ptr<ViewPort>&& view_port)
{
	return this->view_port_pool_.Load(view_port);
}

const unsigned int Seed::Graphics::Impl::LoadGeometry(std::unique_ptr<Geometry> && geometry)
{
	return this->geometry_pool_.Load(geometry);
}

const unsigned int Seed::Graphics::Impl::LoadRenderTarget(std::unique_ptr<RenderTarget> && render_target)
{
	return this->render_target_pool_.Load(render_target);
}

const unsigned int Seed::Graphics::Impl::LoadDepthStencil(std::unique_ptr<DepthStencil>&& depth_stencil)
{
	return this->depth_stencil_pool_.Load(depth_stencil);
}

const unsigned int Seed::Graphics::Impl::LoadShader(std::unique_ptr<Shader>&& shader)
{
	return this->shader_pool_.Load(shader);
}

const unsigned int Seed::Graphics::Impl::CreateViewPort(const unsigned int & width, const unsigned int & height)
{
	return this->LoadViewPort(ViewPort::Create(this->device_context_, width, height));
}

const unsigned int Seed::Graphics::Impl::CreateBackBuffer(void)
{
	return this->LoadRenderTarget(RenderTarget::BackBuffer(this->swap_chain_, this->device_context_));
}

const unsigned int Seed::Graphics::Impl::CreateDepthStencil(const unsigned int & width, const unsigned int & height)
{
	return this->LoadDepthStencil(DepthStencil::Create(this->device_context_, width, height));
}

const unsigned int Seed::Graphics::Impl::CreateShader(const std::string & file_name)
{
	return this->LoadShader(Shader::Create(this->device_context_, file_name));
}

const unsigned int Seed::Graphics::Impl::CreateBox(const DirectX::XMFLOAT3 & size)
{
	return this->LoadGeometry(Geometry::Box(this->device_context_, size));
}

const unsigned int Seed::Graphics::Impl::CreateSphere(const float & diameter, const size_t & tessellation)
{
	return this->LoadGeometry(Geometry::Sphere(this->device_context_, diameter, tessellation));
}

void Seed::Graphics::Impl::UnloadViewPort(const unsigned int & key)
{
	this->view_port_pool_.Unload(key);
}

void Seed::Graphics::Impl::UnloadGeometry(const unsigned int & key)
{
	this->geometry_pool_.Unload(key);
}

void Seed::Graphics::Impl::UnloadRenderTarget(const unsigned int & key)
{
	this->render_target_pool_.Unload(key);
}

void Seed::Graphics::Impl::UnloadDepthStencil(const unsigned int & key)
{
	this->depth_stencil_pool_.Unload(key);
}

void Seed::Graphics::Impl::ClearTarget(const std::vector<unsigned int>& render_targets, const std::vector<unsigned int>& depth_stencil)
{
	for (auto & rt : render_targets)
		this->render_target_pool_.Get(rt)->Clear();

	for (auto & ds : depth_stencil)
		this->depth_stencil_pool_.Get(ds)->Clear();
}

void Seed::Graphics::Impl::SetViewPort(const unsigned int & view_port)
{
	this->view_port_pool_.Get(view_port)->Setup();
}

void Seed::Graphics::Impl::SetTarget(const std::vector<unsigned int>& render_targets, const unsigned int & depth_stencil)
{
	std::vector<ID3D11RenderTargetView*> rtvs_;

	for (auto & rt : render_targets)
		rtvs_.emplace_back(this->render_target_pool_.Get(rt)->GetRTV());

	ID3D11DepthStencilView * dsv = this->depth_stencil_pool_.Get(depth_stencil)->GetDSV();

	this->device_context_->OMSetRenderTargets(rtvs_.size(), rtvs_.data(), dsv);
}

void Seed::Graphics::Impl::SetShader(const unsigned int & shader)
{
	this->shader_pool_.Get(shader)->Setup();
}

void Seed::Graphics::Impl::Draw(const unsigned int & key)
{
	this->geometry_pool_.Get(key)->Draw();
}
