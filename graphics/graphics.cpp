#include "graphics.h"

#include "depth-stencil.h"
#include "geometry.h"
#include "render-target.h"
#include "shader.h"
#include "view-port.h"
#include "texture.h"

#include "resource-pool.h"

#include <Windows.h>

using DeviceContext = Microsoft::WRL::ComPtr<ID3D11DeviceContext>;

class Seed::Graphics::Impl
{
private:
	DeviceContext device_context_;
	Microsoft::WRL::ComPtr<IDXGISwapChain> swap_chain_;
	Microsoft::WRL::ComPtr<ID3D11InputLayout> input_layout_;

private:
	Microsoft::WRL::ComPtr<ID3D11RasterizerState> wire_frame_;
	Microsoft::WRL::ComPtr<ID3D11RasterizerState> ccw_;
	Microsoft::WRL::ComPtr<ID3D11RasterizerState> cw_;
	Microsoft::WRL::ComPtr<ID3D11RasterizerState> cull_none_;
	Microsoft::WRL::ComPtr<ID3D11BlendState> blend_state_;

public:
	void Initialize(void);
	const bool Run(void);
	void Finalize(void);

private:
	HWND handle_;
	unsigned int width_;
	unsigned int height_;

public:
	void set_handle(void * handle);
	void set_width(const unsigned int & width);
	void set_height(const unsigned int & height);

	const unsigned int & width(void);
	const unsigned int & height(void);

private:
	Microsoft::WRL::ComPtr<ID3D11Buffer> main_buffer_;
	Microsoft::WRL::ComPtr<ID3D11Buffer> model_buffer_;

private:
	ResourcePool<RenderTarget> render_target_pool_;
	ResourcePool<DepthStencil> depth_stencil_pool_;
	ResourcePool<ViewPort> view_port_pool_;
	ResourcePool<Shader> shader_pool_;
	ResourcePool<Geometry> geometry_pool_;
	ResourcePool<Texture> texture_pool_;

public:
	struct MainCB
	{
		MainCB(void)
			: view_(DirectX::XMMatrixIdentity())
			, projection_(DirectX::XMMatrixIdentity())
			, tex_uv_(DirectX::XMMatrixIdentity())
			, eye_({ 0, 0, 0 })
			, dir_light_({ 0, 0, 0 })
			, timer_(0)
			, view_port_({ 0, 0 })
			, screen_color_({1,1,1,1})
		{}

		DirectX::XMMATRIX view_;
		DirectX::XMMATRIX projection_;
		DirectX::XMMATRIX light_view_;
		DirectX::XMMATRIX light_proj_;
		DirectX::XMMATRIX tex_uv_;
		DirectX::XMFLOAT3A eye_;
		DirectX::XMFLOAT3A dir_light_;
		__declspec(align(16)) unsigned int timer_;
		DirectX::XMFLOAT2A view_port_;
		DirectX::XMFLOAT4 screen_color_;

	} main_cb_;

	struct ModelCB
	{
		ModelCB(void)
			: world_(DirectX::XMMatrixIdentity())
			, color_({ 1, 1, 1, 1 })
			, screen_({ 1,1,1,1 })
		{}

		DirectX::XMMATRIX world_;
		DirectX::XMFLOAT4 color_;
		DirectX::XMFLOAT4 screen_;
	} model_cb_;

	Microsoft::WRL::ComPtr<ID3D11SamplerState> cmp_;

private:
	const unsigned int LoadViewPort(std::unique_ptr<ViewPort> && view_port);
	const unsigned int LoadRenderTarget(std::unique_ptr<RenderTarget> && render_target);
	const unsigned int LoadDepthStencil(std::unique_ptr<DepthStencil> && depth_stencil);
	const unsigned int LoadShader(std::unique_ptr<Shader> && shader);
	const unsigned int LoadGeometry(std::unique_ptr<Geometry> && geometry);
	const unsigned int LoadTexture(std::unique_ptr<Texture> && texture);

public:
	const unsigned int CreateViewPort(const unsigned int & width, const unsigned int & height);
		
