# AgLib

AgLib is a Qt-based C++ library for development purposes of AiGaoSenDe Advanced Medical Technology Co., Ltd. (including Hyper-Spectral Images)

**Features:**

- Library of reading envi standard hyper-spectral images

**Contents:**

- [AgHyperImage](#aghyperimage)

<span id="aghyperimage">**AgHyperImage:**</span>

This module is designed to read and render hyper-spectral images, contains:

- abstract hyper image class

- envi standard hyper-spectral images for data type = 12 and interleave = bil

**Requirements:**

- [armadillo](http://arma.sourceforge.net/): C++ library for linear algebra & scientific computing

**Example:**

- AgHyperImage:
- - load image

```C++
AEnviHyperImage hyperImage;
hyperImage.load("/tmp/image001.raw"); // data
hyperImage.load("/tmp/image001.hdr"); // info
hyperImage.load("/tmp/image001.bmp"); // preview
```

- - image info

```c++
qDebug() << hyperImage.lines() << hyperImage.samples() << hyperImage.bands()
         << hyperImage.fileType()
         << hyperImage.dataType()
         << hyperImage.interLeave()
         << hyperImage.headerOffset()
         << hyperImage.binning()
         << hyperImage.wavelengthUnit();
arma::cout << hyperImage.wavelength().t() << arma::endl;

Output:
650 696 256 AAbstractHyperImage::FileType(ENVI) AAbstractHyperImage::DataType(UnsignedShort) AEnviHyperImage::InterLeave(Bil) 0 QPair(1,1) AAbstractHyperImage::WavelengthUnit(NanoMeter)

3.9250e+02   3.9480e+02   3.9700e+02   3.9930e+02   4.0160e+02   4.0380e+02   4.0610e+02   4.0840e+02   4.1060e+02   4.1290e+02   4.1520e+02   4.1740e+02   4.1970e+02   4.2200e+02   4.2430e+02   4.2660e+02   4.2890e+02   4.3110e+02   4.3340e+02   4.3570e+02   4.3800e+02   4.4030e+02   4.4260e+02   4.4490e+02   4.4720e+02   4.4950e+02   4.5180e+02   4.5410e+02   4.5640e+02   4.5870e+02   4.6100e+02   4.6340e+02   4.6570e+02   4.6800e+02   4.7030e+02   4.7260e+02   4.7490e+02   4.7730e+02   4.7960e+02   4.8190e+02   4.8430e+02   4.8660e+02   4.8890e+02   4.9130e+02   4.9360e+02   4.9590e+02   4.9830e+02   5.0060e+02   5.0300e+02   5.0530e+02   5.0770e+02   5.1000e+02   5.1240e+02   5.1470e+02   5.1710e+02   5.1940e+02   5.2180e+02   5.2410e+02   5.2650e+02   5.2890e+02   5.3120e+02   5.3360e+02   5.3600e+02   5.3840e+02   5.4070e+02   5.4310e+02   5.4550e+02   5.4790e+02   5.5020e+02   5.5260e+02   5.5500e+02   5.5740e+02   5.5980e+02   5.6220e+02   5.6460e+02   5.6700e+02   5.6940e+02   5.7180e+02   5.7420e+02   5.7660e+02   5.7900e+02   5.8140e+02   5.8380e+02   5.8620e+02   5.8860e+02   5.9100e+02   5.9340e+02   5.9590e+02   5.9830e+02   6.0070e+02   6.0310e+02   6.0550e+02   6.0800e+02   6.1040e+02   6.1280e+02   6.1530e+02   6.1770e+02   6.2010e+02   6.2260e+02   6.2500e+02   6.2740e+02   6.2990e+02   6.3230e+02   6.3480e+02   6.3720e+02   6.3970e+02   6.4210e+02   6.4460e+02   6.4700e+02   6.4950e+02   6.5200e+02   6.5440e+02   6.5690e+02   6.5930e+02   6.6180e+02   6.6430e+02   6.6680e+02   6.6920e+02   6.7170e+02   6.7420e+02   6.7670e+02   6.7910e+02   6.8160e+02   6.8410e+02   6.8660e+02   6.8910e+02   6.9160e+02   6.9410e+02   6.9650e+02   6.9900e+02   7.0150e+02   7.0400e+02   7.0650e+02   7.0900e+02   7.1150e+02   7.1410e+02   7.1660e+02   7.1910e+02   7.2160e+02   7.2410e+02   7.2660e+02   7.2910e+02   7.3160e+02   7.3420e+02   7.3670e+02   7.3920e+02   7.4170e+02   7.4430e+02   7.4680e+02   7.4930e+02   7.5190e+02   7.5440e+02   7.5690e+02   7.5950e+02   7.6200e+02   7.6460e+02   7.6710e+02   7.6970e+02   7.7220e+02   7.7480e+02   7.7730e+02   7.7990e+02   7.8240e+02   7.8500e+02   7.8750e+02   7.9010e+02   7.9270e+02   7.9520e+02   7.9780e+02   8.0040e+02   8.0290e+02   8.0550e+02   8.0810e+02   8.1070e+02   8.1320e+02   8.1580e+02   8.1840e+02   8.2100e+02   8.2360e+02   8.2620e+02   8.2870e+02   8.3130e+02   8.3390e+02   8.3650e+02   8.3910e+02   8.4170e+02   8.4430e+02   8.4690e+02   8.4950e+02   8.5210e+02   8.5470e+02   8.5740e+02   8.6000e+02   8.6260e+02   8.6520e+02   8.6780e+02   8.7040e+02   8.7310e+02   8.7570e+02   8.7830e+02   8.8090e+02   8.8360e+02   8.8620e+02   8.8880e+02   8.9150e+02   8.9410e+02   8.9670e+02   8.9940e+02   9.0200e+02   9.0470e+02   9.0730e+02   9.0990e+02   9.1260e+02   9.1520e+02   9.1790e+02   9.2060e+02   9.2320e+02   9.2590e+02   9.2850e+02   9.3120e+02   9.3390e+02   9.3650e+02   9.3920e+02   9.4190e+02   9.4450e+02   9.4720e+02   9.4990e+02   9.5260e+02   9.5520e+02   9.5790e+02   9.6060e+02   9.6330e+02   9.6600e+02   9.6870e+02   9.7130e+02   9.7400e+02   9.7670e+02   9.7940e+02   9.8210e+02   9.8480e+02   9.8750e+02   9.9020e+02   9.9290e+02   9.9560e+02   9.9830e+02   1.0011e+03   1.0038e+03   1.0065e+03   1.0092e+03   1.0119e+03   1.0146e+03   1.0174e+03   1.0201e+03   1.0228e+03   1.0255e+03   1.0283e+03
```

- - read spectrum

```c++
// spectrum at point(300, 300)
arma::vec spectrum = hyperImage.spectrum(300, 300)
arma::vec spectrum = hyperImage.spectrum(QPoint(300, 300));
// average spectrum in rectangle, topleft = (300, 300), width = 3, height = 4
arma::vec spectrum = hyperImage.spectrum(300, 300, 3, 4);
arma::vec spectrum = hyperImage.spectrum(QPoint(300, 300), QSize(3, 4));
    
spectrum of Point(300, 300), output in double:
0.0421   0.0524   0.0737   0.0951   0.1053   0.1194   0.1257   0.1254   0.1229   0.1212   0.1052   0.0883   0.0784   0.0697   0.0636   0.0558   0.0546   0.0516   0.0471   0.0538   0.0573   0.0659   0.0768   0.0925   0.1012   0.1205   0.1213   0.1237   0.1210   0.1271   0.1281   0.1371   0.1431   0.1537   0.1670   0.1702   0.1680   0.1709   0.1730   0.1747   0.1964   0.2105   0.2368   0.2626   0.2893   0.2900   0.2955   0.2800   0.2684   0.2618   0.2437   0.2283   0.2231   0.2183   0.2076   0.2017   0.1905   0.1899   0.1877   0.1768   0.1838   0.1779   0.1776   0.1765   0.1741   0.1772   0.1732   0.1745   0.1762   0.1796   0.1802   0.1787   0.1909   0.1852   0.1808   0.1907   0.1913   0.1940   0.1892   0.1989   0.1899   0.2006   0.2112   0.2206   0.2260   0.2330   0.2460   0.2627   0.2729   0.2852   0.2995   0.3199   0.3191   0.3260   0.3311   0.3499   0.3585   0.3603   0.3682   0.3680   0.3763   0.3798   0.3932   0.4025   0.3989   0.4076   0.4083   0.4221   0.4199   0.4192   0.4327   0.4399   0.4417   0.4430   0.4470   0.4443   0.4591   0.4576   0.4662   0.4607   0.4641   0.4705   0.4672   0.4915   0.4769   0.4821   0.4930   0.5020   0.4947   0.4898   0.5086   0.4965   0.4918   0.4962   0.4936   0.4994   0.4939   0.5021   0.4972   0.4915   0.4911   0.4844   0.4937   0.4867   0.4873   0.4746   0.4830   0.4784   0.4529   0.4736   0.4527   0.4406   0.4470   0.4379   0.4220   0.4177   0.4151   0.4213   0.4143   0.4092   0.4101   0.4015   0.3926   0.3945   0.3897   0.3843   0.3675   0.3737   0.3637   0.3577   0.3514   0.3455   0.3352   0.3331   0.3279   0.3190   0.3173   0.3173   0.3120   0.2949   0.2952   0.2895   0.2759   0.2762   0.2722   0.2726   0.2726   0.2578   0.2487   0.2518   0.2361   0.2394   0.2387   0.2274   0.2257   0.2220   0.2157   0.2077   0.2008   0.1981   0.1926   0.1911   0.1814   0.1806   0.1759   0.1732   0.1620   0.1553   0.1536   0.1508   0.1509   0.1395   0.1426   0.1317   0.1313   0.1328   0.1202   0.1166   0.1146   0.1075   0.1067   0.1027   0.1028   0.0926   0.0921   0.0927   0.0849   0.0828   0.0779   0.0770   0.0712   0.0671   0.0629   0.0647   0.0538   0.0533   0.0575   0.0537   0.0486   0.0497   0.0425   0.0436   0.0421   0.0416   0.0393   0.0404   0.0398   0.0367   0.0325   0.0330   0.0334   0.0291   0.0285   0.0265   0.0272   0.0258
```

- - render image

```c++
QImage image = hyperImage.image(125, 55, 25); // #band_red = 125, #band_green = 55, #band_green = 25
```

