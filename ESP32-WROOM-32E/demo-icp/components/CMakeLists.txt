# idf_component_register(SRCS "components.c"
#                     INCLUDE_DIRS "include")
set(src_dirs
            common sensors)

set(include_dirs .
            common sensors)

set(requires
            driver)

idf_component_register(SRC_DIRS ${src_dirs} INCLUDE_DIRS ${include_dirs} REQUIRES ${requires})

component_compile_options(-ffast-math -O3 -Wno-error=format=-Wno-format)