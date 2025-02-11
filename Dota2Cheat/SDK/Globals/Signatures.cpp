#include "Signatures.h"

#ifdef _DEBUG
#define SCAN_FUNC(var, scan) var = (scan); std::cout << #var << ": " << var << '\n';
#else
#define SCAN_FUNC(var, scan) var = scan;
#endif

void Signatures::FindSignatures(bool log) {
	CMsg = reinterpret_cast<decltype(CMsg)>(GetProcAddress(GetModuleHandleA("tier0.dll"), "Msg"));
	CMsgColor = reinterpret_cast<decltype(CMsgColor)>(GetProcAddress(GetModuleHandleA("tier0.dll"), "?ConColorMsg@@YAXAEBVColor@@PEBDZZ"));

	SigScanContext ssctx(ctx.CurProcHandle, ctx.CurProcId);
	if (log)
		std::cout << "[SIGNATURES]\n";

	//xref: "<BAD GAMEUI STATE>"
	//you can see messages about UI state in console when switching between game/menu/loading screen
	// SCAN_FUNC(CGameUI__ChangeGameUIState, ssctx.Scan("E8 ? ? ? ? 48 8B 5C 24 ? C6 86", L"client.dll").GetAbsoluteAddress(1, 5));

	SCAN_FUNC(GetPlayer, ssctx.Scan("33 C0 83 F9 FF", L"client.dll"));

	// xref "particles/ui_mouseactions/waypoint_flag.vpcf"
	// The one with the bigger offset from function
	SCAN_FUNC(PrepareUnitOrders, ssctx.Scan("E8 ? ? ? ? 49 8B CF FF C5", L"client.dll").GetAbsoluteAddress(1, 5));

	// Xref DestroyParticleEffect to a lea rcx just behind the string
	// It's offset by 9 bytes because it checks for an invalid handle before doing the initial mov
	SCAN_FUNC(CDOTAParticleManager::DestroyParticleFunc, ssctx.Scan("E8 ? ? ? ? 48 83 C3 1C", L"client.dll").GetAbsoluteAddress(1, 5));

	// JS function
	SCAN_FUNC(CDOTAGameRules::GetGameTimeFunc, ssctx.Scan("E8 ? ? ? ? 8B 04 2E", L"client.dll").GetAbsoluteAddress(1, 5));

	// UnknownCheats wiki -> Dota 2 -> link to Using engine functions
	SCAN_FUNC(WorldToScreen, ssctx.Scan("E8 ? ? ? ? 83 7D B7 00", L"client.dll").GetAbsoluteAddress(1, 5));

	// xref: "BuildCacheSubscribed(CEconItem)"
	SCAN_FUNC(CreateEconItem, ssctx.Scan("48 83 EC ? B9 ? ? ? ? E8 ? ? ? ? 48 85 C0 74 ? 48 8D 0D", L"client.dll"));
	// Last call in JS func GetLevelSpecialValueFor for a method of CDOTABaseAbility
	SCAN_FUNC(CDOTABaseAbility::GetLevelSpecialValueForFunc, ssctx.Scan("E8 ? ? ? ? F3 0F 5A C0", L"client.dll").GetAbsoluteAddress(1, 5));
	// Second call inside that ^
	SCAN_FUNC(CDOTABaseAbility::GetKVEntry, Address(CDOTABaseAbility::GetLevelSpecialValueForFunc).Offset(0x33).GetAbsoluteAddress(1, 5));

	//xref: "You are #%d in line of %d waiting players.\n"
	SCAN_FUNC(DispatchPacket, ssctx.Scan("E8 ? ? ? ? 48 8B CF E8 ? ? ? ? B8", L"client.dll").GetAbsoluteAddress(1, 5));

	//xref: "CProtoBufMsg::BAsyncSendProto"
	SCAN_FUNC(BAsyncSendProto, ssctx.Scan("E8 ? ? ? ? 48 8B 4D 90 48 89 7C 24", L"client.dll").GetAbsoluteAddress(1, 5));
	SCAN_FUNC(GetItemSchema, ssctx.Scan("E8 ? ? ? ? 48 89 5D 18", L"client.dll").GetAbsoluteAddress(1, 5));
	SCAN_FUNC(CDOTAItemSchema::GetItemDefByIndex, ssctx.Scan("E8 ? ? ? ? 83 FE 05", L"client.dll").GetAbsoluteAddress(1, 5));
	SCAN_FUNC(CDOTAItemSchema::GetItemDefArrIdx, Address(CDOTAItemSchema::GetItemDefByIndex).Offset(0x16).GetAbsoluteAddress(1, 5));

	//xref: "RP: Setting %s's status to %s (%s).\n"
	SCAN_FUNC(CDOTARichPresence::SetRPStatusFunc, ssctx.Scan("4C 89 4C 24 20 55 53 57 41 54", L"client.dll"));

	//xref: "Failed to get custom game %llu timestamp/CRC!\n"
	SCAN_FUNC(CDOTAGCClientSystem__SendReadyUpMessageForCurrentLobby,
		ssctx.Scan("E8 ? ? ? ? 48 8B D7 48 8B CB E8 ? ? ? ? 48 8D 8B", L"client.dll")
		.GetAbsoluteAddress(1)
		.Offset(0x27E)
		.GetAbsoluteAddress(1));

	//xref: "cache_%u_%u.soc", closest to the beginning
	SCAN_FUNC(SaveSerializedSOCache, ssctx.Scan("4C 8B DC 57 48 81 EC ? ? ? ? 48 8B 05", L"client.dll"));

	//xref: "#DOTA_GlobalItems_Emoticons"
	//decompile in IDA
	//in the middle, 240 lines in is:
	// if(!sub_XXXXXXX(v34, v89)) goto LABEL_XX:
	SCAN_FUNC(BIsEmoticonUnlocked, ssctx.Scan("E8 ? ? ? ? 84 C0 0F 84 ? ? ? ? 48 8B 45 08", L"client.dll").GetAbsoluteAddress(1, 5));

	//xref "OnColorChanged", lea rax, [XXXXXXXXX] below it
	SCAN_FUNC(CBaseEntity::OnColorChanged, ssctx.Scan("40 53 48 83 EC 20 48 8B D9 48 8B 89 ? ? ? ? 48 8B 01 0F B6 93", L"client.dll"));

	// LoadUITexture = ssctx.Scan("57 48 83 EC 20 48 8B 1A 49 8B F0 48 8B FA 48 85 DB", L"panorama.dll").Offset(-10);
}
