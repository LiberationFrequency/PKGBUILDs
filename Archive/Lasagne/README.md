# Install Lasagne Test on an old Lenovo B550   


offizielle Pakete:  
python2-setuptools  
python2-sympy  
python-setuptools  
python-sympy  
 

----------------------------
Die numpy Version müssen/sollten auf 1.12.0 geändert werden.    

https://aur.archlinux.org/packages/openblas-lapack/    
https://aur.archlinux.org/packages/python2-numpy-openblas/  
https://aur.archlinux.org/packages/python-numpy-openblas  
https://aur.archlinux.org/packages/python-scipy-openblas/  
* "export OPENBLAS_NUM_THREADS=1" before giving "makepkg -s"  




Install propritary nvidia-driver:  

% sudo pacman -S nvidia-340xx nvidia-340xx-libgl      
% sudo nvidia-xconfig  
% sudo nano /etc/default/grub   
* GRUB_CMDLINE_LINUX_DEFAULT="resume=/dev/sda2 nomodeset"    
% sudo grub-mkconfig -o /boot/grub/grub.cfg  
% systemctl reboot    
  
    % lspci -nnk | grep -i vga -A3  
    01:00.0 VGA compatible controller [0300]: NVIDIA Corporation GT218M [GeForce G210M] [10de:0a74] (rev a2)  
	Subsystem: Lenovo Device [17aa:389f]  
	Kernel driver in use: nvidia  
	Kernel modules: nouveau, nvidia    

    % lsmod  
    is the kernel modul nvidia-uvm loaded?      
    %  sudo modprobe nvidia-uvm  
  

https://aur.archlinux.org/packages/gcc49/  

sudo pacman -S opencl-nvidia-340xx  
sudo pacman -S opencl-headers  ???   
 
https://aur.archlinux.org/packages/cuda65/  
* my cuda65 PKGBUILD    
  
sudo pacman -S python-pycuda    
sudo pacman -S python2-pycuda    
  
https://aur.archlinux.org/packages/libgpuarray-git/      
  
sudo pacman -S python-pyopencl  
sudo pacman -S python2-pyopencl  
  
https://aur.archlinux.org/packages/python-pygpu/  
* my PKGBUILD and disable check   
  
https://aur.archlinux.org/packages/python-theano/  

https://aur.archlinux.org/packages/pygpu2-git/  ???? not installed  

Lasagne:  
* my PKGBUILD and disable check  
      

 
   


  

Add this to the end of your ~/.zprofile file.    

    export PATH=/opt/cuda/bin:"$PATH"  
    export LD_LIBRARY_PATH=/usr/lib64:"$LD_LIBRARY_PATH"   
  

create a ~/.theanorc file and add:  
  
    [global]
    mode=FAST_RUN
    device = gpu
    floatX = float32
    #optimizer = fast_compile
    #optimizer = None
    #exception_verbosity = high
    allow_gc = False

    [blas]
    python ldflags = -L/usr/lib64 -lopenblas

    [cuda]
    root = /opt/cuda

    #[lib]
    #cnmem = 1

    [nvcc]
    compiler_bindir = /opt/cuda/bin
    fastmath = true
    #flags=-arch=sm_12
    flags=-D_FORCE_INLINES -arch=sm_12


Purge theamo cache, if .theanorc is changed:    
% theano-cache purge   
    

