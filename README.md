Attempt to create a minimal EDK2 for some MSM8226 Samsung devices

## Status
Boots to EFI shell, eMMC is working, the memory map is from WP target, ACPI from Lumia 830.

## Building
Tested on Ubuntu 24.04.

First, clone EDK2.

```
cd ..
git clone https://github.com/tianocore/edk2.git -b edk2-stable202302--recursive
git clone https://github.com/tianocore/edk2-platforms.git
```

You should have all three directories side by side.

Next, install dependencies:

20.04 or later:

```
sudo apt install build-essential uuid-dev iasl git nasm python3-distutils crossbuild-essential-armel
```

Also see [EDK2 website](https://github.com/tianocore/tianocore.github.io/wiki/Using-EDK-II-with-Native-GCC#Install_required_software_from_apt)

Then ./firstrun.sh

Finally, ./script/s3neo.sh, or ./s5mini-debug.sh if you are planning to test on the S5 Mini Duos with stock BL.

Then make a image using AIK (Android Image Kitchen) and make a tar to flash with Odin.

# Credits

based on edk2-msm8226 by sonic011gamer [edk2-msm8226](https://github.com/sonic011gamer/edk2-msm8226).

SimpleFbDxe screen driver is from imbushuo's [Lumia950XLPkg](https://github.com/WOA-Project/Lumia950XLPkg).

SmemDxe driver is from Dominduchami's [Lumia830Pkg](https://github.com/Dominduchami/Lumia830Pkg).

SmdRpmDxe driver is also from Dominduchami's [Lumia830Pkg](https://github.com/Dominduchami/Lumia830Pkg).

ButtonsDxe driver is from sonic011gamer's [Lumia650Pkg](https://github.com/sonic011gamer/Lumia650Pkg).

SmBiosTableDxe driver is also from Dominduchami's [Lumia830Pkg](https://github.com/Dominduchami/Lumia830Pkg).
