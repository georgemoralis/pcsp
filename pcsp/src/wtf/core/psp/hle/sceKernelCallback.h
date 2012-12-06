#pragma once

namespace hle
{
	void sceKernelCreateCallback(AlContext &context);
	void sceKernelCheckCallback(AlContext &context);
	void sceKernelDeleteCallback(AlContext &context);
	void sceKernelNotifyCallback(AlContext &context);
	void _sceKernelReturnFromCallback(AlContext &context);
}