	const unsigned int CreateBackBuffer(void);
	const unsigned int CreateColorMap(const unsigned int & width, const unsigned int & height);
	const unsigned int CreatePositionMap(const unsigned int & width, const unsigned int & height);
	const unsigned int CreateNormalMap(const unsigned int & width, const unsigned int & height);
	const unsigned int CreateR32Map(const unsigned int & width, const unsigned int & height);

	const unsigned int CreateDepthStencil(const unsigned int & width, const unsigned int & height);

	const unsigned int CreateShader(const std::string & file_name);
	const unsigned int CreateTexture(const std::string & file_name);

	const unsigned int CreatePlane(const unsigned int & div_x, const unsigned int & div_y, const DirectX::XMFLOAT2 & size = { 1, 1 });
	const unsigned int CreateBox(const DirectX::XMFLOAT3 & size);
	const unsigned int CreateSphere(const float & diameter, const unsigned int & tessellation);
	const unsigned int CreateGeoSphere(const float & diameter, const unsigned int & tessellation);
	const unsigned int CreateCapsule(const DirectX::XMFLOAT3 & p1, const DirectX::XMFLOAT3 & p2, const float & diameter, const unsigned int & tessellation);
	
	const DirectX::Vector2 GetTextureSize(const unsigned int & key);

	void CCW(void);
	void CW(void);
	void CullNone(void);

	void UnloadViewPort(const unsigned int & key);
	void UnloadRenderTarget(const unsigned int & key);
	void UnloadDepthStencil(const unsigned int & key);
	void UnloadShader(const unsigned int & key);
	void UnloadGeometry(const unsigned int & key);
	void UnloadTexture(const unsigned int & key);

	void EnableWireFrame(const bool & enable);
	void ClearTarget(const std::vector<unsigned int> & render_targets, const std::vector<unsigned int> & depth_stencil);
	void SetViewPort(const unsigned int & view_port);
	void SetTarget(const std::vector<unsigned int> & render_targets, const unsigned int & depth_stencil);
	void SetShader(const unsigned int & shader, void * constant_buffer);
	void UpdateMainConstantBuffer(void);
	void UpdateModelConstantBuffer(void);
	void Draw(const unsigned int & key);
	void DrawScreen(const std::vector<unsigned int>& render_targets);
	void DrawTexture(const unsigned int & texture_id);

	void SetWorld(const DirectX::XMMATRIX & world);
	void SetView(const DirectX::XMMATRIX & view);
	void SetProjection(const DirectX::XMMATRIX & projection);
	void SetEye(const DirectX::Vector3 & eye);
	void SetLightView(const DirectX::XMMATRIX & light_view);
	void SetDirectionLight(const DirectX::Vector3 & dir_light);
	void SetDiffuse(const DirectX::Vector4 & color);
	void SetRTSRV(const std::vector<unsigned int>& render_targets);
	void SetBlend(const bool & blend);
	void SetScreenColor(const DirectX::Vector4 & color);
};

const unsigned int Seed::Graphics::CreatePlane(const unsigned int & div_x, const unsigned int & div_y, const DirectX::XMFLOAT2 & size)
{
	return this->impl_->CreatePlane(div_x, div_y, size);
}

const unsigned int Seed::Graphics::CreateBox(const DirectX::XMFLOAT3 & size)
{
	return this->impl_->CreateBox(size);
}

const unsigned int Seed::Graphics::CreateSphere(const float & diameter, const unsigned int & tessellation)
{
	return this->impl_->CreateSphere(diameter, tessellation);
}

const unsigned int Seed::Graphics::CreateGeoSphere(const float & diameter, const unsigned int & tessellation)
{
	return this->impl_->CreateGeoSphere(diameter, tessellation);
}

const unsigned int Seed::Graphics::CreateCapsule(const DirectX::XMFLOAT3 & p1, const DirectX::XMFLOAT3 & p2, const float & diameter, const unsigned int & tessellation)
{
	return this->impl_->CreateCapsule(p1, p2, diameter, tessellation);
}

