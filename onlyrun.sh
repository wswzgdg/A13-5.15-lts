#工具链
export PATH=/usr/lib/llvm-23/bin/:$PATH

#export PATH=/root/clang+llvm-19.1.0-aarch64-linux-gnu/bin:$PATH


#export PATH=/root/clang+llvm-11.0.0-aarch64-linux-gnu/bin:$PATH


#export PATH=/root/electron-clang-12.0.1/bin:$PATH


#export PATH=/root/clang+llvm-13.0.0-aarch64-linux-gnu/bin:$PATH

#验证版本
clang -v
clang++ -v
git -v



# 禁用 Git 信息
touch .scmversion

# 确保 EXTRAVERSION 为空
sed -i 's/^EXTRAVERSION =.*/EXTRAVERSION =/' Makefile


#echo CONFIG_LOCALVERSION=\"-Corona\" >> arch/arm64/configs/gki_defconfig


#线程
#export KMI_GENERATION=8
#export STOP_SHIP_TRACEPRINTK=1

#用户主机名
export KBUILD_BUILD_USER=ZakoBai♡
export KBUILD_BUILD_HOST=XinRan

#构建时间
#export KBUILD_BUILD_TIMESTAMP="Mon Sep 16 14:52:44 UTC 2024"


#生成配置文件
make LLVM=1 LLVM_IAS=1 ARCH=arm64 CC="ccache clang" HOSTCC="ccache clang" HOSTCXX="ccache clang++" PYTHON=python3 O=out gki_defconfig



#构建           
make LLVM=1 LLVM_IAS=1 ARCH=arm64 CC="ccache clang" HOSTCC="ccache clang" HOSTCXX="ccache clang++" PYTHON=python3 O=out KCFLAGS=-Wno-error -j$(nproc --all)

