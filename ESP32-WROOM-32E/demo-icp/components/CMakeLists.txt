# idf_component_register(SRCS "components.c"
#                     INCLUDE_DIRS "include")
set(src_dirs
            common sensors bluetooth)

set(include_dirs .
            common sensors bluetooth)

set(requires
            driver bt)

idf_component_register(SRC_DIRS ${src_dirs} INCLUDE_DIRS ${include_dirs} REQUIRES ${requires})

component_compile_options(-ffast-math -O3 -Wno-error=format=-Wno-format)