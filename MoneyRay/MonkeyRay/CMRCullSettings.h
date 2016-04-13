#ifndef CMRCullSettings_h__
#define CMRCullSettings_h__

namespace MR
{
	class CMRCullSettings
	{
	public:
		enum VariablesMask
		{
			COMPUTE_NEAR_FAR_MODE = (0x1 << 0),
			CULLING_MODE = (0x1 << 1),
			LOD_SCALE = (0x1 << 2),
			SMALL_FEATURE_CULLING_PIXEL_SIZE = (0x1 << 3),
			CLAMP_PROJECTION_MATRIX_CALLBACK = (0x1 << 4),
			NEAR_FAR_RATIO = (0x1 << 5),
			IMPOSTOR_ACTIVE = (0x1 << 6),
			DEPTH_SORT_IMPOSTOR_SPRITES = (0x1 << 7),
			IMPOSTOR_PIXEL_ERROR_THRESHOLD = (0x1 << 8),
			NUM_FRAMES_TO_KEEP_IMPOSTORS_SPRITES = (0x1 << 9),
			CULL_MASK = (0x1 << 10),
			CULL_MASK_LEFT = (0x1 << 11),
			CULL_MASK_RIGHT = (0x1 << 12),
			CLEAR_COLOR = (0x1 << 13),
			CLEAR_MASK = (0x1 << 14),
			LIGHTING_MODE = (0x1 << 15),
			LIGHT = (0x1 << 16),
			DRAW_BUFFER = (0x1 << 17),
			READ_BUFFER = (0x1 << 18),

			NO_VARIABLES = 0x00000000,
			ALL_VARIABLES = 0x7FFFFFFF
		};

		enum InheritanceMaskActionOnAttributeSetting
		{
			DISABLE_ASSOCIATED_INHERITANCE_MASK_BIT,
			DO_NOT_MODIFY_INHERITANCE_MASK
		};

		typedef int InheritanceMask;
	public:
		CMRCullSettings();
		CMRCullSettings(const CMRCullSettings* cs);
		virtual ~CMRCullSettings() {}
		CMRCullSettings& operator = (const CMRCullSettings& cs)
		{
			if (this == &cs)
			{
				return *this;
			}
			SetCullSettings(cs);
			return *this;
		}

		void SetCullSettings(const CMRCullSettings& cs);

		void SetInheritanceMask(InheritanceMask mask)
		{
			m_inheritanceMask = mask;
		}
		
		InheritanceMask GetInheritanceMask()const
		{
			return m_inheritanceMask;
		}

		virtual void InheritanceCullSettings(const CMRCullSettings& settings)
		{
			InheritanceCullSettings(settings, m_inheritanceMask);
		}

		virtual void InheritanceCullSettings(const CMRCullSettings& settings, InheritanceMask mask)
		{

		}

		void SetInheritanceMaskActionOnAttributeSetting(InheritanceMaskActionOnAttributeSetting action)
		{
			m_inheritanceMaskActionOnAttributeSetting = action;
		}

		InheritanceMaskActionOnAttributeSetting GetInheritanceMaskActionAttributeSetting() const { return m_inheritanceMaskActionOnAttributeSetting; }


		inline void ApplyMaskAction(unsigned int maskBit)
		{
			if (m_inheritanceMaskActionOnAttributeSetting == DISABLE_ASSOCIATED_INHERITANCE_MASK_BIT)
			{
				m_inheritanceMask = m_inheritanceMask & (~maskBit);
			}
		}

		void SetImpostorsActive(bool bActive) { m_bImpostorsActive = bActive; ApplyMaskAction(IMPOSTOR_ACTIVE); }

	protected:
		InheritanceMask m_inheritanceMask;
		InheritanceMaskActionOnAttributeSetting m_inheritanceMaskActionOnAttributeSetting;
		bool m_bImpostorsActive;
	};
}

#endif // CMRCullSettings_h__
