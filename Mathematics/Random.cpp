#include "Precompiled.h"
#include "Random.h"

using namespace Mathematics;

u64 Random::m_Seed64 = 0;

u64 Random::m_Seed1024[16];

u8 Random::m_Step = 0;

bool Random::m_Initialized = false;