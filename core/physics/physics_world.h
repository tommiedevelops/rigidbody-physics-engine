#ifndef PHYSICS_WORLD_H
#define PHYSICS_WORLD_H

#include <vector>

class RigidBody {};
class Collider {};
class ContactManifold {};
class Broadphase {};
class Narrowphase {};
class ConstraintSolver {};

class PhysicsWorld
{ 
private:
	std::vector<RigidBody>          m_bodies;
	std::vector<Collider>           m_colliders;
	std::vector<ContactManifold>    m_contacts;

	Broadphase         m_broadphase;
	Narrowphase        m_narrowphase;
	ConstraintSolver   m_solver;

};

#endif