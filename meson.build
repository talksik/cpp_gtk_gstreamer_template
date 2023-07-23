project('flowy', 'cpp')

gtkmm_dep = dependency('gtkmm-4.0', version: '>= 4.6.0')
gstreamer_dep = dependency('gstreamer-1.0')

exe_file = executable('flowy',
  sources: [
    'src/main.cpp',
    'src/local_capture.cpp'
  ],
  dependencies: [gtkmm_dep, gstreamer_dep],
  win_subsystem: 'windows',
)
