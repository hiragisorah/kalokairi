#include "geometry.h"

#include <DirectXPackedVector.h>
#include <map>
#include <algorithm>
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
			vertices.emplace_back(DirectX::XMFLOAT3(-w * div_x * 0.5f + i * w, 0, -h * div_y * 0.5f + n * h), DirectX::XMFLOAT3(0, 1, 0), DirectX::XMFLOAT2(0, 0));
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

	static const XMVECTORF32 uv_s[4] =
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
		vertices.emplace_back(Vertex(XMVectorMultiply(XMVectorSubtract(XMVectorSubtract(normal, side1), side2), tsize), normal, uv_s[0]));

		// (normal - side1 + side2) * tsize // normal // t1
		vertices.emplace_back(Vertex(XMVectorMultiply(XMVectorAdd(XMVectorSubtract(normal, side1), side2), tsize), normal, uv_s[1]));

		// (normal + side1 + side2) * tsize // normal // t2
		vertices.emplace_back(Vertex(XMVectorMultiply(XMVectorAdd(normal, XMVectorAdd(side1, side2)), tsize), normal, uv_s[2]));

		// (normal + side1 - side2) * tsize // normal // t3
		vertices.emplace_back(Vertex(XMVectorMultiply(XMVectorSubtract(XMVectorAdd(normal, side1), side2), tsize), normal, uv_s[3]));
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
		throw std::out_of_range("tessellation parameter out of range");

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
			XMVECTOR uv_ = XMVectorSet(u, v, 0, 0);

			vertices.push_back(Vertex(XMVectorScale(normal, radius), normal, uv_));
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

#undef max
#undef min

