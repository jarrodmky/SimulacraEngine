//===========================================================================
// Filename:	Terrain.cpp
// Author:		Jarrod MacKay
//===========================================================================

//===========================================================================
// Includes
//===========================================================================

#include "Precompiled.h"
#include "Terrain.h"

using namespace Visualization;
using namespace Mathematics;

//===========================================================================
// Definitions
//===========================================================================

Terrain::Terrain(System& p_System)
	: m_System(p_System)
	, m_Mesh(p_System)
{}