//===========================================================================
// Filename:	HelooTEXTUREWindowedApp.cpp
// Author:		Jarrod MacKay
//===========================================================================

//===========================================================================
// Includes
//===========================================================================

#include "Game.h"

using namespace Abstracts;
using namespace Mathematics;
using namespace Algorithms;


const scalar kTileSize = 0.65f;
const Vector2 kOffset(MakeVector(kTileSize * 0.5f - 3.0f, kTileSize * 0.5f - 3.0f));
Grid grid;
SearchContext<Dijkstra> context;
std::vector<u32> path;

namespace
{
	//filter
	bool IsBlocked(u32 p_Start, u32 p_End)
	{
		u32 x = grid.GetX(p_End);
		u32 y = grid.GetY(p_End);
		//TODO: decide if end is traversable
		return true;
	}

	void ShowPath()
	{
		const Graph& graph = grid.GetGraph();
		Assert(path.size() > 0, "No path set!");
		for (u32 i = 0; i < path.size() - 1; ++i)
		{
			const Graph::Node& startNode = graph.GetNode(path[i]);
			const Graph::Node& endNode = graph.GetNode(path[i + 1]);
			u32 x0 = grid.GetX(startNode.GetIndex());
			u32 y0 = grid.GetY(startNode.GetIndex());
			u32 x1 = grid.GetX(endNode.GetIndex());
			u32 y1 = grid.GetY(endNode.GetIndex());

			Vector2 a(MakeVector(x0 * kTileSize, y0 * kTileSize));
			Vector2 b(MakeVector(x1 * kTileSize, y1 * kTileSize));

			//Renderer::AddLineSegment(Point(a + kOffset), Point(b + kOffset), ConstantColours::Green);
		}
	}

	void ShowNeighbours()
	{
		const Graph& graph = grid.GetGraph();
		for (u32 i = 0; i < graph.GetNumberOfNodes(); ++i)
		{
			const Graph::Node& node = graph.GetNode(i);
			u32 x0 = grid.GetX(node.GetIndex());
			u32 y0 = grid.GetY(node.GetIndex());

			for (u32 n = 0; n < node.GetNumberOfNeighbours(); ++n)
			{
				const Graph::Node& neighbour = node.GetNeighbour(n);
				u32 x1 = grid.GetX(neighbour.GetIndex());
				u32 y1 = grid.GetY(neighbour.GetIndex());

				Vector2 a(MakeVector(x0 * kTileSize, y0 * kTileSize));
				Vector2 b(MakeVector(x1 * kTileSize, y1 * kTileSize));

				//Renderer::AddLineSegment(Point(a + kOffset), Point(b + kOffset), ConstantColours::Blue);
			}
		}
	}

	void ShowClosedList()
	{
		const Graph& graph = grid.GetGraph();
		for (u32 i = 0; i < context.ClosedList.size(); ++i)
		{
			const Graph::Node& startNode = graph.GetNode(context.ClosedList[i]);
			u32 next = context.Parents[startNode.GetIndex()];
			if (next == -1)
			{
				continue;
			}
			const Graph::Node& endNode = graph.GetNode(next);
			u32 x0 = grid.GetX(startNode.GetIndex());
			u32 y0 = grid.GetY(startNode.GetIndex());
			u32 x1 = grid.GetX(endNode.GetIndex());
			u32 y1 = grid.GetY(endNode.GetIndex());

			Vector2 a(MakeVector(x0 * kTileSize, y0 * kTileSize));
			Vector2 b(MakeVector(x1 * kTileSize, y1 * kTileSize));

			//Renderer::AddLineSegment(Point(a + kOffset), Point(b + kOffset), ConstantColours::Red);
		}
	}
}
//===========================================================================
// Class Definitions
//===========================================================================

Game::Game()
: Synchronization::WindowedApp()
{}

//---------------------------------------------------------------------------

Game::~Game() {}

//---------------------------------------------------------------------------

void Game::OnInitialize()
{

	Mathematics::Random::Initialize();

	//AI
	grid.Initialize(10, 10);
	context.Filter = IsBlocked;

	const Graph& graph = grid.GetGraph();
	u32 numNodes = graph.GetNumberOfNodes();
	u32 start = Random::GetInteger(0, numNodes - 1);
	u32 end = 0;
	do
	{
		end = Random::GetInteger(0, numNodes - 1);
	} while (end == start);

	//context.Initialize(numNodes, start, end);
	//context.GetH = [](u32 p_Index1, u32 p_Index2)->f32
	//{ return Vector2(MakeVector(static_cast<scalar>(grid.GetX(p_Index1)), static_cast<scalar>(grid.GetY(p_Index1)))
	//- MakeVector(static_cast<scalar>(grid.GetX(p_Index1)), static_cast<scalar>(grid.GetY(p_Index1)))).Length(); };
	//context.GetG = [](u32 p_Index1, u32 p_Index2)->f32
	//{ return Vector(Point(static_cast<scalar>(grid.GetX(p_Index1)), static_cast<scalar>(grid.GetY(p_Index1)), 0.0f)
	//- Point(static_cast<scalar>(grid.GetX(p_Index1)), static_cast<scalar>(grid.GetY(p_Index1)), 0.0f)).Length(); };

	GraphSearch<Dijkstra>::Run(graph, context);
	GraphSearch<Dijkstra>::GetPath(context, path);
}

//---------------------------------------------------------------------------

void Game::OnTerminate()
{
	grid.Free();
}

//---------------------------------------------------------------------------

void Game::OnUpdate(f32 p_DeltaTime)
{
}

//---------------------------------------------------------------------------

void Game::OnRender()
{

	ShowPath();
	ShowClosedList();
	ShowNeighbours();
}