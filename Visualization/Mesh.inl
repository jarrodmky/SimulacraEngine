//===========================================================================
// Class Definitions
//===========================================================================

namespace Visualization
{

	template<typename t_VertexType>
	Mesh<t_VertexType>::Mesh()
	: m_VertexBuffer(nullptr)
	, m_IndexBuffer(nullptr)
	, m_VertexCount(0)
	, m_IndexCount(0)
	, Topology(PointList)
	{}

//---------------------------------------------------------------------------

	template<typename t_VertexType>
	Mesh<t_VertexType>::~Mesh()
	{
		Assert(m_VertexBuffer == nullptr, "Vertices still allocated!!");
		Assert(m_IndexBuffer == nullptr, "Indices still allocated!!");
	}

//---------------------------------------------------------------------------
	
	template<typename t_VertexType>
	void Mesh<t_VertexType>::Allocate(const u32 p_NumVertices, const u32 p_NumIndices)
	{
		Assert(m_VertexBuffer == nullptr, "Vertices already allocated!!");
		Assert(m_IndexBuffer == nullptr, "Indices already allocated!!");
		Assert(p_NumVertices != 0, "Invalid vertex count!");
		Assert(p_NumIndices != 0, "Invalid index count!!");
		m_VertexBuffer = std::make_unique<t_VertexType[]>(p_NumVertices);
		m_IndexBuffer = std::make_unique<u32[]>(p_NumIndices);
		m_VertexCount = p_NumVertices;
		m_IndexCount = p_NumIndices;
	}

//---------------------------------------------------------------------------

	template<typename t_VertexType>
	void Mesh<t_VertexType>::Destroy()
	{
		m_VertexBuffer.reset();
		m_IndexBuffer.reset();
		m_VertexCount = 0;
		m_IndexCount = 0;
		Topology = PointList;
	}

//---------------------------------------------------------------------------
		
	template<typename t_VertexType>
	t_VertexType& Mesh<t_VertexType>::GetVertex(const u32 p_Index) const
	{
		Assert(p_Index < m_VertexCount, "Invalid Index Number!");
		return m_VertexBuffer[p_Index];
	}

//---------------------------------------------------------------------------
		
	template<typename t_VertexType>
	u32& Mesh<t_VertexType>::GetIndex(const u32 p_Index) const
	{
		Assert(p_Index < m_IndexCount, "Invalid Index Number!");
		return m_IndexBuffer[p_Index];
	}

}