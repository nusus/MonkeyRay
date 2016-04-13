#ifndef CMRGUIEventAdapter_h__
#define CMRGUIEventAdapter_h__

#include "CMRObject.h"  // object引用
//#include "CMRMatrix4x3.h"    //数学库引用
//inclued ""    GraphicsContext引用
#include  "CMREvent.h"
namespace MR {
	struct PointerData : public MR::CMRRef
	{
		PointerData() :
			m_object(0),
			m_x(0.0f),
			m_xMin(-1.0f),
			m_xMax(1.0f),
			m_y(0.0f),
			m_yMin(-1.0f),
			m_yMax(1.0f) {}

		PointerData(MR::CMRObject* obj, float in_x, float in_xMin, float in_xMax, float in_y, float in_yMin, float in_yMax) :
			m_object(obj),
			m_x(in_x),
			m_xMin(in_xMin),
			m_xMax(in_xMax),
			m_y(in_y),
			m_yMin(in_yMin),
			m_yMax(in_yMax) {}

		PointerData(const PointerData& pd) :
			MR::CMRRef(),
			m_xMin(pd.m_xMin),
			m_xMax(pd.m_xMax),
			m_y(pd.m_y),
			m_yMin(pd.m_yMin),
			m_yMax(pd.m_yMax) {}

		PointerData& operator = (const PointerData& pd)
		{
			if (&pd == this) return *this;

			m_object = pd.m_object;
			m_x = pd.m_x;
			m_xMin = pd.m_xMin;
			m_xMax = pd.m_xMax;
			m_y = pd.m_y;
			m_yMin = pd.m_yMin;
			m_yMax = pd.m_yMax;

			return *this;
		}

		MR::SmartPtr<MR::CMRObject> m_object;
		float m_x, m_xMin, m_xMax;
		float m_y, m_yMin, m_yMax;

		float GetXnormalized() const { return (m_x - m_xMin) / (m_xMax - m_xMin)*2.0f - 1.0f; }
		float GetYnormalized() const { return (m_y - m_yMin) / (m_yMax - m_yMin)*2.0f - 1.0f; }
	};


	class  CMRGUIEventAdapter : public CMREvent 
	{
	public:

		enum MouseButtonMask {
			LEFT_MOUSE_BUTTON = 1 << 0,
			MIDDLE_MOUSE_BUTTON = 1 << 1,
			RIGHT_MOUSE_BUTTON = 1 << 2
		};

		enum EventType {
			NONE = 0,
			PUSH = 1 << 0,
			RELEASE = 1 << 1,
			DOUBLECLICK = 1 << 2,
			DRAG = 1 << 3,
			MOVE = 1 << 4,
			KEYDOWN = 1 << 5,
			KEYUP = 1 << 6,
			FRAME = 1 << 7,
			RESIZE = 1 << 8,
			SCROLL = 1 << 9,
			PEN_PRESSURE = 1 << 10,
			PEN_ORIENTATION = 1 << 11,
			PEN_PROXIMITY_ENTER = 1 << 12,
			PEN_PROXIMITY_LEAVE = 1 << 13,
			CLOSE_WINDOW = 1 << 14,
			QUIT_APPLICATION = 1 << 15,
			USER = 1 << 16
		};
		enum KeySymbol
		{
			KEY_Space = 0x20,

			KEY_0 = '0',
			KEY_1 = '1',
			KEY_2 = '2',
			KEY_3 = '3',
			KEY_4 = '4',
			KEY_5 = '5',
			KEY_6 = '6',
			KEY_7 = '7',
			KEY_8 = '8',
			KEY_9 = '9',
			KEY_A = 'a',
			KEY_B = 'b',
			KEY_C = 'c',
			KEY_D = 'd',
			KEY_E = 'e',
			KEY_F = 'f',
			KEY_G = 'g',
			KEY_H = 'h',
			KEY_I = 'i',
			KEY_J = 'j',
			KEY_K = 'k',
			KEY_L = 'l',
			KEY_M = 'm',
			KEY_N = 'n',
			KEY_O = 'o',
			KEY_P = 'p',
			KEY_Q = 'q',
			KEY_R = 'r',
			KEY_S = 's',
			KEY_T = 't',
			KEY_U = 'u',
			KEY_V = 'v',
			KEY_W = 'w',
			KEY_X = 'x',
			KEY_Y = 'y',
			KEY_Z = 'z',

