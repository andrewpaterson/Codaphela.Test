#include "StandardLib/Pointer.h"
#include "StandardLib/NamedObject.h"
#include "StandardLib/ArrayObject.h"


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
CONSTRUCTABLE(CPlayerVehicle);
protected:
	CGraphicPicture		mcPicture;
	SPhysicsPoint*		mpsPoint;

	SStateOnKill*		mpsBeforeDeath;
	SStateOnKill*		mpsAfterDeath;

public:
			Ptr<CPlayerVehicle>	Init(void);
			void				Class(void);
			void				KillData(void);

			BOOL				Save(CObjectSerialiser* pcFile) { return FALSE; };
			BOOL				Load(CObjectDeserialiser* pcFile) { return FALSE; };

			void				SetKillHook(SStateOnKill* psBeforeDeath, SStateOnKill* psAfterDeath);

	virtual void				PlayerInput(void) =0;
};


class CHarrier : public CPlayerVehicle
{
CONSTRUCTABLE(CHarrier);
protected:
	Ptr<CArrayObject>	maMissiles;
	Ptr<CGameWorld>		mpWorld;
	int					miSpeed;

public:
	Ptr<CHarrier>		Init(Ptr<CGameWorld> pWorld);
	void				Class(void);
	void				KillData(void);

	BOOL				Save(CObjectSerialiser* pcFile) { return FALSE; };
	BOOL				Load(CObjectDeserialiser* pcFile) { return FALSE; };

	void				PlayerInput(void) {};
	Ptr<CMissile>		FireMissile(CPointer& pTarget);
	Ptr<CArrayObject>	GetMissiles(void);
};


class CJeep : public CPlayerVehicle
{
CONSTRUCTABLE(CJeep);
protected:
	Ptr<CGameWorld>		mpWorld;
	float				mfFrontWheel;
	float				mfBackWheel;

public:
	Ptr<CJeep>	Init(Ptr<CGameWorld> pWorld);
	void		Class(void);
	void		KillData(void);

	BOOL		Save(CObjectSerialiser* pcFile) { return FALSE; };
	BOOL		Load(CObjectDeserialiser* pcFile) { return FALSE; };

	void		PlayerInput(void) {};
};


class CRedJet : public CNamedObject
{
CONSTRUCTABLE(CRedJet);
protected:
	CGraphicPicture		mcPicture;
	Ptr<CGameWorld>		mpWorld;
	SPhysicsPoint*		mpsPoint;

	SStateOnKill*		mpsBeforeDeath;
	SStateOnKill*		mpsAfterDeath;

public:
	Ptr<CRedJet>	Init(Ptr<CGameWorld> pWorld);
	void			Class(void);
	void			KillData(void);

	BOOL			Save(CObjectSerialiser* pcFile) { return FALSE; };
	BOOL			Load(CObjectDeserialiser* pcFile) { return FALSE; };

	void			SetKillHook(SStateOnKill* psBeforeDeath, SStateOnKill* psAfterDeath);
};


class CMissile : public CObject
{
CONSTRUCTABLE(CMissile);
protected:
	Ptr<CGameWorld>		mpWorld;
	CPointer			mpTarget;
	char*				mszKillState;

public:
	Ptr<CMissile>	Init(Ptr<CGameWorld> pWorld);
	void			Class(void);
	void			KillData(void);

	BOOL			Save(CObjectSerialiser* pcFile);
	BOOL			Load(CObjectDeserialiser* pcFile);

	void			SetTarget(CPointer& pTarget);
	CPointer		GetTarget(void);

	void			SetKillString(char* szKillString);
};


class CClusterMissile : public CNamedObject
{
CONSTRUCTABLE(CClusterMissile);
public:
	CMissile			mcMissile1;
	CMissile			mcMissile2;
protected:
	Ptr<CGameWorld>		mpWorld;
	char*				mszKillState;

public:
	Ptr<CClusterMissile> 	Init(Ptr<CGameWorld> pWorld);
	void					Class(void);
	void					KillData(void);

	BOOL					Save(CObjectSerialiser* pcFile);
	BOOL					Load(CObjectDeserialiser* pcFile);

	void					SetKillString(char* szKillString);
};


class CClusterLauncher : public CObject
{
CONSTRUCTABLE(CClusterLauncher);
public:
	Ptr<CClusterMissile>	mpMissile;

	Ptr<CClusterLauncher> 	Init(void);
	void					Class(void);
	void					KillData(void);

	BOOL					Save(CObjectSerialiser* pcFile) { return FALSE; };
	BOOL					Load(CObjectDeserialiser* pcFile) { return FALSE; };
};


class CGameWorld : public CObject
{
CONSTRUCTABLE(CGameWorld);
protected:
	Ptr<CArrayObject>	maTickables;
	Ptr<CPlayerVehicle>	mpPlayer1;
	Ptr<CPlayerVehicle>	mpPlayer2;

public:
	Ptr<CGameWorld>		Init(void);
	void				Class(void);
	void				KillData(void);

	BOOL				Save(CObjectSerialiser* pcFile);
	BOOL				Load(CObjectDeserialiser* pcFile);

	void				Tick(void);
	void				AddPlayer(Ptr<CPlayerVehicle> pPlayer);
	void				AddTickable(CPointer& pTickable);
	void				RemoveTickable(CPointer& pTickable);
	Ptr<CArrayObject>	GetTickables(void);
};

