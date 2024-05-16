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

	void DecRefCount(/*CRef* const this*/) // 숨은 의미 캐치
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
	/* 포인트 연산자 오버로딩 라고 합니다. */
	T* operator->()
	{
		return PTR;
	}

	/* 형변환 연산자 라고 합니다. */
	operator T* () //  그 자신 
	{
		return PTR;
	}

	template<typename OTHERTYPE>
	operator CPtr<OTHERTYPE>()
	{
		return dynamic_cast<OTHERTYPE*>(PTR);
	}

	/////// 추가했습니다. 
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

	CPtr& operator=(T* const _Other) // 주소
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
	/* 포인터 연산자 오버로딩 입니다. */
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
	new를 했으면 delete 를 해줘야한다.
	어딘가에 보관하지 않으면 이 포인터는 잃어버리게 되고 자연스럽게 릭이 발생합니다.
*/
#pragma endregion

#pragma region 다운캐스팅
/*
	다운캐스팅
	강제변환은 안전하지 않다.
	EX) 몬스터
		1. 오크
		2. 드래곤
		드래곤 -> 오크 : 영향을 끼치는 경우가 되어버린다.
*/
#pragma endregion

#pragma region CAST 이슈모음
/*
	const_cast	: const를 const가 아니게 만든다. 사용하지 않는다.

	static_cast	: 우리가 알고 있는 일반적인 memcpy를 통한 캐스트나 다름 없다.
				  크기 검사만 하는 캐스팅에 가깝다. (일반적)

	reinterpret_cast (모름)

	dynamic_cast :  상속관계일 때만 캐스팅을 해준다
					왜 virtual 을 하면 다이내믹 캐스트가 가능해질까?
					상속 관계인지 검사하려면 공짜가 없다. 뭐가 필요할까?
					당연히 값이 필요하다. 메모리가 필요하다.
					검사를 가상함수 포인터를 이용해서 한다. 내부 알고리즘을 정확히 알 수는 없다.
					하지만 가상함수 테이블의 값을 기반으로 캐스팅을 해주기 때문에
					virtual이 부모 쪽에 있어야 한다.
					결론 : 안전한 상황에서만 사용하겠다. 최소한의 안전장치이다.
*/
#pragma endregion