			KEY_Exclaim = 0x21,
			KEY_Quotedbl = 0x22,
			KEY_Hash = 0x23,
			KEY_Dollar = 0x24,
			KEY_Ampersand = 0x26,
			KEY_Quote = 0x27,
			KEY_Leftparen = 0x28,
			KEY_Rightparen = 0x29,
			KEY_Asterisk = 0x2A,
			KEY_Plus = 0x2B,
			KEY_Comma = 0x2C,
			KEY_Minus = 0x2D,
			KEY_Period = 0x2E,
			KEY_Slash = 0x2F,
			KEY_Colon = 0x3A,
			KEY_Semicolon = 0x3B,
			KEY_Less = 0x3C,
			KEY_Equals = 0x3D,
			KEY_Greater = 0x3E,
			KEY_Question = 0x3F,
			KEY_At = 0x40,
			KEY_Leftbracket = 0x5B,
			KEY_Backslash = 0x5C,
			KEY_Rightbracket = 0x5D,
			KEY_Caret = 0x5E,
			KEY_Underscore = 0x5F,
			KEY_Backquote = 0x60,

			KEY_BackSpace = 0xFF08,
			KEY_Tab = 0xFF09,
			KEY_Linefeed = 0xFF0A,
			KEY_Clear = 0xFF0B,
			KEY_Return = 0xFF0D,
			KEY_Pause = 0xFF13,
			KEY_Scroll_Lock = 0xFF14,
			KEY_Sys_Req = 0xFF15,
			KEY_Escape = 0xFF1B,
			KEY_Delete = 0xFFFF,

			KEY_Home = 0xFF50,
			KEY_Left = 0xFF51,
			KEY_Up = 0xFF52,
			KEY_Right = 0xFF53,
			KEY_Down = 0xFF54,
			KEY_Prior = 0xFF55,
			KEY_Page_Up = 0xFF55,
			KEY_Next = 0xFF56,
			KEY_Page_Down = 0xFF56,
			KEY_End = 0xFF57,
			KEY_Begin = 0xFF58,

			KEY_Select = 0xFF60,
			KEY_Print = 0xFF61,
			KEY_Execute = 0xFF62,
			KEY_Insert = 0xFF63,
			KEY_Undo = 0xFF65,
			KEY_Redo = 0xFF66,
			KEY_Menu = 0xFF67,
			KEY_Find = 0xFF68,
			KEY_Cancel = 0xFF69,
			KEY_Help = 0xFF6A,
			KEY_Break = 0xFF6B,
			KEY_Mode_switch = 0xFF7E,
			KEY_Script_switch = 0xFF7E,
			KEY_Num_Lock = 0xFF7F,

			KEY_KP_SPACE = 0xFF80,
			KEY_KP_Tab = 0xFF89,
			KEY_KP_Enter = 0xFF8D,        
			KEY_KP_F1 = 0xFF91,        
			KEY_KP_F2 = 0xFF92,
			KEY_KP_F3 = 0xFF93,
			KEY_KP_F4 = 0xFF94,
			KEY_KP_Home = 0xFF95,
			KEY_KP_Left = 0xFF96,
			KEY_KP_Up = 0xFF97,
			KEY_KP_Right = 0xFF98,
			KEY_KP_Down = 0xFF99,
			KEY_KP_Prior = 0xFF9A,
			KEY_KP_Page_Up = 0xFF9A,
			KEY_KP_Next = 0xFF9B,
			KEY_KP_Page_Down = 0xFF9B,
			KEY_KP_End = 0xFF9C,
			KEY_KP_Begin = 0xFF9D,
			KEY_KP_Insert = 0xFF9E,
			KEY_KP_Delete = 0xFF9F,
			KEY_KP_Equal = 0xFFBD,        
			KEY_KP_Multiply = 0xFFAA,
			KEY_KP_Add = 0xFFAB,
			KEY_KP_Separator = 0xFFAC,       
			KEY_KP_Subtract = 0xFFAD,
			KEY_KP_Decimal = 0xFFAE,
			KEY_KP_Divide = 0xFFAF,

			KEY_KP_0 = 0xFFB0,
			KEY_KP_1 = 0xFFB1,
			KEY_KP_2 = 0xFFB2,
			KEY_KP_3 = 0xFFB3,
			KEY_KP_4 = 0xFFB4,
			KEY_KP_5 = 0xFFB5,
			KEY_KP_6 = 0xFFB6,
			KEY_KP_7 = 0xFFB7,
			KEY_KP_8 = 0xFFB8,
			KEY_KP_9 = 0xFFB9,

			KEY_F1 = 0xFFBE,
			KEY_F2 = 0xFFBF,
			KEY_F3 = 0xFFC0,
			KEY_F4 = 0xFFC1,
			KEY_F5 = 0xFFC2,
			KEY_F6 = 0xFFC3,
			KEY_F7 = 0xFFC4,
			KEY_F8 = 0xFFC5,
			KEY_F9 = 0xFFC6,
			KEY_F10 = 0xFFC7,
			KEY_F11 = 0xFFC8,
			KEY_F12 = 0xFFC9,

