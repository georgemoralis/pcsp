#pragma once

namespace hle
{

	void HLEDECL sceKernelCancelSema(AlContext &context);
	void HLEDECL sceKernelCreateSema(AlContext &context);
	void HLEDECL sceKernelDeleteSema(AlContext &context);
	void HLEDECL sceKernelPollSema(AlContext &context);
	void HLEDECL sceKernelReferSemaStatus(AlContext &context);
	void HLEDECL sceKernelSignalSema(AlContext &context);
	void HLEDECL sceKernelWaitSema(AlContext &context);
	void HLEDECL sceKernelWaitSemaCB(AlContext &context);

}

