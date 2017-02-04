# Install Lasagne Test    


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
    export LD_LIBRARY_PATH=/opt/cuda/lib64:"$LD_LIBRARY_PATH"  

create a ~/.theanorc file and add:  
  
    [global]  
    floatX = float32  
    #optimizer = fast_compile  
    optimizer = None  
    device = gpu  
    #exception_verbosity = high  
    #allow_gc = False  
  
    #[cuda]  
    #root = /opt/cuda  
     
    #[lib]  
    #cnmem = 1  
  
    [nvcc]  
    #compiler_bindir = /usr/bin  
    #fastmath = true  
    flags=-arch=sm_12  
    #flags=-D_FORCE_INLINES -arch=sm_12

  
  
    

Test failed: src/Theano-0.8.2/theano/misc % python check_blas.py   
* Total execution time: 229.72s on ERROR, unable to tell if Theano used the cpu or the gpu:  




Test without errors: .../src/python-lasagne/examples % python mnist.py mlp 5  

    Using gpu device 0: GeForce G210M (CNMeM is disabled, cuDNN not available)  
    Loading data...  
    Building model and compiling functions...  
    Starting training...  
    Epoch 1 of 5 took 42.481s  
      training loss:                1.213349  
      validation loss:              0.411466  
      validation accuracy:          88.47 %  
    Epoch 2 of 5 took 42.493s  
      training loss:                0.565136  
      validation loss:              0.308621  
      validation accuracy:          91.03 %  
    Epoch 3 of 5 took 42.660s  
      training loss:                0.467084  
      validation loss:              0.265284  
      validation accuracy:          92.22 %  
    Epoch 4 of 5 took 42.654s  
      training loss:                0.412077  
      validation loss:              0.236401   
      validation accuracy:          93.16 %   
    Epoch 5 of 5 took 42.627s  
      training loss:                0.374579  
      validation loss:              0.212768  
      validation accuracy:          93.83 %  
    Final results:    
      test loss:                    0.222602    
      test accuracy:                93.57 %    
    python mnist.py mlp 5  363,48s user 84,53s system 190% cpu 3:55,11 total    







  

further Informationen:  
---------------------------------------------------------  
http://lasagne.readthedocs.io/en/latest/user/installation.html  
http://deeplearning.net/software/theano/install.html#linux  
https://github.com/Lasagne/Lasagne/wiki/From-Zero-to-Lasagne-on-Ubuntu-14.04  
https://groups.google.com/forum/#!msg/theano-dev/-8WCMn2FMR0/bJPasoZXaqoJ  
http://osdf.github.io/blog/numpyscipy-with-openblas-for-ubuntu-1204-second-try.html  



