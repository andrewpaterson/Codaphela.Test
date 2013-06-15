#include "StandardLib/Pointer.h"
#include "StandardLib/NamedObject.h"
#include "StandardLib/Array.h"


class CMissile;
class CGameWorld;


class CGraphicPicture
{
public:
	char	mszPretenedImAPicture[16];

	void Init(void);
	void Kill(void);
};


struct SPhysicsPoint
{
	int		x;
	int		y;
	int		z;
};


struct SStateOnKill
{
	SPhysicsPoint		sPoint;
	CGraphicPicture		cPicture;
};


class CPlayerVehicle : public CNamedObject
{
BASE_FUNCTIONS(CPlayerVehicle);
protected:
	CGraphicPicture			mcPicture;
	SPhysicsPoint*			mpsPoint;

	SStateOnKill*		mpsBeforeDeath;
	SStateOnKill*		mpsAfterDeath;

public:
			void Init(void);
			void KillData(void);

			BOOL Save(CObjectSerialiser* pcFile) { return FALSE; };
			BOOL Load(CObjectDeserialiser* pcFile) { return FALSE; };

			void SetKillHook(SStateOnKill* psBeforeDeath, SStateOnKill* psAfterDeath);

	virtual void PlayerInput(void) =0;
};


class CHarrier : public CPlayerVehicle
{
BASE_FUNCTIONS(CHarrier);
protected:
	CPointer<CArray>		maMissiles;
	CPointer<CGameWorld>	mpWorld;
	int						miSpeed;

public:
	void					Init(CPointer<CGameWorld> pWorld);
	void					KillData(void);

	BOOL					Save(CObjectSerialiser* pcFile) { return FALSE; };
	BOOL					Load(CObjectDeserialiser* pcFile) { return FALSE; };

	void					PlayerInput(void) {};
	CPointer<CMissile>		FireMissile(CPointerObject pTarget);
	CPointer<CArray>		GetMissiles(void);
};


class CJeep : public CPlayerVehicle
{
BASE_FUNCTIONS(CJeep);
protected:
	CPointer<CGameWorld>	mpWorld;
	float					mfFrontWheel;
	float					mfBackWheel;

public:
	void Init(CPointer<CGameWorld> pWorld);
	void KillData(void);

	BOOL Save(CObjectSerialiser* pcFile) { return FALSE; };
	BOOL Load(CObjectDeserialiser* pcFile) { return FALSE; };

	void PlayerInput(void) {};
};


class CRedJet : public CNamedObject
{
BASE_FUNCTIONS(CRedJet);
protected:
	CGraphicPicture			mcPicture;
	CPointer<CGameWorld>	mpWorld;
	SPhysicsPoint*			mpsPoint;

	SStateOnKill*			mpsBeforeDeath;
	SStateOnKill*			mpsAfterDeath;

public:
	void Init(CPointer<CGameWorld> pWorld);
	void KillData(void);

	BOOL Save(CObjectSerialiser* pcFile) { return FALSE; };
	BOOL Load(CObjectDeserialiser* pcFile) { return FALSE; };

	void SetKillHook(SStateOnKill* psBeforeDeath, SStateOnKill* psAfterDeath);
};


class CMissile : public CObject
{
BASE_FUNCTIONS(CMissile);
protected:
	CPointer<CGameWorld>	mpWorld;
	CPointerObject			mpTarget;  

public:
	void				Init(CPointer<CGameWorld> pWorld);
	void				KillData(void);

	BOOL				Save(CObjectSerialiser* pcFile) { return FALSE; };
	BOOL				Load(CObjectDeserialiser* pcFile) { return FALSE; };

	void				SetTarget(CPointerObject pTarget);
	CPointerObject		GetTarget(void);
};


class CGameWorld : public CObject
{
BASE_FUNCTIONS(CGameWorld);
protected:
	CPointer<CArray>			maTickables;
	CPointer<CPlayerVehicle>	mpPlayer1;
	CPointer<CPlayerVehicle>	mpPlayer2;

public:
	void Init(void);
	void KillData(void);

	BOOL Save(CObjectSerialiser* pcFile) { return FALSE; };
	BOOL Load(CObjectDeserialiser* pcFile) { return FALSE; };

	void Tick(void);
	void AddPlayer(CPointer<CPlayerVehicle> pPlayer);
	void AddTickable(CPointerObject pTickable);
};

