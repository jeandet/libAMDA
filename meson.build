project('libAMDA', 'cpp',default_options : ['cpp_std=c++14'])

inc = include_directories('src')

mongoose_dep = dependency('mongoose', required : true, fallback:['mongoose','mongoose'])
cpr = dependency('cpr', required : true, fallback:['cpr','cpr'])

AMDA_lib = library('AMDA',
                       ['src/AMDA_Rest.cpp','src/AMDA_reader.cpp'],
                       include_directories : inc,
                       dependencies : cpr,
                       install : true
                       )


libAMDA = declare_dependency(link_with : AMDA_lib,
                                include_directories : inc)

gtest_dep = dependency('gtest', required : true, main : false, fallback:['gtest','gtest_mainless_dep'])


tests = [
  [['tests/VectorRead/vector_read.cpp'], 'VectorRead', 'Simple Vector Read'],
  [['tests/SimpleREST/SimpleREST.cpp'], 'SimpleREST', 'Simple REST Request']
]

test_src_dir = '-DTEST_SRC_DIR="@0@/tests/"'.format(meson.current_source_dir())

foreach unit_test : tests
  test_exe = executable(unit_test[1],unit_test[0],
                          dependencies : [libAMDA, gtest_dep],
                          cpp_args : [test_src_dir])
  test(unit_test[2], test_exe)
endforeach
