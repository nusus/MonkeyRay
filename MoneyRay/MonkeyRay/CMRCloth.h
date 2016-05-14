#ifndef CMRCloth_h__
#define CMRCloth_h__
#include "CMRRef.h"
#include "CMRDrawable.h"
namespace MR
{
	class CMRParticle : public CMRRef
	{
	public:
		typedef vmath::vec3 Force;


	public:
		CMRParticle() :
			mass(0.0f),
			pos(),
			last_pos(),
			force(),
			num_x(0),
			num_y(0)
		{}

		CMRParticle(float fMass, const vmath::vec3& vpos, const vmath::vec3& vlast_pos, const Force& vforce, GLint numX, GLint numY) :
			mass(fMass),
			pos(vpos),
			last_pos(vlast_pos),
			force(vforce),
			num_x(numX),
			num_y(numY)
		{}


	public:
		vmath::vec3 GetVerletVelocity(float dt)
		{
			return (pos - last_pos) / dt;
		}


	public:
		static const float s_kMassConstant;

	public:
		float			mass;
		vmath::vec3		pos;
		vmath::vec3		last_pos;
		Force			force;
		GLint           num_x;
		GLint           num_y;
	};

	class CMRSpring : public CMRRef
	{
	public:
		enum SpringType
		{
			STRUCTURAL,
			SHEAR,
			BEND

		};


	public:
		CMRSpring(CMRParticle* pa, CMRParticle* p2, float frest_length, float fk, float fdamping, SpringType enumType):
			particle1(pa),
			particle2(p2),
			rest_length(frest_length),
			k(fk),
			damping(fdamping),
			type(enumType)
		{}


	public:
		static const float s_kDefaultDamping;

		static const float s_kKStructural;
		static const float s_kDStructural;
		static const float s_kKShear;
		static const float s_kDShear;
		static const float s_kKBend;
		static const float s_kDBend;

	public:
		CMRParticle* particle1;
		CMRParticle* particle2;
		float rest_length;
		float k;
		float damping;
		SpringType type;
	};

	class CMRCloth : public CMRDrawable
	{
	public:
		typedef vector<SmartPtr<CMRSpring> >	Springs;
		typedef vector<SmartPtr<CMRParticle> >	Particles;
		typedef vector<GLushort>                Indices;


	public:
		CMRCloth(int hCount, int vCount, int sizeNum) :
			m_horizontalCount(hCount),
			m_verticalCount(vCount),
			m_sizeNumber(sizeNum),
			m_bInit(false),
			m_totalPoints((hCount + 1) * (vCount + 1)),
			m_springs(m_totalPoints),
			m_indices(m_horizontalCount * m_verticalCount * 2 * 3)
		{}


	public:
		virtual void DrawImplemention(CMRProgram* program) override
		{
			throw std::logic_error("The method or operation is not implemented.");
		}

		virtual void Accept(CMRNodeVisitor& nv) override
		{
			
		}

	protected:
		virtual ~CMRCloth();


	protected:
		void _AddSpring(CMRParticle* p1, CMRParticle* p2, float fk, float fdamping, CMRSpring::SpringType type);
		template<typename T>
		void _AddSpring(const SmartPtr<T>& p1, const SmartPtr<T>& p2, float fk, float fdamping, CMRSpring::SpringType type)
		{
			_AddSpring(p1.Get(), p2.Get(), fk, fdamping, type);
		}

		void _InitCloth();

		void _ComputeForces(float dt);

		void _IntegrateVerlet(float dt);

		void _UpdatePhysics(float deltaTime);


	protected:
		bool		m_bInit;
		int			m_horizontalCount;
		int			m_verticalCount;
		int			m_totalPoints;
		int			m_sizeNumber;
		Springs		m_springs;
		Particles	m_particles;
		Indices		m_indices;
	};
}
#endif // CMRCloth_h__
