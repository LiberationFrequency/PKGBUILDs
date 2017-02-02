Ohne CUDA, weil meine GPU mit der aktuellen Version nicht mehr untestützt wird, der gcc 6.x anscheinend nicht unterstützt wird, 
ich keinen propritären Nvidia-Treiber installieren möchte, das Ganze über 2 GB groß ist, 
und ich es erst mal nur testen möchte.    
Das wären mir zu große Änderungen.  

Das ist nicht vollständig, ich hatte schon eine Menge Abhängigkeiten installiert.  


offizielle Pakete:
* python2-setuptools  
* python2-sympy  
* python-setuptools  
* python-sympy  
 


Die numpy Version müssen/sollten auf 1.12.0 geändert werden.    
* https://aur.archlinux.org/packages/openblas-lapack/    
* https://aur.archlinux.org/packages/python2-numpy-openblas/  
* https://aur.archlinux.org/packages/python-numpy-openblas  
* https://aur.archlinux.org/packages/python-scipy-openblas/  
* "export OPENBLAS_NUM_THREADS=1" before giving "makepkg -s"  


CUDA (empfohlen)  


https://aur.archlinux.org/packages/python-theano/  



Lasagne:  
mein PKGBUILD    


 
CUDA für meine alte Grafikkarte: 
----------------------------------------------------------------------- 
Herunterladen, pacman -U ..., danach /etc/pacman.conf IgnorePkg = cuda  
https://archive.archlinux.org/packages/c/cuda/cuda-6.5.19-1-x86_64.pkg.tar.xz    
https://archive.archlinux.org/packages/c/cuda/cuda-6.5.19-1-x86_64.pkg.tar.xz.sig  
  
https://www.archlinux.org/packages/community/x86_64/python-pycuda/ ???  
  
https://aur.archlinux.org/packages/libgpuarray-git/  
  
pygpu  

  

Nachlesen:  
---------------------------------------------------------  
http://lasagne.readthedocs.io/en/latest/user/installation.html  
http://deeplearning.net/software/theano/install.html#linux  
https://groups.google.com/forum/#!msg/theano-dev/-8WCMn2FMR0/bJPasoZXaqoJ  
http://osdf.github.io/blog/numpyscipy-with-openblas-for-ubuntu-1204-second-try.html  




