project('libeventemitter', 'c', version: '1.0', license: 'BSD-3', meson_version: '>=1.3.0')

glib = dependency('glib-2.0', required: true)

cc = meson.get_compiler('c')

cc.has_header('glib.h', dependencies: glib, required: true)

# 类型
types = [
  'GList', 
  'GQueue'
]

foreach type : types
  cc.has_type(type, dependencies: glib, prefix: '#include <glib.h>', required: true)
endforeach

# GHashTable 特殊处理
cc.has_header_symbol('glib.h', 'GHashTable', dependencies: glib, required: true)

# 函数
funcs = [
  'g_free',
  'g_hash_table_contains',
  'g_hash_table_lookup',
  'g_list_append',
  'g_malloc',
  'g_queue_free_full',
  'g_queue_get_length',
  'g_queue_new',
  'g_queue_peek_nth',
  'g_queue_pop_tail',
  'g_queue_push_tail',
  'g_queue_remove',
  'g_strcmp0',
]

foreach func : funcs
  cc.has_function(func, dependencies: glib, prefix: '#include <glib.h>', required: true)
endforeach

# 宏
marcos = [
  'g_error',
  'GINT_TO_POINTER',
  'GPOINTER_TO_INT'
]

foreach marco: marcos
  if not cc.has_define(marco, dependencies: glib, prefix: '#include <glib.h>')
    error('Define @0@ not found'.format(marco))
  endif
endforeach

# 配置
arch = build_machine.cpu_family()

glibCflags = run_command('pkg-config', '--cflags', 'glib-2.0', capture: true, check: true).stdout()
glibLdflags = run_command('pkg-config', '--libs', 'glib-2.0', capture: true, check: true).stdout()

cfg = configuration_data({
  'ARCH': arch,
  'GLIB_CFLAGS': glibCflags,
  'GLIB_LDFLAGS': glibLdflags,
  'VERSION': meson.project_version()
})

configure_file(configuration: cfg, input: 'LocalSettings.ini.in', output: 'LocalSettings.ini')

# pkg-config

pc = configuration_data({
  'VER': meson.project_version(),
  'PREFIX': get_option('prefix')
})

configure_file(configuration: pc, input: 'resources/assets/libee.pc.in', output: 'libee.pc')

# 后处理
run_command('cp', '@0@/LocalSettings.ini'.format(meson.project_build_root()), meson.project_source_root(), check: true)

# 目标
custom_target('make',
  command: ['bash', '@0@/make_libeventemitter.sh'.format(meson.project_source_root())],
  build_by_default: true,
  output: [
    'libee.so.1',
    'libee-ver'
  ]
)

# Meson, I l(f)o(u)v(c)e(k) You!

run_command('sh', '-c', 'cd @0@ && mkdir output && touch output/libee.so.1 && touch output/libee-ver'.format(meson.project_source_root()), check: false)

# 安装

install_data(
  '@0@/output/libee.so.1'.format(meson.project_source_root()),
  install_dir: '@0@/lib'.format(get_option('prefix')),
  install_tag: 'runtime'
)

install_data(
  '@0@/output/libee-ver'.format(meson.project_source_root()),
  install_dir: '@0@/bin'.format(get_option('prefix')),
  install_tag: 'runtime'
)

install_data(
  '@0@/libee.pc'.format(meson.project_build_root()),
  install_dir: '@0@/lib/pkgconfig'.format(get_option('prefix')),
  rename: 'libeventemitter.pc',
  install_tag: 'devel'
)

install_subdir(
  '@0@/includes/defines'.format(meson.project_source_root()),
  install_dir: '@0@/include'.format(get_option('prefix')),
  strip_directory: true,
  install_tag: 'devel'
)

install_symlink(
  'libee.so',
  install_dir: '@0@/lib'.format(get_option('prefix')),
  pointing_to: '@0@/lib/libee.so.1'.format(get_option('prefix')),
  install_tag: 'runtime'
)

meson.add_install_script(
  'ldconfig',
  install_tag: 'postinstall'
)

# Meson, I l(f)o(u)v(c)e(k) You!

run_command('sh', '-c', 'cd @0@ && rm -rf output'.format(meson.project_source_root()), check: false)

# 清理
run_target(
  'lbclean',
  command: ['rm', '-rf', '@0@/*.o @0@/output/*'.format(meson.project_source_root())]
)

# 为了应对天(傻)才(逼)meson的限制
message('Never run ninja clean, use ninja lbclean')

# 留给有心之人
# if get_option('lesboys') == 'i_want_see_easter_egg'
#   message('Meow~')
#   if get_option('lesboys2') == 'give_me_more'
#     message('Meson is really stupid and I fucked it')
#   endif
# endif