#include "view-port.h"

using DSV = Microsoft::WRL::ComPtr<ID3D11DepthStencilView>;

class Seed::ViewPort::Impl
{
public:
	Impl(const DeviceContext & device_context)
		: device_context_(device_context)
		, view_port_({})
	{}

private:
	const DeviceContext & device_context_;

private:
	D3D11_VIEWPORT view_port_;

public:
	void Initialize(const unsigned int & width, const unsigned int & height);

public:
	void Setup(void) const;
};

Seed::ViewPort::~ViewPort(void)
{
}

std::unique_ptr<Seed::ViewPort> Seed::ViewPort::Create(const DeviceContext & device_context, const unsigned int & width, const unsigned int & height)
{
	std::unique_ptr<ViewPort> view_port(new ViewPort(device_context));

	view_port->impl_->Initialize(width, height);

	return view_port;
}

void Seed::ViewPort::Setup(void) const
{
	this->impl_->Setup();
}

Seed::ViewPort::ViewPort(const DeviceContext& device_context) noexcept(false)
	: impl_(std::make_unique<Impl>(device_context))
{
}

void Seed::ViewPort::Impl::Initialize(const unsigned int & width, const unsigned int & height)
{
	auto & vp = this->view_port_;

	vp.Width = static_cast<float>(width);
	vp.Height = static_cast<float>(height);
	vp.MinDepth = 0.f;
	vp.MaxDepth = 1.f;
	vp.TopLeftX = 0.f;
	vp.TopLeftY = 0.f;
}

void Seed::ViewPort::Impl::Setup(void) const
{
	this->device_context_->RSSetViewports(1, &this->view_port_);
}