std::unique_ptr<Seed::Geometry> Seed::Geometry::GeoSphere(const DeviceContext& device_context, const float & diameter, const unsigned int & tessellation)
{
	std::unique_ptr<Geometry> geometry(new Geometry(device_context));

	IndexCollection indices;
	VertexCollection vertices;

	vertices.clear();
	indices.clear();

	// An undirected edge between two vertices, represented by a pair of indexes into a vertex array.
	// Becuse this edge is undirected, (a,b) is the same as (b,a).
	typedef std::pair<unsigned int, unsigned int> UndirectedEdge;

	// Makes an undirected edge. Rather than overloading comparison operators to give us the (a,b)==(b,a) property,
	// we'll just ensure that the larger of the two goes first. This'll simplify things greatly.
	auto makeUndirectedEdge = [](unsigned int a, unsigned int b)
	{
		return std::make_pair(std::max(a, b), std::min(a, b));
	};

	// Key: an edge
	// Value: the index of the vertex which lies midway between the two vertices pointed to by the key value
	// This map is used to avoid duplicating vertices when subdividing triangles along edges.
	typedef std::map<UndirectedEdge, unsigned int> EdgeSubdivisionMap;


	static const XMFLOAT3 OctahedronVertices[] =
	{
		// when looking down the negative z-axis (into the screen)
		XMFLOAT3(0,  1,  0), // 0 top
		XMFLOAT3(0,  0, -1), // 1 front
		XMFLOAT3(1,  0,  0), // 2 right
		XMFLOAT3(0,  0,  1), // 3 back
		XMFLOAT3(-1,  0,  0), // 4 left
		XMFLOAT3(0, -1,  0), // 5 bottom
	};
	static const unsigned int OctahedronIndices[] =
	{
		0, 1, 2, // top front-right face
		0, 2, 3, // top back-right face
		0, 3, 4, // top back-left face
		0, 4, 1, // top front-left face
		5, 1, 4, // bottom front-left face
		5, 4, 3, // bottom back-left face
		5, 3, 2, // bottom back-right face
		5, 2, 1, // bottom front-right face
	};

	const float radius = diameter / 2.0f;

	// Start with an octahedron; copy the data into the vertex/index collection.

	std::vector<XMFLOAT3> vertexPositions(std::begin(OctahedronVertices), std::end(OctahedronVertices));

	indices.insert(indices.begin(), std::begin(OctahedronIndices), std::end(OctahedronIndices));

	// We know these values by looking at the above index list for the octahedron. Despite the subdivisions that are
	// about to go on, these values aren't ever going to change because the vertices don't move around in the array.
	// We'll need these values later on to fix the singularities that show up at the poles.
	const unsigned int northPoleIndex = 0;
	const unsigned int southPoleIndex = 5;

	for (unsigned int iSubdivision = 0; iSubdivision < tessellation; ++iSubdivision)
	{
		assert(indices.size() % 3 == 0); // sanity

										 // We use this to keep track of which edges have already been subdivided.
		EdgeSubdivisionMap subdividedEdges;

		// The new index collection after subdivision.
		IndexCollection newIndices;

		const unsigned int triangleCount = static_cast<unsigned int>(indices.size()) / 3;
		for (unsigned int iTriangle = 0; iTriangle < triangleCount; ++iTriangle)
		{
			// For each edge on this triangle, create a new vertex in the middle of that edge.
			// The winding order of the triangles we output aret the same as the winding order of the inputs.

			// Indices of the vertices making up this triangle
			unsigned int iv0 = indices[iTriangle * 3 + 0];
			unsigned int iv1 = indices[iTriangle * 3 + 1];
			unsigned int iv2 = indices[iTriangle * 3 + 2];

			// Get the new vertices
			XMFLOAT3 v01; // vertex on the midpoint of v0 and v1
			XMFLOAT3 v12; // ditto v1 and v2
			XMFLOAT3 v20; // ditto v2 and v0
			unsigned int iv01; // index of v01
			unsigned int iv12; // index of v12
			unsigned int iv20; // index of v20

							   // Function that, when given the index of two vertices, creates a new vertex at the midpoint of those vertices.
			auto divideEdge = [&](unsigned int i0, unsigned int i1, XMFLOAT3& outVertex, unsigned int& outIndex)
			{
				const UndirectedEdge edge = makeUndirectedEdge(i0, i1);

				// Check to see if we've already generated this vertex
				auto it = subdividedEdges.find(edge);
				if (it != subdividedEdges.end())
				{
					// We've already generated this vertex before
					outIndex = it->second; // the index of this vertex
					outVertex = vertexPositions[outIndex]; // and the vertex itself
				}
				else
				{
					// Haven't generated this vertex before: so add it now

					// outVertex = (vertices[i0] + vertices[i1]) / 2
					XMStoreFloat3(
						&outVertex,
						XMVectorScale(
							XMVectorAdd(XMLoadFloat3(&vertexPositions[i0]), XMLoadFloat3(&vertexPositions[i1])),
							0.5f
						)
					);

					outIndex = static_cast<unsigned int>(vertexPositions.size());
					vertexPositions.push_back(outVertex);

					// Now add it to the map.
					auto entry = std::make_pair(edge, outIndex);
					subdividedEdges.insert(entry);
				}
			};

			// Add/get new vertices and their indices
			divideEdge(iv0, iv1, v01, iv01);
			divideEdge(iv1, iv2, v12, iv12);
			divideEdge(iv0, iv2, v20, iv20);

			// Add the new indices. We have four new triangles from our original one:
			//        v0
			//        o
			//       /a\
						            //  v20 o---o v01
//     /b\c/d\
            // v2 o---o---o v1
//       v12
			const unsigned int indicesToAdd[] =
			{
				iv0, iv01, iv20, // a
				iv20, iv12,  iv2, // b
				iv20, iv01, iv12, // c
				iv01,  iv1, iv12, // d
			};
			newIndices.insert(newIndices.end(), std::begin(indicesToAdd), std::end(indicesToAdd));
		}

		indices = std::move(newIndices);
	}

	// Now that we've completed subdivision, fill in the final vertex collection
	vertices.reserve(vertexPositions.size());
	for (auto it = vertexPositions.begin(); it != vertexPositions.end(); ++it)
	{
		auto vertexValue = *it;

		auto normal = XMVector3Normalize(XMLoadFloat3(&vertexValue));
		auto pos = XMVectorScale(normal, radius);

		XMFLOAT3 normalFloat3;
		XMStoreFloat3(&normalFloat3, normal);

		// calculate texture coordinates for this vertex
		float longitude = atan2(normalFloat3.x, -normalFloat3.z);
		float latitude = acos(normalFloat3.y);

		float u = longitude / XM_2PI + 0.5f;
		float v = latitude / XM_PI;

		auto texcoord = XMVectorSet(1.0f - u, v, 0.0f, 0.0f);
		vertices.push_back(Vertex(pos, normal, texcoord));
	}

	// There are a couple of fixes to do. One is a texture coordinate wraparound fixup. At some point, there will be
	// a set of triangles somewhere in the mesh with texture coordinates such that the wraparound across 0.0/1.0
	// occurs across that triangle. Eg. when the left hand side of the triangle has a U coordinate of 0.98 and the
	// right hand side has a U coordinate of 0.0. The intent is that such a triangle should render with a U of 0.98 to
	// 1.0, not 0.98 to 0.0. If we don't do this fixup, there will be a visible seam across one side of the sphere.
	// 
	// Luckily this is relatively easy to fix. There is a straight edge which runs down the prime meridian of the
	// completed sphere. If you imagine the vertices along that edge, they circumscribe a semicircular arc starting at
	// y=1 and ending at y=-1, and sweeping across the range of z=0 to z=1. x stays zero. It's along this edge that we
	// need to duplicate our vertices - and provide the correct texture coordinates.
	unsigned int preFixupVertexCount = static_cast<unsigned int>(vertices.size());
	for (unsigned int i = 0; i < preFixupVertexCount; ++i)
	{
		// This vertex is on the prime meridian if position.x and texcoord.u are both zero (allowing for small epsilon).
		bool isOnPrimeMeridian = XMVector2NearEqual(
			XMVectorSet(vertices[i].position_.x, vertices[i].uv_.x, 0.0f, 0.0f),
			XMVectorZero(),
			XMVectorSplatEpsilon());

		if (isOnPrimeMeridian)
		{
			unsigned int newIndex = static_cast<unsigned int>(vertices.size()); // the index of this vertex that we're about to add

											   // copy this vertex, correct the texture coordinate, and add the vertex
			Vertex v = vertices[i];
			v.uv_.x = 1.0f;
			vertices.push_back(v);

			// Now find all the triangles which contain this vertex and update them if necessary
			for (unsigned int j = 0; j < indices.size(); j += 3)
			{
				unsigned int* triIndex0 = &indices[j + 0];
				unsigned int* triIndex1 = &indices[j + 1];
				unsigned int* triIndex2 = &indices[j + 2];

				if (*triIndex0 == i)
				{
					// nothing; just keep going
				}
				else if (*triIndex1 == i)
				{
					std::swap(triIndex0, triIndex1); // swap the pointers (not the values)
				}
				else if (*triIndex2 == i)
				{
					std::swap(triIndex0, triIndex2); // swap the pointers (not the values)
				}
				else
				{
					// this triangle doesn't use the vertex we're interested in
					continue;
				}

				// If we got to this point then triIndex0 is the pointer to the index to the vertex we're looking at
				assert(*triIndex0 == i);
				assert(*triIndex1 != i && *triIndex2 != i); // assume no degenerate triangles

				const Vertex& v0 = vertices[*triIndex0];
				const Vertex& v1 = vertices[*triIndex1];
				const Vertex& v2 = vertices[*triIndex2];

				// check the other two vertices to see if we might need to fix this triangle

				if (abs(v0.uv_.x - v1.uv_.x) > 0.5f ||
					abs(v0.uv_.x - v2.uv_.x) > 0.5f)
				{
					// yep; replace the specified index to point to the new, corrected vertex
					*triIndex0 = static_cast<unsigned int>(newIndex);
				}
			}
		}
	}

	// And one last fix we need to do: the poles. A common use-case of a sphere mesh is to map a rectangular texture onto
	// it. If that happens, then the poles become singularities which map the entire top and bottom rows of the texture
	// onto a single point. In general there's no real way to do that right. But to match the behavior of non-geodesic
	// spheres, we need to duplicate the pole vertex for every triangle that uses it. This will introduce seams near the
	// poles, but reduce stretching.
	auto fixPole = [&](unsigned int poleIndex)
	{
		auto poleVertex = vertices[poleIndex];
		bool overwrittenPoleVertex = false; // overwriting the original pole vertex saves us one vertex

		for (unsigned int i = 0; i < indices.size(); i += 3)
		{
			// These pointers point to the three indices which make up this triangle. pPoleIndex is the pointer to the
			// entry in the index array which represents the pole index, and the other two pointers point to the other
			// two indices making up this triangle.
			unsigned int* pPoleIndex;
			unsigned int* pOtherIndex0;
			unsigned int* pOtherIndex1;
			if (indices[i + 0] == poleIndex)
			{
				pPoleIndex = &indices[i + 0];
				pOtherIndex0 = &indices[i + 1];
				pOtherIndex1 = &indices[i + 2];
			}
			else if (indices[i + 1] == poleIndex)
			{
				pPoleIndex = &indices[i + 1];
				pOtherIndex0 = &indices[i + 2];
				pOtherIndex1 = &indices[i + 0];
			}
			else if (indices[i + 2] == poleIndex)
			{
				pPoleIndex = &indices[i + 2];
				pOtherIndex0 = &indices[i + 0];
				pOtherIndex1 = &indices[i + 1];
			}
			else
			{
				continue;
			}

			const auto& otherVertex0 = vertices[*pOtherIndex0];
			const auto& otherVertex1 = vertices[*pOtherIndex1];

			// Calculate the texcoords for the new pole vertex, add it to the vertices and update the index
			Vertex newPoleVertex = poleVertex;
			newPoleVertex.uv_.x = (otherVertex0.uv_.x + otherVertex1.uv_.x) / 2;
			newPoleVertex.uv_.y = poleVertex.uv_.y;

			if (!overwrittenPoleVertex)
			{
				vertices[poleIndex] = newPoleVertex;
				overwrittenPoleVertex = true;
			}
			else
			{
				*pPoleIndex = static_cast<unsigned int>(vertices.size());
				vertices.push_back(newPoleVertex);
			}
		}
	};

	fixPole(northPoleIndex);
	fixPole(southPoleIndex);

	ReverseWinding(indices, vertices);

	geometry->impl_->Initialize(indices, vertices);

	geometry->impl_->set_topology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	return geometry;
}

