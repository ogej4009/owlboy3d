#pragma once

class CRef
{
public:
	int RefCount;

public:
	void AddRefCount()
	{
		++RefCount;
	}

	void DecRefCount(/*CRef* const this*/) // ���� �ǹ� ĳġ
	{
		--RefCount;
		if (0 >= RefCount)
		{
			delete this;
		}
	}

public:
	CRef() : RefCount(0) {}
	virtual ~CRef() {}
};


template<typename T>
class CPtr
{
public:
	T* PTR;

public:
	/* ����Ʈ ������ �����ε� ��� �մϴ�. */
	T* operator->()
	{
		return PTR;
	}

	/* ����ȯ ������ ��� �մϴ�. */
	operator T* () //  �� �ڽ� 
	{
		return PTR;
	}

	template<typename OTHERTYPE>
	operator CPtr<OTHERTYPE>()
	{
		return dynamic_cast<OTHERTYPE*>(PTR);
	}

	/////// �߰��߽��ϴ�. 
	template<typename OTHERTYPE>
	operator OTHERTYPE* ()
	{
		return dynamic_cast<OTHERTYPE*>(PTR);
	}

	bool operator==(const CPtr<T>& _Other) const
	{
		return PTR == _Other.PTR;
	}

	bool operator==(void* _nullptr) const
	{
		return PTR == _nullptr;
	}

	bool operator!=(void* _nullptr) const
	{
		return PTR != _nullptr;
	}

	CPtr& operator=(const CPtr<T>& _Other)
	{
		if (nullptr != PTR)
		{
			PTR->DecRefCount();
		}

		PTR = _Other.PTR;

		if (nullptr != PTR)
		{
			PTR->AddRefCount();
		}
		return *this;
	}

	CPtr& operator=(T* const _Other) // �ּ�
	{
		if (nullptr != PTR)
		{
			PTR->DecRefCount();
		}

		PTR = _Other;
		if (nullptr != PTR)
		{
			PTR->AddRefCount();
		}
		return *this;
	}

public:
	CPtr(const CPtr<T>& _Other) : PTR(_Other.PTR)
	{
		if (nullptr == PTR)
		{
			return;
		}
		PTR->AddRefCount();
	}

	CPtr(T* _Ptr) : PTR(_Ptr)
	{
		if (nullptr == _Ptr)
		{
			return;
		}

		_Ptr->AddRefCount();
	}

	CPtr() : PTR(nullptr) {}

	~CPtr()
	{
		if (nullptr == PTR)
		{
			return;
		}

		PTR->DecRefCount();
	}
};


template<typename T>
bool operator!=(void* _Ptr, const CPtr<T> _TypeName)
{
	return _TypeName.operator!=(_Ptr);
}


template<typename T>
bool operator==(void* _Ptr, const CPtr<T> _TypeName)
{
	return _TypeName.operator==(_Ptr);
}


template<typename T>
class CWPtr
{
public:
	T* PTR;

public:
	/* ������ ������ �����ε� �Դϴ�. */
	T* operator->()
	{
		return PTR;
	}

	CWPtr& operator=(const CWPtr<T>& _Other)
	{
		PTR = _Other.PTR;
		return *this;
	}

public:
	CWPtr(const CPtr<T>& _Other) : PTR(_Other.PTR) {}
	CWPtr() : PTR(nullptr) {}
	CWPtr(T* _Ptr) : PTR(_Ptr) {}
	virtual ~CWPtr() {}
};

#pragma region new delete
/*
	new�� ������ delete �� ������Ѵ�.
	��򰡿� �������� ������ �� �����ʹ� �Ҿ������ �ǰ� �ڿ������� ���� �߻��մϴ�.
*/
#pragma endregion

#pragma region �ٿ�ĳ����
/*
	�ٿ�ĳ����
	������ȯ�� �������� �ʴ�.
	EX) ����
		1. ��ũ
		2. �巡��
		�巡�� -> ��ũ : ������ ��ġ�� ��찡 �Ǿ������.
*/
#pragma endregion

#pragma region CAST �̽�����
/*
	const_cast	: const�� const�� �ƴϰ� �����. ������� �ʴ´�.

	static_cast	: �츮�� �˰� �ִ� �Ϲ����� memcpy�� ���� ĳ��Ʈ�� �ٸ� ����.
				  ũ�� �˻縸 �ϴ� ĳ���ÿ� ������. (�Ϲ���)

	reinterpret_cast (��)

	dynamic_cast :  ��Ӱ����� ���� ĳ������ ���ش�
					�� virtual �� �ϸ� ���̳��� ĳ��Ʈ�� ����������?
					��� �������� �˻��Ϸ��� ��¥�� ����. ���� �ʿ��ұ�?
					�翬�� ���� �ʿ��ϴ�. �޸𸮰� �ʿ��ϴ�.
					�˻縦 �����Լ� �����͸� �̿��ؼ� �Ѵ�. ���� �˰����� ��Ȯ�� �� ���� ����.
					������ �����Լ� ���̺��� ���� ������� ĳ������ ���ֱ� ������
					virtual�� �θ� �ʿ� �־�� �Ѵ�.
					��� : ������ ��Ȳ������ ����ϰڴ�. �ּ����� ������ġ�̴�.
*/
#pragma endregion