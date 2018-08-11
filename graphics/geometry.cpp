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
	void Initialize(const IndexCollection & indices, const VertexCollection & vertices) const;

public:
	void Draw(void) const;
};

Seed::Geometry::~Geometry(void)
{
}

std::unique_ptr<Seed::Geometry> Seed::Geometry::Box(const DeviceContext& device_context, const XMFLOAT3 & size)
{
	std::unique_ptr<Geometry> geometry(new Geometry(device_context));

	IndexCollection indices;
	VertexCollection vertices;

	geometry->impl_->Initialize(indices, vertices);

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
		size_t vbase = vertices.size();
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

	geometry->impl_->set_topology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	return geometry;
}

std::unique_ptr<Seed::Geometry> Seed::Geometry::Sphere(const DeviceContext& device_context, const float & diameter, const size_t & tessellation)
{
	std::unique_ptr<Geometry> geometry(new Geometry(device_context));

	IndexCollection indices;
	VertexCollection vertices;

	vertices.clear();
	indices.clear();

	if (tessellation < 3)
		throw std::out_of_range("tesselation parameter out of range");

	size_t verticalSegments = tessellation;
	size_t horizontalSegments = tessellation * 2;

	float radius = diameter / 2;

	// Create rings of vertices at progressively higher latitudes.
	for (size_t i = 0; i <= verticalSegments; i++)
	{
		float v = 1 - float(i) / verticalSegments;

		float latitude = (i * XM_PI / verticalSegments) - XM_PIDIV2;
		float dy, dxz;

		XMScalarSinCos(&dy, &dxz, latitude);

		// Create a single ring of vertices at this latitude.
		for (size_t j = 0; j <= horizontalSegments; j++)
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
	size_t stride = horizontalSegments + 1;

	for (size_t i = 0; i < verticalSegments; i++)
	{
		for (size_t j = 0; j <= horizontalSegments; j++)
		{
			size_t nextI = i + 1;
			size_t nextJ = (j + 1) % stride;

			indices.emplace_back(i * stride + j);
			indices.emplace_back(nextI * stride + j);
			indices.emplace_back(i * stride + nextJ);

			indices.emplace_back(i * stride + nextJ);
			indices.emplace_back(nextI * stride + j);
			indices.emplace_back(nextI * stride + nextJ);
		}
	}

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

void Seed::Geometry::Impl::Initialize(const IndexCollection & indices, const VertexCollection & vertices) const
{
	this->index_buffer_->IndexBuffer(this->device_context_, indices);
	this->vertex_buffer_->VertexBuffer(this->device_context_, vertices);
}

void Seed::Geometry::Impl::Draw(void) const
{
	this->vertex_buffer_->Setup();
	this->index_buffer_->Setup();
}