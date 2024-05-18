#pragma once

#include "UI.h"


BEGIN(Engine)
class CTexture;
class CRenderer;
class CVIBuffer_Rect;
class CTransform;
END

BEGIN(Client)

class CUI_Result final :public CUI
{
private:
	explicit CUI_Result(LPDIRECT3DDEVICE9 pGraphicDevice);
	explicit CUI_Result(const CUI_Result& rhs);
	virtual ~CUI_Result() = default;

public:
	virtual HRESULT Initialize_Prototype(void* pArg)override;
	virtual HRESULT Initialize_Clone(void* pArg)override;

	virtual _int Update(_float fDeltaTime)override;

	virtual _int LateUpdate(_float fDeltaTime)override;

	virtual _int Render()override;
	virtual _int LateRender()override;

private:
	HRESULT		SetUp_Components();
	HRESULT		SetUp_RenderState();
	HRESULT		Release_RenderState();
	HRESULT		SetUp_Pont(); //��Ʈ�� ���õ� �Լ�
	HRESULT		SetUp_Player();	//�÷��̾�� ������ �� ���̴� �Լ�
public:
	void		Button_Picking();
	void		Set_Clear(_bool _bClear);
	void		Set_Clear_Wait_AnimTime(_bool bIsClear, _float MaxAnimTime);
	HRESULT		Ready_Layer_RankStar(const _tchar * pLayerTag);
	void		Set_RankStar();
	_int		Get_RankStar() {return RankNumber;}

	void		Set_PlusTimer(_float fPlusTime) {m_fMaxTime += fPlusTime; }
	void		Set_MaxTime(_float fMaxtime) { m_fMaxTime= fMaxtime; };
	_float		Get_MaxTime() { return m_fMaxTime; };
	_float		Get_NowTime() { return m_fTimer; };
	void		Set_MaxTimebyTimeUp(_float fTime) { m_fMaxTimebySkill += fTime; }
	_float		Get_MaxTimebyTimeUp() { return m_fMaxTimebySkill; }
	//������ �����ӿ�ũ
private:
	HRESULT		Ready_Layer_Button(const _tchar * pLayerTag);//��ư Ŭ���� ����� ����
	HRESULT		Update_UIButtonList(_float fTimeDelta); //�̰� ��ư�� ������Ʈ�� �����ְ� �ִ�.
	HRESULT		LateUpdate_UIButtonList(_float fTimeDelta); //�̰� ��ư�� ����Ʈ������Ʈ�� �����ְ� �ִ�.
	CUI *		Find_UI(const _tchar * tagUI); //UI ��ġ�°� �ִ��� üũ
	CUI *		Find_Button(const _tchar * tagUIList); //�̰� Ŭ���� ã��

	void		Set_Particle_Firecracker2();
	void		Set_Particle_Firecracker();

	void		Set_Particle_Cry();

private:
	CTexture*				m_ComTexture = nullptr;
	CTransform*				m_ComTransform = nullptr;
	CVIBuffer_Rect*			m_ComVIBuffer = nullptr;
	CRenderer*				m_ComRenderer = nullptr;

private:
	map<const _tchar*, CUI*>			m_UIButtonList;
	map<const _tchar*, CUI*>			m_UIPrototypes;

	_float			m_fForPlayerAnimationMaxTime = 0;
	_float			m_fPlayerAnimFrame = 0;
	_bool			m_bAfterAnimIsClear = false;		//�÷��̾� �ִϸ��̼� ���� Ŭ����� ������� ���з� ������� ���θ� �Ǵ��� ����


	_float			m_fFrame = 0.f;
	_float			m_fFrameTexture = 0.f;
	_float4			m_vUIDesc; //���â��

	_float4			m_vButtonDesc; // ��ư��
	RECT			m_fStartButton;
	RECT			m_fCancelButton;

	_bool			m_isClicked = false;

	_float			m_fMaxTimebySkill = 0;
	_uint			RankNumber = 0;
	_bool			m_bStopSwitch = false; //Ÿ�̸� ���� ����
	_float			m_fTimer = 0.f; // Ÿ�̸�
	_float			m_fMaxTime = 0.f; // �ִ� �ð�
	_bool			m_bClear = false; //Ŭ���� ����
	_uint			TempMinutes = 0; //������� �����
	_uint			TempSeconds = 0; //�������� �����

	_uint			RankStarGold = 0; //RankStar �ϳ��� ��差
	_uint			AcquisitionGold = 0;//ȹ���差
	_float			TempBestClear = 0.f;	//�ְ� ����� ��� ����

	_bool			m_bSetupGenerate = false; //1ȸ�� ���ؼ� ������


	_float			TempY = 0;
	_float			StartPosY = 0;
	_float			TargetPosY = 0;
	_float			EasingTime = 0;

	_bool			EasingSwitch = false;


	_bool			SoundSwitch = false;

	////////////////////////
	_uint			m_iOldFrameTexture = 0;
	_bool			m_bFrameTexture = true;

	_bool			m_bParticle_Switch = false;

public:
	static CUI_Result* Create(LPDIRECT3DDEVICE9 pGraphicDevice, void* pArg = nullptr);
	virtual CGameObject* Clone(void* pArg = nullptr)override;
	virtual void Free()override;
};

END