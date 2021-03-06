//===========================================================================
// Filename:	Component.cpp
// Author:		Jarrod MacKay
//===========================================================================

//===========================================================================
// Includes
//===========================================================================

#include "Precompiled.h"
#include "Component.h"

using namespace Gameplay;

//===========================================================================
// Meta Definitions
//===========================================================================

MetaClassBegin(Component)
	MetaNoFields
MetaClassEnd

//===========================================================================
// Class Definitions
//===========================================================================

Component::Component()
: m_GameObject(nullptr)
{}

Component::~Component()
{}