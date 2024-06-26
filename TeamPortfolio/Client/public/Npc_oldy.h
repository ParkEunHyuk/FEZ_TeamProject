#pragma once
#include "Npc.h"

BEGIN(Engine)
class CTransform;
class CTexture;
class CCollision;
class CVIBuffer;
class CRenderer;
END


BEGIN(Client)

class CNpc_oldy : public CNpc
{
private:
	explicit CNpc_oldy(LPDIRECT3DDEVICE9	pGraphicDevice);
	explicit CNpc_oldy(const CNpc_oldy& rhs);
	virtual	~CNpc_oldy() = default;

protected:
	virtual HRESULT Initialize_Prototype(void* pArg) override;
	virtual HRESULT Initialize_Clone(void* pArg) override;
	virtual _int Update(_float fDeltaTime)override;
	virtual _int LateUpdate(_float fDeltaTime)override;
	virtual _int Render()override;
	virtual _int LateRender()override;
	virtual HRESULT ReInitialize(void* pArg)override;

public:
private:
	CTexture*				m_ComTexture = nullptr;
	CTransform*				m_ComTransform = nullptr;
	CVIBuffer_Rect*			m_ComRectVIBuffer = nullptr;
	CRenderer*				m_ComRenderer = nullptr;



	/* �浹ó�� */
	CCollision*				m_pCollisionCom = nullptr;
private:
	NPCDESC					m_tNpcDesc;
	_bool					m_bIsShdow = false;
	_bool					m_bisMoveRight = false;
	_bool					m_bMove = false;
	_float					m_fMoveTime = 0.f;
	_float					m_fPassedTime = 0.f;
	_float					m_fStartMoveCount = 0.f;
	_bool					m_bPause = false;
	_bool					m_bTextStart = false;
	_float					m_fText = 0.f;
	_float					m_fFrame = 0.f;
	_int					m_iRand = 0;
private:


	HRESULT	SetUp_Components();
	HRESULT SetUp_RenderState();
	HRESULT Release_RenderState();

	HRESULT Move(_float DeltaTime);
	_int Obsever_On_Trigger(CGameObject * pDestObjects, _float3 fCollision_Distance, _float fDeltaTime);
public:
	static CNpc_oldy* Create(LPDIRECT3DDEVICE9 pGraphicDevice, void* pArg = nullptr);
	virtual CGameObject* Clone(void* pArg = nullptr);
	virtual void Free()override;
};
END