.../src/Theano-0.8.2/theano/misc % python check_blas.py   

    Using gpu device 0: GeForce G210M (CNMeM is disabled, cuDNN not available)  
   
    [...]  

    Some Theano flags:
        blas.ldflags= -L/usr/lib64 -lopenblas -lopenblas
        compiledir= /home/che3po/.theano/compiledir_Linux-4.9--ARCH-x86_64-with-arch--3.6.0-64
        floatX= float32
       device= gpu
    Some OS information:
        sys.platform= linux
        sys.version= 3.6.0 (default, Jan 16 2017, 12:12:55) 
    [GCC 6.3.1 20170109]
        sys.prefix= /usr
    Some environment variables:
        MKL_NUM_THREADS= None
        OMP_NUM_THREADS= None
        GOTO_NUM_THREADS= None
  
    Numpy config: (used when the Theano flag "blas.ldflags" is empty)
    blas_mkl_info:
      NOT AVAILABLE
    blis_info:
      NOT AVAILABLE
    openblas_info:
        libraries = ['openblas', 'openblas']
        library_dirs = ['/usr/lib64']
        language = c
        define_macros = [('HAVE_CBLAS', None)]
    blas_opt_info:
        libraries = ['openblas', 'openblas']
        library_dirs = ['/usr/lib64']
        language = c
        define_macros = [('HAVE_CBLAS', None)]
    lapack_mkl_info:
      NOT AVAILABLE
    openblas_lapack_info:
        libraries = ['openblas', 'openblas']
        library_dirs = ['/usr/lib64']
        language = c
        define_macros = [('HAVE_CBLAS', None)]
    lapack_opt_info:
        libraries = ['openblas', 'openblas']
        library_dirs = ['/usr/lib64']
        language = c
        define_macros = [('HAVE_CBLAS', None)]
    Numpy dot module: numpy.core.multiarray
    Numpy location: /usr/lib/python3.6/site-packages/numpy/__init__.py
    Numpy version: 1.12.0
    nvcc version:
    nvcc: NVIDIA (R) Cuda compiler driver
    Copyright (c) 2005-2014 NVIDIA Corporation
    Built on Wed_Aug_27_10:36:36_CDT_2014
    Cuda compilation tools, release 6.5, V6.5.16
   
  
       We executed 10 calls to gemm with a and b matrices of shapes (5000, 5000) and (5000, 5000).

       Total execution time: 7.32s on GPU.

    for comparison ... 
  
    a second run:  
    Total execution time: 10.92s on GPU.  
  
    three runs with optimizer = None:  
    Total execution time: 39.81s on GPU.    
    Total execution time: 41.35s on GPU.  
    Total execution time: 44.01s on GPU.  




    same on CPU (note the missing part above) ...  

      We executed 10 calls to gemm with a and b matrices of shapes (5000, 5000) and (5000, 5000).

      Total execution time: 223.98s on CPU (with direct Theano binding to blas).



Test without errors: .../src/python-lasagne/examples % python mnist.py mlp 5  

    Using gpu device 0: GeForce G210M (CNMeM is disabled, cuDNN not available)
    Loading data...
    Building model and compiling functions...
    Starting training...
    Epoch 1 of 5 took 22.280s
      training loss:                1.224885
      validation loss:              0.423956
      validation accuracy:          88.04 %
    Epoch 2 of 5 took 22.249s
      training loss:                0.573711
      validation loss:              0.311270
      validation accuracy:          90.85 %
    Epoch 3 of 5 took 22.252s
      training loss:                0.472108
      validation loss:              0.269416
     validation accuracy:          92.07 %
    Epoch 4 of 5 took 22.253s
      training loss:                0.417506
      validation loss:              0.238364
      validation accuracy:          92.98 %
    Epoch 5 of 5 took 22.254s
      training loss:                0.379962
      validation loss:              0.216625
      validation accuracy:          93.62 %
    Final results:
      test loss:                    0.229084
      test accuracy:                93.31 %
   python mnist.py mlp 5  188,47s user 105,59s system 98% cpu 4:57,09 total


.../999_config-files/Tests/cuda_check  
#################################  
Found 1 device(s).		#  
Device: 0			#  
  Name: GeForce G210M		#  
  Compute Capability: 1.2	#  
  Multiprocessors: 2		#   
  CUDA Cores: 16		#   
  Concurrent threads: 2048	#   
  GPU clock: 1468 MHz		#   
  Memory clock: 500 MHz		#   
  Total Memory: 511 MiB		#     
  Free Memory: 460 MiB		#   
#################################   


  

% python  
>>> import numpy as np    
>>> np.show_config()  


  
  
% python -c "import numpy; numpy.test(verbose=2)" > numpytest.txt   
% python -c "import scipy; scipy.test(verbose=2)" > scipytest.txt   
% python -c "import theano; theano.test()" > theanotest.txt





further Informationen:  
---------------------------------------------------------  
http://lasagne.readthedocs.io/en/latest/user/installation.html  
http://deeplearning.net/software/theano/install.html#linux  
https://github.com/Lasagne/Lasagne/wiki/From-Zero-to-Lasagne-on-Ubuntu-14.04  
https://groups.google.com/forum/#!msg/theano-dev/-8WCMn2FMR0/bJPasoZXaqoJ  
http://osdf.github.io/blog/numpyscipy-with-openblas-for-ubuntu-1204-second-try.html  



