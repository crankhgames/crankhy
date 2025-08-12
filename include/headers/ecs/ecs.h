#pragma once
#include <bits/stdc++.h>

// ECS utils

const int COMPONENT_COUNT = 32;
const int MAX_ENTITY_COUNT = 300;

using EntityID = std::uint32_t;
using ComponentBitset = std::bitset<COMPONENT_COUNT>;
using ComponentID = std::size_t;
using ComponentTypeID = std::size_t;
using ComponentType = const char *;
