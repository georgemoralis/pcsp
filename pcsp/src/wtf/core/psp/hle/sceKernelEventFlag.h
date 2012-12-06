#pragma once

namespace hle
{
	void HLEDECL sceKernelCreateEventFlag(AlContext &context);
	void HLEDECL sceKernelClearEventFlag(AlContext &context);
	void HLEDECL sceKernelDeleteEventFlag(AlContext &context);
	void HLEDECL sceKernelSetEventFlag(AlContext &context);
	void HLEDECL sceKernelWaitEventFlag(AlContext &context);
	void HLEDECL sceKernelWaitEventFlagCB(AlContext &context);
	void HLEDECL sceKernelPollEventFlag(AlContext &context);
	void HLEDECL sceKernelCancelEventFlag(AlContext &context);
	void HLEDECL sceKernelReferEventFlagStatus(AlContext &context);
}

