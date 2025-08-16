![GitHub License](https://img.shields.io/github/license/LesBoys43/libeventemitter?style=for-the-badge)
![GitHub Actions Workflow Status](https://img.shields.io/github/actions/workflow/status/LesBoys43/libeventemitter/AutoMaster.yaml?style=for-the-badge)
![GitHub Actions Workflow Status](https://img.shields.io/github/actions/workflow/status/LesBoys43/libeventemitter/ExecuteUnits.yaml?style=for-the-badge&label=test)
![GitHub Actions Workflow Status](https://img.shields.io/github/actions/workflow/status/LesBoys43/libeventemitter/QuickFormat.yaml?style=for-the-badge&label=format)
![GitHub Release](https://img.shields.io/github/v/release/LesBoys43/libeventemitter?include_prereleases&style=for-the-badge)


**libeventemitter** 是一款轻量级，非线程安全，事件驱动的 C 语言事件发射器库，参照了 JavaScript 的 EventEmitter 和本人之前的 PyEventEmitter 开发。

# 依赖
meson 是构建时依赖。
glib 是运行时依赖。

# 安装
克隆仓库后，如果你是小白，请根据以下指引安装：
```bash
chmod +x BriskMakeAll.sh # 确保可执行
./BriskMakeAll.sh # 自动编译
```

如果你是专家且希望自定义配置，请按照以下方法安装：
```bash
meson setup build --prefix="此处可以设置prefix"
meson compile -C build # 也可以用 ./make_libeventemitter.sh [额外make参数]
meson install -C build
```

# 文档
## 手册
请参见 MANUAL.md，查看简明手册。

## 详细文档
### 安装文档（依赖 pandoc）
```shell
make -f DOCS.make install WITHYELP=[如果你有yelp 设置为1 否则0] WITHMAN=1 WITHMD=[如果你希望安装到家目录markdown文档 设置为1 否则0]
```