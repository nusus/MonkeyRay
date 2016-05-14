#include "CMRCloth.h"

using namespace MR;

const float MR::CMRParticle::s_kMassConstant = 1.0f;

const float MR::CMRSpring::s_kDefaultDamping = -0.0125f;

const float MR::CMRSpring::s_kKStructural = 50.75f;

const float MR::CMRSpring::s_kDStructural = -0.25f;

const float MR::CMRSpring::s_kKShear = 50.75f;

const float MR::CMRSpring::s_kDShear = -0.25f;

const float MR::CMRSpring::s_kKBend = 50.95f;

const float MR::CMRSpring::s_kDBend = -0.25f;

const vmath::vec3 s_kGravity = vmath::vec3(0.0f, -0.00981f, 0.0f);

MR::CMRCloth::~CMRCloth()
{
	m_particles.clear();
	m_springs.clear();
	m_indices.clear();
}

void MR::CMRCloth::_AddSpring(CMRParticle* p1, CMRParticle* p2, float fk, float fdamping, CMRSpring::SpringType type)
{
	if (p1 == nullptr || p2 == nullptr)
	{
		CMR_STD_OUT << "particle can not be null" << CMR_STD_ENDL;
		assert(false);
		return;
	}
	float rest_length = vmath::length(p1->pos - p2->pos);
	CMRSpring* ret = new CMRSpring(p1, p2, rest_length, fk, fdamping, type);
	m_springs.push_back(ret);
}

void MR::CMRCloth::_InitCloth()
{
	int i = 0, j = 0, count = 0;
	int l1 = 0, l2 = 0;
	int v = m_verticalCount + 1;
	int u = m_horizontalCount + 1;

	//fill in position
	float hsize = m_sizeNumber / 2.0f;
	for (j = 0; j <= m_verticalCount; j++)
	{
		for (i = 0; i <= m_horizontalCount; i++)
		{
			vmath::vec3 pos(((float(i) / (u - 1)) * 2 - 1)* hsize, m_sizeNumber + 1, ((float(j) / (v - 1))* m_sizeNumber));
			CMRParticle* particle = new CMRParticle(CMRParticle::s_kMassConstant, pos, pos, vmath::vec3(), i, j);
			m_particles[count] = particle;
			count++;
		}
	}

	//fill in indices
	GLushort* id = &m_indices[0];
	for (i = 0; i < m_verticalCount; i++) {
		for (j = 0; j < m_horizontalCount; j++) {
			int i0 = i * (m_horizontalCount + 1) + j;
			int i1 = i0 + 1;
			int i2 = i0 + (m_horizontalCount + 1);
			int i3 = i2 + 1;
			if ((j + i) % 2) {
				*id++ = i0; *id++ = i2; *id++ = i1;
				*id++ = i1; *id++ = i2; *id++ = i3;
			}
			else {
				*id++ = i0; *id++ = i2; *id++ = i3;
				*id++ = i0; *id++ = i3; *id++ = i1;
			}
		}
	}

	//setup springs
	// Horizontal
	for (l1 = 0; l1 < v; l1++)	// v
		for (l2 = 0; l2 < (u - 1); l2++) {
			_AddSpring(m_particles[(l1 * u) + l2], m_particles[(l1 * u) + l2 + 1], CMRSpring::s_kKStructural, CMRSpring::s_kDStructural, CMRSpring::STRUCTURAL);
		}

	// Vertical
	for (l1 = 0; l1 < (u); l1++)
		for (l2 = 0; l2 < (v - 1); l2++) {
			_AddSpring(m_particles[(l2 * u) + l1], m_particles[((l2 + 1) * u) + l1], CMRSpring::s_kKStructural, CMRSpring::s_kDStructural, CMRSpring::STRUCTURAL);
		}


	// Shearing Springs
	for (l1 = 0; l1 < (v - 1); l1++)
		for (l2 = 0; l2 < (u - 1); l2++) {
			_AddSpring(m_particles[(l1 * u) + l2], m_particles[((l1 + 1) * u) + l2 + 1], CMRSpring::s_kKShear, CMRSpring::s_kDShear, CMRSpring::SHEAR);
			_AddSpring(m_particles[((l1 + 1) * u) + l2], m_particles[(l1 * u) + l2 + 1], CMRSpring::s_kKShear, CMRSpring::s_kDShear, CMRSpring::SHEAR);
		}


	// Bend Springs
	for (l1 = 0; l1 < (v); l1++) {
		for (l2 = 0; l2 < (u - 2); l2++) {
			_AddSpring(m_particles[(l1 * u) + l2], m_particles[(l1 * u) + l2 + 2], CMRSpring::s_kKBend, CMRSpring::s_kDBend, CMRSpring::BEND);
		}
		_AddSpring(m_particles[(l1 * u) + (u - 3)], m_particles[(l1 * u) + (u - 1)], CMRSpring::s_kKBend, CMRSpring::s_kDBend, CMRSpring::BEND);
	}
	for (l1 = 0; l1 < (u); l1++) {
		for (l2 = 0; l2 < (v - 2); l2++) {
			_AddSpring(m_particles[(l2 * u) + l1], m_particles[((l2 + 2) * u) + l1], CMRSpring::s_kKBend, CMRSpring::s_kDBend, CMRSpring::BEND);
		}
		_AddSpring(m_particles[((v - 3) * u) + l1], m_particles[((v - 1) * u) + l1], CMRSpring::s_kKBend, CMRSpring::s_kDBend, CMRSpring::BEND);
	}
	m_bInit = true;
}

