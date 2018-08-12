#include "geometry.h"

#include <DirectXPackedVector.h>

#include "buffer.h"

using namespace DirectX;

class Seed::Geometry::Impl
{
public:
	Impl(const DeviceContext & device_context)
		: device_context_(device_context)
		, topology_(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST)
	{}

private:
	const DeviceContext & device_context_;

private:
	std::unique_ptr<Buffer> index_buffer_;
	std::unique_ptr<Buffer> vertex_buffer_;
	D3D11_PRIMITIVE_TOPOLOGY topology_;

public:
	void set_topology(const D3D11_PRIMITIVE_TOPOLOGY & topology);

public:
	void Initialize(const IndexCollection & indices, const VertexCollection & vertices);

public:
	void Draw(void) const;
};

Seed::Geometry::~Geometry(void)
{
}

void ReverseWinding(Seed::IndexCollection & indices, Seed::VertexCollection & vertices)
{
	for (auto it = indices.begin(); it != indices.end(); it += 3)
	{
		std::swap(*it, *(it + 2));
	}

	for (auto it = vertices.begin(); it != vertices.end(); ++it)
	{
		it->uv_.x = (1.f - it->uv_.x);
	}
}

unsigned int Reverse(unsigned int x, unsigned int y, unsigned int div_x)
{
	return x % (div_x + 1) + y * (div_x + 1);
}

unsigned int v2to1(unsigned int x, unsigned int y, unsigned int div_x)
{
	return x % (div_x + 1) + y * (div_x + 1);
}

std::unique_ptr<Seed::Geometry> Seed::Geometry::Plane(const DeviceContext & device_context, const unsigned int & div_x, const unsigned int & div_y, const DirectX::XMFLOAT2 & size)
{
	std::unique_ptr<Geometry> geometry(new Geometry(device_context));
	
	IndexCollection indices;
	VertexCollection vertices;

	vertices.clear();
	indices.clear();

	float w = size.x / div_x, h = size.y / div_y;

	for (unsigned int n = 0; n < div_y + 1; ++n)
	{
		for (unsigned int i = 0; i < div_x + 1; ++i)
		{
			vertices.emplace_back(DirectX::XMFLOAT3(-w * div_x * 0.5f + i * w, 0, -h * div_y * 0.5f + n * h), DirectX::XMFLOAT3(0, 0, 0), DirectX::XMFLOAT2(0, 0));
		}
	}

	for (unsigned int n = 0; n < div_y; ++n)
	{
		for (unsigned int i = 0; i < div_x; ++i)
		{
			indices.emplace_back(v2to1(i + 0, n + 0, div_x));
			indices.emplace_back(v2to1(i + 0, n + 0, div_x));
			indices.emplace_back(v2to1(i + 1, n + 0, div_x));
			indices.emplace_back(v2to1(i + 0, n + 1, div_x));
			indices.emplace_back(v2to1(i + 1, n + 1, div_x));
			indices.emplace_back(v2to1(i + 1, n + 1, div_x));
		}
	}

	geometry->impl_->Initialize(indices, vertices);

	geometry->impl_->set_topology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	return geometry;
}

std::unique_ptr<Seed::Geometry> Seed::Geometry::Box(const DeviceContext& device_context, const XMFLOAT3 & size)
{
	std::unique_ptr<Geometry> geometry(new Geometry(device_context));

	IndexCollection indices;
	VertexCollection vertices;

	vertices.clear();
	indices.clear();

	// A box has six faces, each one pointing in a different direction.
	const int FaceCount = 6;

	static const XMVECTORF32 faceNormals[FaceCount] =
	{
		{ { { 0,  0,  1, 0 } } },
	{ { { 0,  0, -1, 0 } } },
	{ { { 1,  0,  0, 0 } } },
	{ { { -1,  0,  0, 0 } } },
	{ { { 0,  1,  0, 0 } } },
	{ { { 0, -1,  0, 0 } } },
	};

	static const XMVECTORF32 textureCoordinates[4] =
	{
		{ { { 1, 0, 0, 0 } } },
	{ { { 1, 1, 0, 0 } } },
	{ { { 0, 1, 0, 0 } } },
	{ { { 0, 0, 0, 0 } } },
	};

	XMVECTOR tsize = XMLoadFloat3(&size);
	tsize = XMVectorDivide(tsize, g_XMTwo);

	// Create each face in turn.
	for (int i = 0; i < FaceCount; i++)
	{
		XMVECTOR normal = faceNormals[i];

		// Get two vectors perpendicular both to the face normal and to each other.
		XMVECTOR basis = (i >= 4) ? g_XMIdentityR2 : g_XMIdentityR1;

		XMVECTOR side1 = XMVector3Cross(normal, basis);
		XMVECTOR side2 = XMVector3Cross(normal, side1);

		// Six indices (two triangles) per face.
		unsigned int vbase = static_cast<unsigned int>(vertices.size());
		indices.emplace_back(vbase + 0);
		indices.emplace_back(vbase + 1);
		indices.emplace_back(vbase + 2);

		indices.emplace_back(vbase + 0);
		indices.emplace_back(vbase + 2);
		indices.emplace_back(vbase + 3);

		// Four vertices per face.
		// (normal - side1 - side2) * tsize // normal // t0
		vertices.emplace_back(Vertex(XMVectorMultiply(XMVectorSubtract(XMVectorSubtract(normal, side1), side2), tsize), normal, textureCoordinates[0]));

		// (normal - side1 + side2) * tsize // normal // t1
		vertices.emplace_back(Vertex(XMVectorMultiply(XMVectorAdd(XMVectorSubtract(normal, side1), side2), tsize), normal, textureCoordinates[1]));

		// (normal + side1 + side2) * tsize // normal // t2
		vertices.emplace_back(Vertex(XMVectorMultiply(XMVectorAdd(normal, XMVectorAdd(side1, side2)), tsize), normal, textureCoordinates[2]));

		// (normal + side1 - side2) * tsize // normal // t3
		vertices.emplace_back(Vertex(XMVectorMultiply(XMVectorSubtract(XMVectorAdd(normal, side1), side2), tsize), normal, textureCoordinates[3]));
	}

	ReverseWinding(indices, vertices);

	geometry->impl_->Initialize(indices, vertices);

	geometry->impl_->set_topology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	return geometry;
}

