#pragma once

#include "Hooks/PrepareUnitOrders.h"
#include "Hooks/NetChannel.h"
#include "Hooks/ParticleRendering.h"
namespace Hooks {
	inline void SetUpByteHooks() {
		HookFunc(Signatures::PrepareUnitOrders, &hkPrepareUnitOrders, &oPrepareUnitOrders, "PrepareUnitOrders");
		HookFunc(Signatures::DispatchPacket, &hkDispatchPacket, &oDispatchPacket, "DispatchPacket");
		HookFunc(Signatures::BAsyncSendProto, &hkBAsyncSendProto, &oBAsyncSendProto, "BAsyncSendProto");
		HookFunc(Signatures::CreateParticleCollection, &hkCreateParticleCollection, &oCreateParticleCollection, "CreateParticleCollection");
	}

	inline void SetUpVirtualHooks() {
		VMTs::NetworkSystem = std::unique_ptr<VMT>(new VMT(Interfaces::NetworkSystem));
		VMTs::NetworkSystem->HookVM(CreateNetChannel, 26);
		VMTs::NetworkSystem->ApplyVMT();
	}
}
