#ifndef IncludedUtilInputStateH
#define IncludedUtilInputStateH

//====================================================================================================
// Filename:	InputState.h
// Created by:	Jarrod MacKay
// Description:	Abstracts keyboard, mouse and gamepad input so the game can query the state.
//====================================================================================================

//====================================================================================================
// Includes
//====================================================================================================

#include <Mathematics.h>
#include "System.h"

namespace Utilization
{

//====================================================================================================
// Definitions
//====================================================================================================
class InputState
{
//Attributes
private:

	System* m_System;

	Mathematics::Vector2 m_LeftDisc;
	Mathematics::Vector2 m_RightDisc;

	Mathematics::Vector2 m_LeftDiscCentre;
	Mathematics::Vector2 m_RightDiscCentre;

	bool m_ActionPressed;
	bool m_ConfirmPressed;
	bool m_DenyPressed;
	bool m_FullscreenPressed;

//Operators
public:

	InputState(System& p_System);

	~InputState();

//Methods
public:


	void Calibrate();
	void Update();

	bool Actioned() const;
	bool Confirmed() const;
	bool Denied() const;
	bool Fullscreen() const;
	f32 GetLeftVerticalAxis() const;
	f32 GetRightVerticalAxis() const;
	f32 GetLeftHorizontalAxis() const;
	f32 GetRightHorizontalAxis() const;

private:

	void Reset();

};

}

#endif