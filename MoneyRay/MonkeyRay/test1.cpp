void SetCullCallback(CMRCallback* cb);

template<typename T>
void SetCullCallback(const SmartPtr<T>& cb)
{
	SetCullCallback(cb.Get());
}

inline CMRCallback* GetCullCallback() { return m_spCullCallback.Get(); }

inline const CMRCallback* GetCullCallback() const { return m_spCullCallback.Get(); }

inline void AddCullCallback(CMRCallback* cb)
{
	if (cb != nullptr)
	{
		if (m_spCullCallback.Valid())
		{
			m_spCullCallback->AddNestedCallback(cb);
		}
		else
		{
			SetCullCallback(cb);
		}
	}
}

template<typename T>
void AddCullCallback(const SmartPtr<T>& cb)
{
	AddCullCallback(cb.Get());
}

inline void RemoveCullCallback(CMRCallback* cb)
{
	if (cb != nullptr && m_spCullCallback.Valid())
	{
		if (m_spCullCallback == cb)
		{
			SmartPtr<CMRCallback> newCullCallback = cb->GetNestedCallback();
			cb->SetNestedCallback(0);
			SetCullCallback(newCullCallback.Get());
		}
		else
		{
			m_spCullCallback->RemoveNestedCallback(cb);
		}
	}
}

template<typename T>
void RemoveCullCallback(const SmartPtr<T>& cb)
{
	RemoveCullCallback(cb.Get());
}