void MR::CMRCloth::_ComputeForces(float dt)
{
	size_t i = 0;

	for (i = 0; i < m_totalPoints; i++) {
		CMRParticle* particle = m_particles[i].Get();
		CMRParticle::Force& force = particle->force;
		force = vmath::vec3(0);
		float mass = particle->mass;
		vmath::vec3 V = particle->GetVerletVelocity(dt);
		//add gravity force
		if (i != 0 && i != (m_horizontalCount))
			force += s_kGravity*mass;
		//add force due to damping of velocity
		force += CMRSpring::s_kDefaultDamping * V;
	}


	for (i = 0; i < m_springs.size(); i++) {
		CMRSpring* spring = m_springs[i].Get();
		CMRParticle* par1 = spring->particle1;
		CMRParticle* par2 = spring->particle2;
		vmath::vec3 p1 =  par1->pos;
		vmath::vec3 p1Last = par1->last_pos;
		vmath::vec3 p2 = par2->pos;
		vmath::vec3 p2Last = par2->last_pos;

		vmath::vec3 v1 = par1->GetVerletVelocity(dt);
		vmath::vec3 v2 = par2->GetVerletVelocity(dt);

		vmath::vec3 deltaP = p1 - p2;
		vmath::vec3 deltaV = v1 - v2;
		float dist = vmath::length(deltaP);

		float leftTerm = -m_springs[i]->k * (dist - m_springs[i]->rest_length);
		float rightTerm = m_springs[i]->damping * (vmath::dot(deltaV, deltaP) / dist);
		//float rightTerm = springs[i].Kd * (vmath::length(deltaV));
		vmath::vec3 springForce = (leftTerm + rightTerm)*vmath::normalize(deltaP);
		GLint index1 = par1->num_y * m_horizontalCount + par1->num_x;
		GLint index2 = par2->num_y * m_horizontalCount + par2->num_x;
		if (index1 != 0 && index1 != m_horizontalCount)
			par1->force += springForce;
		if (index2 != 0 && index2 != m_horizontalCount)
			par2->force -= springForce;
	}
}

void MR::CMRCloth::_IntegrateVerlet(float deltaTime)
{
	float deltaTime2Mass = (deltaTime*deltaTime) / CMRParticle::s_kMassConstant;
	size_t i = 0;


	for (i = 0; i < m_totalPoints; i++) {
		vmath::vec3& pos = m_particles[i]->pos;
		vmath::vec3& last_pos = m_particles[i]->last_pos;
		vmath::vec3 buffer = pos;

		pos = pos + (pos - last_pos) + deltaTime2Mass * m_particles[i]->force;

		last_pos = buffer;

		if (pos[1] < 0) {
			pos[1] = 0;
		}
	}
}

void MR::CMRCloth::_UpdatePhysics(float deltaTime)
{
	_ComputeForces(deltaTime);
	_IntegrateVerlet(deltaTime);
}