std::unique_ptr<Seed::Geometry> Seed::Geometry::Sphere(const DeviceContext& device_context, const float & diameter, const unsigned int & tessellation)
{
	std::unique_ptr<Geometry> geometry(new Geometry(device_context));

	IndexCollection indices;
	VertexCollection vertices;

	vertices.clear();
	indices.clear();

	if (tessellation < 3)
		throw std::out_of_range("tesselation parameter out of range");

	unsigned int verticalSegments = tessellation;
	unsigned int horizontalSegments = tessellation * 2;

	float radius = diameter / 2;

	// Create rings of vertices at progressively higher latitudes.
	for (unsigned int i = 0; i <= verticalSegments; i++)
	{
		float v = 1 - float(i) / verticalSegments;

		float latitude = (i * XM_PI / verticalSegments) - XM_PIDIV2;
		float dy, dxz;

		XMScalarSinCos(&dy, &dxz, latitude);

		// Create a single ring of vertices at this latitude.
		for (unsigned int j = 0; j <= horizontalSegments; j++)
		{
			float u = float(j) / horizontalSegments;

			float longitude = j * XM_2PI / horizontalSegments;
			float dx, dz;

			XMScalarSinCos(&dx, &dz, longitude);

			dx *= dxz;
			dz *= dxz;

			XMVECTOR normal = XMVectorSet(dx, dy, dz, 0);
			XMVECTOR textureCoordinate = XMVectorSet(u, v, 0, 0);

			vertices.push_back(Vertex(XMVectorScale(normal, radius), normal, textureCoordinate));
		}
	}

	// Fill the index buffer with triangles joining each pair of latitude rings.
	unsigned int stride = horizontalSegments + 1;

	for (unsigned int i = 0; i < verticalSegments; i++)
	{
		for (unsigned int j = 0; j <= horizontalSegments; j++)
		{
			unsigned int nextI = i + 1;
			unsigned int nextJ = (j + 1) % stride;

			indices.emplace_back(i * stride + j);
			indices.emplace_back(nextI * stride + j);
			indices.emplace_back(i * stride + nextJ);

			indices.emplace_back(i * stride + nextJ);
			indices.emplace_back(nextI * stride + j);
			indices.emplace_back(nextI * stride + nextJ);
		}
	}

	ReverseWinding(indices, vertices);

	geometry->impl_->Initialize(indices, vertices);

	geometry->impl_->set_topology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	return geometry;
}

void Seed::Geometry::Draw(void) const
{
	this->impl_->Draw();
}

Seed::Geometry::Geometry(const DeviceContext& device_context) noexcept(false)
	: impl_(std::make_unique<Impl>(device_context))
{
}

void Seed::Geometry::Impl::set_topology(const D3D11_PRIMITIVE_TOPOLOGY & topology)
{
	this->topology_ = topology;
}

void Seed::Geometry::Impl::Initialize(const IndexCollection & indices, const VertexCollection & vertices)
{
	this->index_buffer_ = Buffer::IndexBuffer(this->device_context_, indices);
	this->vertex_buffer_ = Buffer::VertexBuffer(this->device_context_, vertices);
}

void Seed::Geometry::Impl::Draw(void) const
{
	this->device_context_->IASetPrimitiveTopology(this->topology_);

	this->vertex_buffer_->Setup();
	this->index_buffer_->Setup();
}