# KJEditor
基于vcglib的Editor


## 依赖
你需要通过vcpkg安装osg、qt5和spdlog
```bash
vcpkg install osg:x64-windows qt5:x64-windows spdlog:x64-windows
```

## 构建方法
```bash
cd KJEditor

mkdir build

cd build 

cmake ..

cmake --build ./ --config Release --target GU -j 10
```