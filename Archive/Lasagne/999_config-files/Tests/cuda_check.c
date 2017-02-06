#include <stdio.h>
#include <cuda.h>
#include <cuda_runtime_api.h>

/* Outputs some information on CUDA-enabled devices on your computer,
 * including compute capability and current memory usage.
 *
 * On Linux, compile with: nvcc -o cuda_check cuda_check.c -lcuda
 * On Windows, compile with: nvcc -o cuda_check.exe cuda_check.c -lcuda
 *
 * Authors: Thomas Unterthiner, Jan Schlüter
 */

int ConvertSMVer2Cores(int major, int minor)
{
	// Returns the number of CUDA cores per multiprocessor for a given
	// Compute Capability version. There is no way to retrieve that via
	// the API, so it needs to be hard-coded.
	switch ((major << 4) + minor) {
		case 0x10: return 8;
		case 0x11: return 8;
		case 0x12: return 8;
		case 0x13: return 8;
		case 0x20: return 32;
		case 0x21: return 48;
		default: return 192;  // 3.0 and above
	}
}

int main()
{
	int nGpus;
	int i;
	char name[100];
	int cc_major, cc_minor, cores, threads_per_core, clockrate;
	size_t freeMem;
	size_t totalMem;

	CUresult result;
	CUdevice device;
	CUcontext context;

	result = cuInit(0);
	if (result != CUDA_SUCCESS) {
		printf("cuInit failed with error code %d: %s\n", result, cudaGetErrorString(result));
		return 1;
	}
	result = cuDeviceGetCount(&nGpus);
	if (result != CUDA_SUCCESS) {
		printf("cuDeviceGetCount failed with error code %d: %s\n", result, cudaGetErrorString(result));
		return 1;
	}
	printf("Found %d device(s).\n", nGpus);
	for (i = 0; i < nGpus; i++) {
		cuDeviceGet(&device, i);
		printf("Device: %d\n", i);
		if (cuDeviceGetName(&name[0], sizeof(name), device) == CUDA_SUCCESS) {
			printf("  Name: %s\n", &name[0]);
		}
		if (cuDeviceComputeCapability(&cc_major, &cc_minor, device) == CUDA_SUCCESS) {
			printf("  Compute Capability: %d.%d\n", cc_major, cc_minor);
		}
		if (cuDeviceGetAttribute(&cores, CU_DEVICE_ATTRIBUTE_MULTIPROCESSOR_COUNT, device) == CUDA_SUCCESS) {
			printf("  Multiprocessors: %d\n", cores);
			if (cuDeviceComputeCapability(&cc_major, &cc_minor, device) == CUDA_SUCCESS) {
				printf("  CUDA Cores: %d\n", cores * ConvertSMVer2Cores(cc_major, cc_minor));
			}
			if (cuDeviceGetAttribute(&threads_per_core, CU_DEVICE_ATTRIBUTE_MAX_THREADS_PER_MULTIPROCESSOR, device) == CUDA_SUCCESS) {
				printf("  Concurrent threads: %d\n", cores*threads_per_core);
			}
		}
		if (cuDeviceGetAttribute(&clockrate, CU_DEVICE_ATTRIBUTE_CLOCK_RATE, device) == CUDA_SUCCESS) {
			printf("  GPU clock: %g MHz\n", clockrate/1000.);
		}
		if (cuDeviceGetAttribute(&clockrate, CU_DEVICE_ATTRIBUTE_MEMORY_CLOCK_RATE, device) == CUDA_SUCCESS) {
			printf("  Memory clock: %g MHz\n", clockrate/1000.);
		}
		cuCtxCreate(&context, 0, device);
		result = cuMemGetInfo(&freeMem, &totalMem);
		if (result == CUDA_SUCCESS ) {
			printf("  Total Memory: %ld MiB\n  Free Memory: %ld MiB\n", totalMem / ( 1024 * 1024 ), freeMem / ( 1024 * 1024 ));
		} else {
			printf("  cMemGetInfo failed with error code %d: %s\n", result, cudaGetErrorString(result));
		}
		cuCtxDetach(context);
	}
	return 0;
}