//===========================================================================
// Filename:	Field.cpp
// Author:		Jarrod MacKay
//===========================================================================

//===========================================================================
// Includes
//===========================================================================

#include "Field.h"
#include "Type.h"

//===========================================================================
// Feild Definitions
//===========================================================================

Meta::Field::Field(const char* p_Name
	, const Meta::Type* p_Type
	, const u32 p_Offset)
	: m_Name(p_Name)
	, m_Type(p_Type)
	, m_Offset(p_Offset)
{}