std::unique_ptr<Seed::Geometry> Seed::Geometry::Capsule(const DeviceContext & device_context, const DirectX::XMFLOAT3 & p1, const DirectX::XMFLOAT3 & p2, const float & diameter, const unsigned int & tessellation)
{
	std::unique_ptr<Geometry> geometry(new Geometry(device_context));

	IndexCollection indices;
	VertexCollection vertices;

	vertices.clear();
	indices.clear();

	if (tessellation < 3)
		throw std::out_of_range("tessellation parameter out of range");

	unsigned int verticalSegments = tessellation;
	unsigned int horizontalSegments = tessellation * 2;

	float radius = diameter / 2;

	for (unsigned int i = 0; i <= verticalSegments; i++)
	{
		float v = 1 - (float)i / verticalSegments;

		float latitude = (i * XM_PI / verticalSegments) - XM_PIDIV2;
		float dy, dxz;

		XMScalarSinCos(&dy, &dxz, latitude);

		DirectX::XMFLOAT3 CenterPos = p1;
		if (i >= (verticalSegments / 2)) {
			CenterPos = p2;
		}

		float SphereTotalFront = diameter * XM_PI / 2.0f;
		float SylinderTotalFront = abs(p1.y - p2.y);
		float SphereRate = SphereTotalFront / (SphereTotalFront + SylinderTotalFront) / 2.0f;

		if (v <= 0.5f) {
			v *= SphereRate;
		}
		else {
			v = 1.0f - ((1.0f - v) * SphereRate);
		}


		for (unsigned int j = 0; j <= horizontalSegments; j++)
		{
			float u = (float)j / horizontalSegments;

			float longitude = j * XM_2PI / horizontalSegments;
			float dx, dz;

			XMScalarSinCos(&dx, &dz, longitude);

			dx *= dxz;
			dz *= dxz;

			DirectX::XMFLOAT3 normal = { dx, dy, dz };
			DirectX::XMFLOAT3 position = { normal.x * radius + CenterPos.x, normal.y * radius + CenterPos.y, normal.z * radius + CenterPos.z };
			DirectX::XMFLOAT2 uv = { u,v };
			
			vertices.push_back(Vertex(position, normal, uv));
		}
	}
	unsigned int stride = horizontalSegments + 1;
	for (unsigned int i = 0; i < verticalSegments; i++)
	{
		for (unsigned int j = 0; j <= horizontalSegments; j++)
		{
			unsigned int nextI = i + 1;
			unsigned int nextJ = (j + 1) % stride;

			indices.push_back((unsigned int)(i * stride + j));
			indices.push_back((unsigned int)(nextI * stride + j));
			indices.push_back((unsigned int)(i * stride + nextJ));

			indices.push_back((unsigned int)(i * stride + nextJ));
			indices.push_back((unsigned int)(nextI * stride + j));
			indices.push_back((unsigned int)(nextI * stride + nextJ));
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