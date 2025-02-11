#include "HookHelper.h"
#include "SDK/Base/VMT.h"

// these hooks are removed when not in-game
#define HOOKFUNC_INGAME(func) HOOKFUNC(func); hooks.insert(func);

void Hooks::SetUpByteHooks() {
	HOOKFUNC_SIGNATURES(PrepareUnitOrders);
	HOOKFUNC_SIGNATURES(BIsEmoticonUnlocked);
	HOOKFUNC_SIGNATURES(DispatchPacket);
	HOOKFUNC_SIGNATURES(BAsyncSendProto);
	HOOKFUNC_SIGNATURES(SaveSerializedSOCache);
	//HOOKFUNC_SIGNATURES(CGameUI__ChangeGameUIState);
}


void Hooks::SetUpVirtualHooks(bool log) {
	HookSteamGC();
	SigScanContext ssctx{ ctx.CurProcHandle, ctx.CurProcId };
	{
		// NetChan constructor
		// vtable ptr at 0x15
		uintptr_t** vtable = ssctx.Scan("40 53 56 57 41 56 48 83 EC ?? 45 33 F6 48 8D 71", L"networksystem.dll").Offset(0x15).GetAbsoluteAddress(3, 7);
		uintptr_t* PostReceivedNetMessage = vtable[86], * SendNetMessage = vtable[69]; // bytehooking through vtables, how's that, Elon Musk?
		HOOKFUNC_INGAME(PostReceivedNetMessage);
		HOOKFUNC_INGAME(SendNetMessage);
	}
	{
		// CDOTA_Buff destructor
		// vtable ptr at 0xd
		auto OnRemoveModifier = ssctx.Scan("4C 8B DC 56 41 57", L"client.dll");
		uintptr_t** vtable = OnRemoveModifier.Offset(0xd).GetAbsoluteAddress(3, 7);
		uintptr_t* OnAddModifier = vtable[39];
		HOOKFUNC(OnAddModifier);
		HOOKFUNC(OnRemoveModifier);
	}
	{
		// xref: "CParticleCollection::~CParticleCollection [%p]\n"
		auto particleDestructor = ssctx.Scan("E8 ? ? ? ? 40 F6 C7 01 74 34", L"particles.dll")
			.GetAbsoluteAddress(1, 5);
		uintptr_t** vtable = particleDestructor
			.Offset(0x19)
			.GetAbsoluteAddress(3, 7);
		auto SetRenderingEnabled = vtable[95];
		HOOKFUNC(SetRenderingEnabled);
	}
	{
		auto vmt = VMT(Interfaces::EntitySystem);
		void* OnAddEntity = vmt.GetVM<EntSystemEvent>(14), * OnRemoveEntity = vmt.GetVM<EntSystemEvent>(15);
		HOOKFUNC(OnAddEntity);
		HOOKFUNC(OnRemoveEntity);
	}
	{
		void* RunScript = Interfaces::UIEngine->GetVFunc(88).ptr,
			* RunFrame = Interfaces::UIEngine->GetVFunc(6).ptr;
		HOOKFUNC(RunFrame);
		HOOKFUNC(RunScript);
	}
}

void Hooks::DisableHooks() {
	for (auto hook : hooks)
		MH_DisableHook(hook);
}

void Hooks::EnableHooks() {
	for (auto hook : hooks)
		MH_EnableHook(hook);
}
