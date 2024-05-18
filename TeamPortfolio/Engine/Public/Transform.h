#pragma once

#include "Component.h"


BEGIN(Engine)

class ENGINE_DLL CTransform : public CComponent
{
public:
	enum TransformState { STATE_RIGHT, STATE_UP, STATE_LOOK, STATE_POS, STATE_END };
	typedef struct tagTransformDesc
	{
		//Move Speed Per Sec
		_float		fMovePerSec;
		//(Radian)Rotation Speed Per Sec 
		_float		fRotationPerSec;
		//�ؽ��ĸ� �׸� �� ������ ���� ��ǥ ���� ��
		_float3		vPivot = _float3(0, 0, 0);
	}TRANSFORMDESC;

	

private:
	explicit CTransform(LPDIRECT3DDEVICE9 pGraphicDevice);
	explicit CTransform(const CTransform& rhs);
	virtual ~CTransform() = default;

public:
	//SetDesc
	void Set_MoveSpeed(_float fMoveSpeed) { m_TransforDesc.fMovePerSec = fMoveSpeed; };

//Move////////////////////////////////////////////////////////////////////////
	void Move_Forward(_float fDeltaTime);
	void Move_Backward(_float fDeltaTime);
	void Move_Right(_float fDeltaTime);
	void Move_Left(_float fDeltaTime);
	void Move_Up(_float fDeltaTime);
	void Move_Down(_float fDeltaTime);

	void MovetoDir(_float3 vDir, _float fDeltaTime);
	void MovetoTarget(_float3 vTarget, _float fDeltaTime);


//Turn////////////////////////////////////////////////////////////////////////
	void LookAt(_float3 vTarget);
	
	//���� ��ǥ �������� ���� ȸ�� ���¿��� �̾ ȸ���� �ϰ����� ��
	void Turn_CW(_float3 vAxis, _float fDeltaTime);
	void Turn_CCW(_float3 vAxis, _float fDeltaTime);

	//���� ��ǥ �������� ȸ���� �����ְ� ���� ��
	void Rotation_CW(_float3 vAxis, _float fRadian);
	void Rotation_CCW(_float3 vAxis, _float fRadian);

//Scale////////////////////////////////////////////////////////////////////////
	//���� �������� Ư�� ������� �����ϰ� ���� ��
	void Scaled(_float3 vScale);
	//���� �������� �̾ ����� �����ϰ� ���� ��
	void Scaling(_float3 vScale, _float fDeltaTime);


public:
	_float3 Get_MatrixState(TransformState eState) { return *(_float3*)(m_WorldMatrix.m[eState]); };
	_float3 Get_MatrixScale() { return _float3(Get_MatrixState(STATE_RIGHT).Get_Lenth(), Get_MatrixState(STATE_UP).Get_Lenth(), Get_MatrixState(STATE_LOOK).Get_Lenth()); };

	void Set_MatrixState(TransformState eState, const _float3& vRow) { memcpy(m_WorldMatrix.m[eState], &vRow, sizeof(_float3)); };
	void Set_Matrix(const _Matrix& mat) { memcpy(m_WorldMatrix, mat, sizeof(_Matrix)); };

	_Matrix Get_InverseWorldMatrix() { return m_WorldMatrix.InverseMatrix(); };

	void Set_TransformDesc(const TRANSFORMDESC& TransformDesc) {m_TransforDesc = TransformDesc;	};

	_Matrix Get_WorldMatrix() { return m_WorldMatrix; }

public:
	//��ġ�� ���� ����� �����Ű�� �Լ�
	HRESULT Bind_WorldMatrix();
	HRESULT Bind_WorldMatrix_Look_Camera();

public:
	HRESULT Initialize_Prototype(void * pArg);
	HRESULT Initialize_Clone(void * pArg);


private:
	_Matrix			m_WorldMatrix;
	TRANSFORMDESC	m_TransforDesc;

public:
	static CTransform* Create(LPDIRECT3DDEVICE9 pGraphicDevice, void* pArg = nullptr);
	virtual CComponent* Clone(void* pArg)override;
	virtual void Free()override;
};

END