void Seed::Graphics::UnloadGeometry(const unsigned int & key)
{
	this->impl_->UnloadGeometry(key);
}

void Seed::Graphics::CCW(void)
{
	this->impl_->CCW();
}

void Seed::Graphics::CW(void)
{
	this->impl_->CW();
}

void Seed::Graphics::CullNone(void)
{
	this->impl_->CullNone();
}

void Seed::Graphics::EnableWireFrame(const bool & enable)
{
	this->impl_->EnableWireFrame(enable);
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

void Seed::Graphics::SetShader(const unsigned int & shader, void * constant_buffer)
{
	this->impl_->SetShader(shader, constant_buffer);
}

void Seed::Graphics::UpdateMainConstantBuffer(void)
{
	this->impl_->UpdateMainConstantBuffer();
}

void Seed::Graphics::UpdateModelConstantBuffer(void)
{
	this->impl_->UpdateModelConstantBuffer();
}

void Seed::Graphics::Draw(const unsigned int & key)
{
	this->impl_->Draw(key);
}

void Seed::Graphics::DrawScreen(const std::vector<unsigned int>& render_targets)
{
	this->impl_->DrawScreen(render_targets);
}

void Seed::Graphics::DrawTexture(const unsigned int & texture_id)
{
	this->impl_->DrawTexture(texture_id);
}

void Seed::Graphics::SetWorld(const DirectX::XMMATRIX & world)
{
	this->impl_->SetWorld(world);
}

void Seed::Graphics::SetView(const DirectX::XMMATRIX & view)
{
	this->impl_->SetView(view);
}

void Seed::Graphics::SetProjection(const DirectX::XMMATRIX & projection)
{
	this->impl_->SetProjection(projection);
}

void Seed::Graphics::SetEye(const DirectX::Vector3 & eye)
{
	this->impl_->SetEye(eye);
}

void Seed::Graphics::SetDirectionLight(const DirectX::Vector3 & dir_light)
{
	this->impl_->SetDirectionLight(dir_light);
}

void Seed::Graphics::SetDiffuse(const DirectX::Vector4 & color)
{
	this->impl_->SetDiffuse(color);
}

void Seed::Graphics::SetRTSRV(const std::vector<unsigned int>& render_targets)
{
	this->impl_->SetRTSRV(render_targets);
}

void Seed::Graphics::SetBlend(const bool & blend)
{
	this->impl_->SetBlend(blend);
}

void Seed::Graphics::SetScreenColor(const DirectX::Vector4 & color)
{
	this->impl_->SetScreenColor(color);
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

const bool Seed::Graphics::Run(void)
{
	return this->impl_->Run();
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

const unsigned int & Seed::Graphics::width(void)
{
	return this->impl_->width();
}

const unsigned int & Seed::Graphics::height(void)
{
	return this->impl_->height();
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

const DirectX::Vector2 Seed::Graphics::GetTextureSize(const unsigned int & key)
{
	return this->impl_->GetTextureSize(key);
}

const unsigned int Seed::Graphics::CreateTexture(const std::string & file_name)
{
	return this->impl_->CreateTexture(file_name);
}

void Seed::Graphics::UnloadTexture(const unsigned int & key)
{
	this->impl_->UnloadTexture(key);
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

const unsigned int Seed::Graphics::CreateColorMap(const unsigned int & width, const unsigned int & height)
{
	return this->impl_->CreateColorMap(width, height);
}

const unsigned int Seed::Graphics::CreatePositionMap(const unsigned int & width, const unsigned int & height)
{
	return this->impl_->CreatePositionMap(width, height);
}

const unsigned int Seed::Graphics::CreateNormalMap(const unsigned int & width, const unsigned int & height)
{
	return this->impl_->CreateNormalMap(width, height);
}

const unsigned int Seed::Graphics::CreateR32Map(const unsigned int & width, const unsigned int & height)
{
	return this->impl_->CreateR32Map(width, height);
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

	{
		D3D11_RASTERIZER_DESC desc = {};

		desc.CullMode = D3D11_CULL_BACK;
		desc.FillMode = D3D11_FILL_WIREFRAME;
		desc.DepthClipEnable = true;
		desc.MultisampleEnable = true;

		device->CreateRasterizerState(&desc, this->wire_frame_.GetAddressOf());

		desc.FillMode = D3D11_FILL_SOLID;

		device->CreateRasterizerState(&desc, this->ccw_.GetAddressOf());

		desc.CullMode = D3D11_CULL_FRONT;

		device->CreateRasterizerState(&desc, this->cw_.GetAddressOf());

		desc.CullMode = D3D11_CULL_NONE;

		device->CreateRasterizerState(&desc, this->cull_none_.GetAddressOf());
	}

	{
		D3D11_BUFFER_DESC bd;
		bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		bd.ByteWidth = sizeof(MainCB);
		bd.CPUAccessFlags = 0;
		bd.MiscFlags = 0;
		bd.StructureByteStride = 0;
		bd.Usage = D3D11_USAGE_DEFAULT;

		device->CreateBuffer(&bd, nullptr, this->main_buffer_.GetAddressOf());
	}

	{
		D3D11_BUFFER_DESC bd;
		bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		bd.ByteWidth = sizeof(ModelCB);
		bd.CPUAccessFlags = 0;
		bd.MiscFlags = 0;
		bd.StructureByteStride = 0;
		bd.Usage = D3D11_USAGE_DEFAULT;

		device->CreateBuffer(&bd, nullptr, this->model_buffer_.GetAddressOf());
	}

	this->device_context_->VSSetConstantBuffers(0, 1, this->main_buffer_.GetAddressOf());
	this->device_context_->GSSetConstantBuffers(0, 1, this->main_buffer_.GetAddressOf());
	this->device_context_->HSSetConstantBuffers(0, 1, this->main_buffer_.GetAddressOf());
	this->device_context_->DSSetConstantBuffers(0, 1, this->main_buffer_.GetAddressOf());
	this->device_context_->PSSetConstantBuffers(0, 1, this->main_buffer_.GetAddressOf());

	this->device_context_->VSSetConstantBuffers(1, 1, this->model_buffer_.GetAddressOf());
	this->device_context_->GSSetConstantBuffers(1, 1, this->model_buffer_.GetAddressOf());
	this->device_context_->HSSetConstantBuffers(1, 1, this->model_buffer_.GetAddressOf());
	this->device_context_->DSSetConstantBuffers(1, 1, this->model_buffer_.GetAddressOf());
	this->device_context_->PSSetConstantBuffers(1, 1, this->model_buffer_.GetAddressOf());

	this->main_cb_.view_port_ = { static_cast<float>(this->width_), static_cast<float>(this->height_) };

	this->main_cb_.tex_uv_.r[0] = DirectX::XMVectorSet(+.5f, +.0f, .0f, .0f);
	this->main_cb_.tex_uv_.r[1] = DirectX::XMVectorSet(+.0f, -.5f, .0f, .0f);
	this->main_cb_.tex_uv_.r[2] = DirectX::XMVectorSet(+.0f, +.0f, 1.f, .0f);
	this->main_cb_.tex_uv_.r[3] = DirectX::XMVectorSet(+.5f, +.5f, .0f, 1.f);
;
	this->main_cb_.light_view_ = DirectX::Matrix::CreateLookAt(DirectX::Vector3(0, 8.f, -8), DirectX::Vector3::Zero, DirectX::Vector3(0, 1, 0));
	//this->main_cb_.light_proj_ = DirectX::Matrix::CreatePerspectiveFieldOfView(DirectX::XM_PIDIV4, static_cast<float>(this->width_) / static_cast<float>(this->height_), 5.0f, 20.f);
	this->main_cb_.light_proj_ = DirectX::Matrix::CreateOrthographic(20, 15, 2.0f, 16.f);
	
	D3D11_SAMPLER_DESC desc = {};
	desc.AddressU = D3D11_TEXTURE_ADDRESS_BORDER;
	desc.AddressV = D3D11_TEXTURE_ADDRESS_BORDER;
	desc.AddressW = D3D11_TEXTURE_ADDRESS_BORDER;
	desc.BorderColor[0] = 1.0f;
	desc.BorderColor[1] = 1.0f;
	desc.BorderColor[2] = 1.0f;
	desc.BorderColor[3] = 1.0f;
	desc.ComparisonFunc = D3D11_COMPARISON_LESS_EQUAL;
	desc.Filter = D3D11_FILTER_COMPARISON_MIN_MAG_MIP_LINEAR;
	desc.MaxAnisotropy = 1;
	desc.MipLODBias = 0;
	desc.MinLOD = -FLT_MAX;
	desc.MaxLOD = +FLT_MAX;

	device->CreateSamplerState(&desc, &this->cmp_);

	this->device_context_->PSSetSamplers(1, 1, this->cmp_.GetAddressOf());

	{
		D3D11_BLEND_DESC blend_desc = {};

		blend_desc.AlphaToCoverageEnable = false;
		blend_desc.IndependentBlendEnable = false;

		blend_desc.RenderTarget[0].BlendEnable = true;
		blend_desc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
		blend_desc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
		blend_desc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
		blend_desc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
		blend_desc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
		blend_desc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
		blend_desc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

		device->CreateBlendState(&blend_desc, this->blend_state_.GetAddressOf());
	}
}

const bool Seed::Graphics::Impl::Run(void)
{
	this->main_cb_.timer_++;
	this->swap_chain_->Present(0, 0);
	
	return true;
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

const unsigned int & Seed::Graphics::Impl::width(void)
{
	return this->width_;
}

const unsigned int & Seed::Graphics::Impl::height(void)
{
	return this->height_;
}

const unsigned int Seed::Graphics::Impl::LoadViewPort(std::unique_ptr<ViewPort> && view_port)
{
	return this->view_port_pool_.Load(view_port);
}

const unsigned int Seed::Graphics::Impl::LoadGeometry(std::unique_ptr<Geometry> && geometry)
{
	return this->geometry_pool_.Load(geometry);
}

const unsigned int Seed::Graphics::Impl::LoadTexture(std::unique_ptr<Texture> && texture)
{
	return this->texture_pool_.Load(texture);
}

const unsigned int Seed::Graphics::Impl::LoadRenderTarget(std::unique_ptr<RenderTarget> && render_target)
{
	return this->render_target_pool_.Load(render_target);
}

const unsigned int Seed::Graphics::Impl::LoadDepthStencil(std::unique_ptr<DepthStencil> && depth_stencil)
{
	return this->depth_stencil_pool_.Load(depth_stencil);
}

const unsigned int Seed::Graphics::Impl::LoadShader(std::unique_ptr<Shader> && shader)
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

const unsigned int Seed::Graphics::Impl::CreateColorMap(const unsigned int & width, const unsigned int & height)
{
	return this->LoadRenderTarget(RenderTarget::ColorMap(this->swap_chain_, this->device_context_, width, height));
}

const unsigned int Seed::Graphics::Impl::CreatePositionMap(const unsigned int & width, const unsigned int & height)
{
	return this->LoadRenderTarget(RenderTarget::PositionMap(this->swap_chain_, this->device_context_, width, height));
}

const unsigned int Seed::Graphics::Impl::CreateNormalMap(const unsigned int & width, const unsigned int & height)
{
	return this->LoadRenderTarget(RenderTarget::NormalMap(this->swap_chain_, this->device_context_, width, height));
}

const unsigned int Seed::Graphics::Impl::CreateR32Map(const unsigned int & width, const unsigned int & height)
{
	return this->LoadRenderTarget(RenderTarget::R32Map(this->swap_chain_, this->device_context_, width, height));
}

const unsigned int Seed::Graphics::Impl::CreateDepthStencil(const unsigned int & width, const unsigned int & height)
{
	return this->LoadDepthStencil(DepthStencil::Create(this->device_context_, width, height));
}

const unsigned int Seed::Graphics::Impl::CreateShader(const std::string & file_name)
{
	return this->LoadShader(Shader::Create(this->device_context_, file_name));
}

const unsigned int Seed::Graphics::Impl::CreateTexture(const std::string & file_name)
{
	return this->LoadTexture(Texture::Load(this->device_context_, file_name));
}

const unsigned int Seed::Graphics::Impl::CreatePlane(const unsigned int & div_x, const unsigned int & div_y, const DirectX::XMFLOAT2 & size)
{
	return this->LoadGeometry(Geometry::Plane(this->device_context_, div_x, div_y, size));
}

const unsigned int Seed::Graphics::Impl::CreateBox(const DirectX::XMFLOAT3 & size)
{
	return this->LoadGeometry(Geometry::Box(this->device_context_, size));
}

const unsigned int Seed::Graphics::Impl::CreateSphere(const float & diameter, const unsigned int & tessellation)
{
	return this->LoadGeometry(Geometry::Sphere(this->device_context_, diameter, tessellation));
}

const unsigned int Seed::Graphics::Impl::CreateGeoSphere(const float & diameter, const unsigned int & tessellation)
{
	return this->LoadGeometry(Geometry::GeoSphere(this->device_context_, diameter, tessellation));
}

const unsigned int Seed::Graphics::Impl::CreateCapsule(const DirectX::XMFLOAT3 & p1, const DirectX::XMFLOAT3 & p2, const float & diameter, const unsigned int & tessellation)
{
	return this->LoadGeometry(Geometry::Capsule(this->device_context_, p1, p2, diameter, tessellation));
}

const DirectX::Vector2 Seed::Graphics::Impl::GetTextureSize(const unsigned int & key)
{
	auto & texture = this->texture_pool_.Get(key);

	return DirectX::Vector2(texture->width(), texture->height());
}

void Seed::Graphics::Impl::CCW(void)
{
	this->device_context_->RSSetState(this->ccw_.Get());
}

void Seed::Graphics::Impl::CW(void)
{
	this->device_context_->RSSetState(this->cw_.Get());
}

void Seed::Graphics::Impl::CullNone(void)
{
	this->device_context_->RSSetState(this->cull_none_.Get());
}

void Seed::Graphics::Impl::UnloadViewPort(const unsigned int & key)
{
	this->view_port_pool_.Unload(key);
}

void Seed::Graphics::Impl::UnloadGeometry(const unsigned int & key)
{
	this->geometry_pool_.Unload(key);
}

void Seed::Graphics::Impl::UnloadTexture(const unsigned int & key)
{
	this->texture_pool_.Unload(key);
}

void Seed::Graphics::Impl::UnloadRenderTarget(const unsigned int & key)
{
	this->render_target_pool_.Unload(key);
}

void Seed::Graphics::Impl::UnloadDepthStencil(const unsigned int & key)
{
	this->depth_stencil_pool_.Unload(key);
}

void Seed::Graphics::Impl::UnloadShader(const unsigned int & key)
{
	this->shader_pool_.Unload(key);
}

void Seed::Graphics::Impl::EnableWireFrame(const bool & enable)
{
	if (enable)
	{
		this->device_context_->RSSetState(this->wire_frame_.Get());
	}
	else
	{
		this->device_context_->RSSetState(this->ccw_.Get());
	}
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

	if (depth_stencil == -1)
		this->device_context_->OMSetRenderTargets(static_cast<unsigned int>(rtvs_.size()), rtvs_.data(), nullptr);
	else
	{
		ID3D11DepthStencilView * dsv = this->depth_stencil_pool_.Get(depth_stencil)->GetDSV();
		this->device_context_->OMSetRenderTargets(static_cast<unsigned int>(rtvs_.size()), rtvs_.data(), dsv);
	}

}

void Seed::Graphics::Impl::SetShader(const unsigned int & shader, void * constant_buffer)
{
	this->shader_pool_.Get(shader)->Setup(constant_buffer);
}

void Seed::Graphics::Impl::UpdateMainConstantBuffer(void)
{
	this->device_context_->UpdateSubresource(this->main_buffer_.Get(), 0, nullptr, &this->main_cb_, 0, 0);
}

void Seed::Graphics::Impl::UpdateModelConstantBuffer(void)
{
	this->device_context_->UpdateSubresource(this->model_buffer_.Get(), 0, nullptr, &this->model_cb_, 0, 0);
}

void Seed::Graphics::Impl::Draw(const unsigned int & key)
{
	this->geometry_pool_.Get(key)->Draw();
}

void Seed::Graphics::Impl::DrawScreen(const std::vector<unsigned int>& render_targets)
{
	for (int n = 0; n < render_targets.size(); ++n)
	{
		auto srv = this->render_target_pool_.Get(render_targets[n])->GetSRV();
		this->device_context_->VSSetShaderResources(n, 1, &srv);
		this->device_context_->GSSetShaderResources(n, 1, &srv);
		this->device_context_->HSSetShaderResources(n, 1, &srv);
		this->device_context_->DSSetShaderResources(n, 1, &srv);
		this->device_context_->PSSetShaderResources(n, 1, &srv);
	}

	this->device_context_->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
	this->device_context_->Draw(4, 0);
}

void Seed::Graphics::Impl::DrawTexture(const unsigned int & texture_id)
{
	auto srv = this->texture_pool_.Get(texture_id)->GetSRV();
	this->device_context_->PSSetShaderResources(0, 1, &srv);
	this->device_context_->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
	this->device_context_->Draw(4, 0);
}

void Seed::Graphics::Impl::SetWorld(const DirectX::XMMATRIX & world)
{
	this->model_cb_.world_ = world;
}

void Seed::Graphics::Impl::SetView(const DirectX::XMMATRIX & view)
{
	this->main_cb_.view_ = view;
}

void Seed::Graphics::Impl::SetProjection(const DirectX::XMMATRIX & projection)
{
	this->main_cb_.projection_ = projection;
}

void Seed::Graphics::Impl::SetEye(const DirectX::Vector3 & eye)
{
	this->main_cb_.eye_ = { eye.x, eye.y, eye.z };
}

void Seed::Graphics::Impl::SetLightView(const DirectX::XMMATRIX & light_view)
{
	this->main_cb_.light_view_ = light_view;
}

void Seed::Graphics::Impl::SetDirectionLight(const DirectX::Vector3 & dir_light)
{
	this->main_cb_.dir_light_ = { dir_light.x, -dir_light.y, -dir_light.z };
	DirectX::Vector3 x_only(1, 0, 0);
	
	this->main_cb_.light_view_ = DirectX::Matrix::CreateLookAt(dir_light, x_only * dir_light + DirectX::Vector3(-1, 0, 0), DirectX::Vector3(0, 1, 0));
}

void Seed::Graphics::Impl::SetDiffuse(const DirectX::Vector4 & color)
{
	this->model_cb_.color_ = color;
}

void Seed::Graphics::Impl::SetRTSRV(const std::vector<unsigned int>& render_targets)
{
	for (int n = 0; n < render_targets.size(); ++n)
	{
		auto srv = this->render_target_pool_.Get(render_targets[n])->GetSRV();
		this->device_context_->VSSetShaderResources(n, 1, &srv);
		this->device_context_->GSSetShaderResources(n, 1, &srv);
		this->device_context_->HSSetShaderResources(n, 1, &srv);
		this->device_context_->DSSetShaderResources(n, 1, &srv);
		this->device_context_->PSSetShaderResources(n, 1, &srv);
	}
}

void Seed::Graphics::Impl::SetBlend(const bool & blend)
{
	if(blend)
		this->device_context_->OMSetBlendState(this->blend_state_.Get(), nullptr, 0xffffffff);
	else
		this->device_context_->OMSetBlendState(nullptr, nullptr, 0xffffffff);
}

void Seed::Graphics::Impl::SetScreenColor(const DirectX::Vector4 & color)
{
	this->model_cb_.screen_ = color;
}
