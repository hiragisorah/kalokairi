#include "buffer.h"

class Seed::Buffer::Impl
{
	enum class PRIVATE_ENUM
	{
		INDEX,
		VERTEX
	};

public:
	Impl(const DeviceContext & device_context)
		: device_context_(device_context)
		, stride_(0)
		, cnt_(0)
		, type_(PRIVATE_ENUM::VERTEX)
	{}

private:
	const DeviceContext & device_context_;

private:
	PRIVATE_ENUM type_;
	Microsoft::WRL::ComPtr<ID3D11Buffer> data_;
	size_t stride_;
	size_t cnt_;

public:
	void Initialize(const IndexCollection & indices);
	void Initialize(const VertexCollection & vertices);

public:
	void Setup(void) const;
};

Seed::Buffer::~Buffer(void)
{
}

std::unique_ptr<Seed::Buffer> Seed::Buffer::IndexBuffer(const DeviceContext& device_context, const IndexCollection & indices)
{
	std::unique_ptr<Buffer> buffer(new Buffer(device_context));

	buffer->impl_->Initialize(indices);

	return buffer;
}

std::unique_ptr<Seed::Buffer> Seed::Buffer::VertexBuffer(const DeviceContext& device_context, const VertexCollection & vertices)
{
	std::unique_ptr<Buffer> buffer(new Buffer(device_context));

	buffer->impl_->Initialize(vertices);

	return buffer;
}

void Seed::Buffer::Setup(void) const
{
	this->impl_->Setup();
}

Seed::Buffer::Buffer(const DeviceContext& device_context) noexcept(false)
	: impl_(std::make_unique<Impl>(device_context))
{

}

void Seed::Buffer::Impl::Initialize(const IndexCollection & indices)
{
	this->type_ = PRIVATE_ENUM::VERTEX;

	this->stride_ = sizeof(Vertex);
	this->cnt_ = indices.size();

	D3D11_BUFFER_DESC bd = {};
	bd.ByteWidth = this->cnt_ * this->stride_;
	bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
	bd.Usage = D3D11_USAGE_DEFAULT;

	D3D11_SUBRESOURCE_DATA sd = {};
	sd.pSysMem = indices.data();

	Microsoft::WRL::ComPtr<ID3D11Device> device;
	this->device_context_->GetDevice(device.GetAddressOf());

	device->CreateBuffer(&bd, &sd, this->data_.GetAddressOf());
}

void Seed::Buffer::Impl::Initialize(const VertexCollection & vertices)
{
	this->type_ = PRIVATE_ENUM::INDEX;

	this->stride_ = sizeof(Vertex);
	this->cnt_ = vertices.size();

	D3D11_BUFFER_DESC bd = {};
	bd.ByteWidth = this->cnt_ * this->stride_;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.Usage = D3D11_USAGE_DEFAULT;

	D3D11_SUBRESOURCE_DATA sd = {};
	sd.pSysMem = vertices.data();

	Microsoft::WRL::ComPtr<ID3D11Device> device;
	this->device_context_->GetDevice(device.GetAddressOf());

	device->CreateBuffer(&bd, &sd, this->data_.GetAddressOf());
}

void Seed::Buffer::Impl::Setup(void) const
{
	if (this->type_ == PRIVATE_ENUM::INDEX)
	{
		this->device_context_->IASetIndexBuffer(this->data_.Get(), DXGI_FORMAT_R32_UINT, 0);
		this->device_context_->DrawIndexed(this->cnt_, 0, 0);
	}
	else
	{
		UINT offset = 0;
		this->device_context_->IASetVertexBuffers(0, 1, this->data_.GetAddressOf(), &this->stride_, &offset);
	}
}