			KEY_Shift_L = 0xFFE1,        
			KEY_Shift_R = 0xFFE2,       
			KEY_Control_L = 0xFFE3,        
			KEY_Control_R = 0xFFE4,       
			KEY_Caps_Lock = 0xFFE5,        
			KEY_Shift_Lock = 0xFFE6,        

			KEY_Meta_L = 0xFFE7,        
			KEY_Meta_R = 0xFFE8,        
			KEY_Alt_L = 0xFFE9,        
			KEY_Alt_R = 0xFFEA,        
			KEY_Super_L = 0xFFEB,        
			KEY_Super_R = 0xFFEC,       
			KEY_Hyper_L = 0xFFED,        
			KEY_Hyper_R = 0xFFEE         
		};

		enum ModKeyMask
		{
			MODKEY_LEFT_SHIFT = 0x0001,
			MODKEY_RIGHT_SHIFT = 0x0002,
			MODKEY_LEFT_CTRL = 0x0004,
			MODKEY_RIGHT_CTRL = 0x0008,
			MODKEY_LEFT_ALT = 0x0010,
			MODKEY_RIGHT_ALT = 0x0020,
			MODKEY_LEFT_META = 0x0040,
			MODKEY_RIGHT_META = 0x0080,
			MODKEY_LEFT_SUPER = 0x0100,
			MODKEY_RIGHT_SUPER = 0x0200,
			MODKEY_LEFT_HYPER = 0x0400,
			MODKEY_RIGHT_HYPER = 0x0800,
			MODKEY_NUM_LOCK = 0x1000,
			MODKEY_CAPS_LOCK = 0x2000,
			MODKEY_CTRL = (MODKEY_LEFT_CTRL | MODKEY_RIGHT_CTRL),
			MODKEY_SHIFT = (MODKEY_LEFT_SHIFT | MODKEY_RIGHT_SHIFT),
			MODKEY_ALT = (MODKEY_LEFT_ALT | MODKEY_RIGHT_ALT),
			MODKEY_META = (MODKEY_LEFT_META | MODKEY_RIGHT_META),
			MODKEY_SUPER = (MODKEY_LEFT_SUPER | MODKEY_RIGHT_SUPER),
			MODKEY_HYPER = (MODKEY_LEFT_HYPER | MODKEY_RIGHT_HYPER)
		};
		
		enum MouseYOrientation
		{
			Y_INCREASING_UPWARDS,
			Y_INCREASING_DOWNWARDS
		};

		enum ScrollingMotion
		{
			SCROLL_NONE,
			SCROLL_LEFT,
			SCROLL_RIGHT,
			SCROLL_UP,
			SCROLL_DOWN,
			SCROLL_2D
		};


public:
	CMRGUIEventAdapter();
	CMRGUIEventAdapter(const CMRGUIEventAdapter& rhs, const CMRCopyPolicy& copyop = CMRCopyPolicy::SHALLOW_COPY);
	META_OBJECT(io, GUIEventAdapter);
	virtual CMRGUIEventAdapter* AsCMRGUIEventAdapter() { return this; }
	virtual const CMRGUIEventAdapter* AsCMRGUIEventAdapter() const { return this; }

	static SmartPtr<CMRGUIEventAdapter>& GetAccumulatedEventState();

	void SetEventType(EventType Type) { m_eventType = Type; }
	virtual EventType GetEventType() const { return m_eventType; }
	double Time() const { return m_time; }

	void SetGraphicsContext(osg::GraphicsContext* context) { _context = context; }
	osg::GraphicsContext* getGraphicsContext() { return _context.Get(); }
	const osg::GraphicsContext* getGraphicsContext() const { return _context.Get(); }

	void SetWindowRectangle(int x, int y, int width, int height, bool updateMouseRange = true);
	void SetWindowX(int v) { m_windowX = v; }
	int GetWindowX() const { return m_windowX; }
	void SetWindowY(int v) { m_windowY = v; }
	int GetWindowY() const { return m_windowY; }
	void SetWindowWidth(int v) { m_windowWidth = v; }
	int GetWindowWidth() const { return m_windowWidth; }
	void SetWindowHeight(int v) { m_windowHeight = v; }
	int GetWindowHeight() const { return m_windowHeight; }

	inline void SetKey(int key) { m_key = key; }
	virtual int GetKey() const { return m_key; }
	void SetUnmodifiedKey(int key) { m_unmodifiedKey = key; }
	int GetUnmodifiedKey() const { return m_unmodifiedKey; }

