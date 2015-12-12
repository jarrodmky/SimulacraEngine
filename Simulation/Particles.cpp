//===========================================================================
// Filename:	Particles.cpp
// Author:		Jarrod MacKay
//===========================================================================

//===========================================================================
// Includes
//===========================================================================

#include "Precompiled.h"
#include "Particles.h"

using namespace Mathematics;
using namespace Simulation;

//===========================================================================
// Definitions
//===========================================================================

//Particle

Particle::Particle(const Mathematics::Vector3& p_Location)
	: Position()
{}

//----------------------------------------------------------------------------------------------------

Particle::~Particle()
{}

//----------------------------------------------------------------------------------------------------

const Mathematics::scalar Particle::GetMass()
{
	return m_Mass;
}

//----------------------------------------------------------------------------------------------------

void Particle::SetMass(const Mathematics::scalar p_Mass)
{
	m_Mass = p_Mass;
	m_InvMass = Mathematics::EquivalentToZero(p_Mass) ? (0.0f) : (1.0f / p_Mass);
}

//----------------------------------------------------------------------------------------------------

const Mathematics::Vector3 Particle::GetAcceleration(const Mathematics::Vector3 p_Force)
{
	return p_Force * m_InvMass;
}

//Static Particle

StaticParticle::StaticParticle(const Mathematics::Vector3& p_Location)
	: Particle(p_Location)
{}

//----------------------------------------------------------------------------------------------------

StaticParticle::~StaticParticle()
{}

//----------------------------------------------------------------------------------------------------

void StaticParticle::Integrate(const Mathematics::scalar p_DeltaTime, const Mathematics::Vector3& p_Force)
{
	Position += p_Force;
}

//----------------------------------------------------------------------------------------------------

const Mathematics::Vector3 StaticParticle::GetVelocity(const Mathematics::scalar p_InvDeltaTime) const
{
	return Mathematics::Zero3();
}

//Euler Particle

EulerParticle::EulerParticle(const Mathematics::Vector3& p_Location)
	: Particle(p_Location)
{}

//----------------------------------------------------------------------------------------------------

EulerParticle::~EulerParticle()
{}

//----------------------------------------------------------------------------------------------------

void EulerParticle::Integrate(const Mathematics::scalar p_DeltaTime, const Mathematics::Vector3& p_Force)
{
	Position += Velocity * p_DeltaTime;
	Velocity += GetAcceleration(p_Force) * p_DeltaTime;
}

//----------------------------------------------------------------------------------------------------

const Mathematics::Vector3 EulerParticle::GetVelocity(const Mathematics::scalar p_InvDeltaTime) const
{
	return Velocity;
}

//VerletParticle

VerletParticle::VerletParticle(const Mathematics::Vector3& p_Location)
	: Particle(p_Location)
{}

//----------------------------------------------------------------------------------------------------

VerletParticle::~VerletParticle()
{}

//----------------------------------------------------------------------------------------------------

void VerletParticle::Integrate(const Mathematics::scalar p_DeltaTime, const Mathematics::Vector3& p_Force)
{
	using namespace Mathematics;
	const Vector3 currentPosition(Position);
	Position += Position - LastPosition + GetAcceleration(p_Force) * p_DeltaTime * p_DeltaTime;
}

//----------------------------------------------------------------------------------------------------

const Mathematics::Vector3 VerletParticle::GetVelocity(const Mathematics::scalar p_InvDeltaTime) const
{
	return (Position - LastPosition) * p_InvDeltaTime;
}