	void SetButton(int button) { m_button = button; }
	int GetButton() const { return m_button; }
	void SetInputRange(float Xmin, float Ymin, float Xmax, float Ymax);
	void SetXmin(float v) { m_Xmin = v; }
	float GetXmin() const { return m_Xmin; }
	void SetXmax(float v) { m_Xmax = v; }
	float GetXmax() const { return m_Xmax; }
	void SetYmin(float v) { m_Ymin = v; }
	float GetYmin() const { return m_Ymin; }
	void SetYmax(float v) { m_Ymax = v; }
	float GetYmax() const { return m_Ymax; }
	void SetX(float x) { m_mx = x; }
	float GetX() const { return m_mx; }
	void SetY(float y) { m_my = y; }
	float GetY() const { return m_my; }

#if 1
	inline float getXnormalized() const
	{
		return m_pointerDataList.size() >= 1 ?
			m_pointerDataList[m_pointerDataList.size() - 1]->GetXnormalized() :
			2.0f*(GetX() - GetXmin()) / (GetXmax() - GetXmin()) - 1.0f;
	}

	inline float getYnormalized() const
	{
		if (m_pointerDataList.size() >= 1) return m_pointerDataList[m_pointerDataList.size() - 1]->GetYnormalized();
		if (m_mouseYOrientation == Y_INCREASING_UPWARDS) return 2.0f*(GetY() - GetYmin()) / (GetYmax() - GetYmin()) - 1.0f;
		else return -(2.0f*(GetY() - GetYmin()) / (GetYmax() - GetYmin()) - 1.0f);
	}

		
#else
#endif
	void SetMouseYOrientation(MouseYOrientation myo) { m_mouseYOrientation = myo; }
	MouseYOrientation GetMouseYOrientation() const { return m_mouseYOrientation; }
	void SetButtonMask(int mask) { m_buttonMask = mask; }
	int GetButtonMask() const { return m_buttonMask; }
	void SetModKeyMask(int mask) { m_modKeyMask = mask; }
	int GetModKeyMask() const { return m_modKeyMask; }
	void SetScrollingMotion(ScrollingMotion motion) { m_scrolling.motion = motion; }
	ScrollingMotion GetScrollingMotion() const { return m_scrolling.motion; }
	void SetScrollingMotionDelta(float x, float y) {
		m_scrolling.motion = SCROLL_2D;
		m_scrolling.deltaX = x;
		m_scrolling.deltaY = y;
	}
	void SetScrollingDeltaX(float v) { m_scrolling.deltaX = v; }
	float GetScrollingDeltaX() const { return m_scrolling.deltaX; }
	void SetScrollingDeltaY(float v) { m_scrolling.deltaY = v; }
	float GetScrollingDeltaY() const { return m_scrolling.deltaY; }

	typedef std::vector< MR::SmartPtr<PointerData> > PointerDataList;
	void SetPointerDataList(const PointerDataList& pdl) { m_pointerDataList = pdl; }
	PointerDataList& GetPointerDataList() { return m_pointerDataList; }
	const PointerDataList& GetPointerDataList() const { return m_pointerDataList; }

	unsigned int GetNumPointerData() const { return static_cast<unsigned int>(m_pointerDataList.size()); }
	PointerData* GetPointerData(unsigned int i) { return m_pointerDataList[i].Get(); }
	const PointerData* GetPointerData(unsigned int i) const { return m_pointerDataList[i].Get(); }

	PointerData* GetPointerData(MR::CMRObject* obj) { for (unsigned int i = 0; i<m_pointerDataList.size(); ++i) { if (m_pointerDataList[i]->m_object == obj) return m_pointerDataList[i].Get(); } return 0; }
	const PointerData* GetPointerData(MR::CMRObject* obj) const { for (unsigned int i = 0; i<m_pointerDataList.size(); ++i) { if (m_pointerDataList[i]->m_object == obj) return m_pointerDataList[i].Get(); } return 0; }
	void AddPointerData(PointerData* pd) { m_pointerDataList.push_back(pd); }


protected:
		virtual ~CMRGUIEventAdapter();

		EventType m_eventType;
		MR::SmartPtr<osg::GraphicsContext> _context;
		int m_windowX;
		int m_windowY;
		int m_windowWidth;
		int m_windowHeight;
		int m_key;
		int m_unmodifiedKey;
		int m_button;
		float m_Xmin, m_Xmax;
		float m_Ymin, m_Ymax;
		float m_mx;
		float m_my;
		int m_buttonMask;
		int m_modKeyMask;
		MouseYOrientation m_mouseYOrientation;

		struct Scrolling {
			ScrollingMotion motion;
			float deltaX;
			float deltaY;

			Scrolling() : motion(SCROLL_NONE), deltaX(0), deltaY(0) {}
			Scrolling(const Scrolling& rhs) : motion(rhs.motion), deltaX(rhs.deltaX), deltaY(rhs.deltaY) {}
		};
		Scrolling m_scrolling;


		PointerDataList m_pointerDataList;
};

}
#endif